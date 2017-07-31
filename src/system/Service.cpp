#include "../includes/system/Service.hpp"
#include "../includes/json/json.h"

void Service::CreateDevice(const std::string & name, std::vector<std::string> &data) {
  if (data.size() > 1)
  {
    std::cout << "TCP" << std::endl;
    TCPMode tmp(data[0], data[1]);
    _systemMap[name] = _core.GetDevice(tmp);
  }
  else
  {
    std::cout << "SERIAL" << std::endl;
    SerialMode tmp(data[0]);
    _systemMap[name] = _core.GetDevice(tmp);
  }
}

void Service::CreateRFG(const std::string & name, std::vector<std::string> &data) {
  if (data.size() > 2)
    _RFGMap[name] =
        RFGenerate(lexical_cast<float>(data[0]), lexical_cast<int>(data[1]), data[2]);
  else
    _RFGMap[name] = RFGenerate(lexical_cast<float>(data[0]), lexical_cast<int>(data[1]));
}

void Service::CreateBAList(const std::string & name) {
  _listMap[name] = GSMBAList();
}

void Service::AddBA(const std::string & name, std::vector<std::string> &data) {
  if (_listMap.find(name) == _listMap.end())
    CreateBAList(name);
  for (size_t i = 0; i < data.size(); ++i) {
    _listMap[name].AddCell(data[i]);
  }
}

void Service::CreateIdentity(const std::string & name, std::vector<std::string> &data) {
  _IdMap[name] =
      GSMNetworkIdentity(data[0], data[1], data[2], data[3], data[4], data[5]);
}

void Service::CreateRFA(const std::string & name, std::vector<std::string> &data) {
  _RFAMap[name] = RFAnalyze(lexical_cast<float>(data[0]), lexical_cast<int>(data[1]),
                              lexical_cast<float>(data[2]), data[3]);
}

void Service::CreateEmission(const std::string & name, std::vector<std::string> &data) {
  _emissionMap[name] =
      EmissionCell(_IdMap[name], _listMap[name], data[0], data[1]);
      _systemMap[name]->Request(_emissionMap[name]);
}

void Service::CreateResult(const std::string & name, std::vector<std::string> &data) {
  //_resultMap[name] = RFResults(data[0]);
  Json::Value root;
  Json::FastWriter writer;
  RFResults tmp(data[1]);
  Result<RFAnalyze> res(_systemMap[name]->Request(tmp));
  RFAnalyze conf = res.GetParam();
  root["Type"] = "Result";
  root["centerFreq"] = conf.GetCenterFreq();
  root["level"] = conf.GetLevel();
  root["span"] = conf.GetSpan();
  root["startFreq"] = conf.GetStartFreq();
  root["stopFreq"] = conf.GetStopFreq();
  root["resultData"] = res.GetData();
  std::string out = writer.write(root);
  boost::asio::streambuf b;
  std::ostream os(&b);
  os.write(out.c_str(), out.length());
  _socket->send(b.data());
}

void Service::ClearMaps()
{
  std::map<std::string, System*>::iterator iter;

  for (iter = _systemMap.begin(); iter != _systemMap.end(); ++iter){
    delete iter->second;
  }
  _RFGMap.clear();
  _listMap.clear();
  _IdMap.clear();
  _RFAMap.clear();
  _emissionMap.clear();
  _resultMap.clear();
}

void Service::PerformActions(tcp::socket *socket) {
  std::string tmp;
  Json::Value root;
  Json::Reader reader;

  boost::array<char, 128> buf;
  buf.assign(0);
  _socket = socket;
  size_t len = 0;

  for (;;) {
    boost::system::error_code error;

    if (!reader.parse(tmp, root))
      len = socket->read_some(boost::asio::buffer(buf), error);
    else {
      std::vector<std::string> words;
      Service::Action methode;
      std::string args;
      Json::Value req;
      const Json::Value requests = root["requests"];
      const std::string name = root["name"].asString();

      args = root["connection"].asString();
      methode = _map.find("CREATE_DEVICE")->second;
      boost::split(words, args, boost::is_any_of(":"), boost::token_compress_on);
      (this->*methode)(name, words);
      for (int i = 0; i < requests.size(); ++i){
        req = requests[i];
        args = req["args"].asString();
        const std::string action = req["action"].asString();

        boost::split(words, args, boost::is_any_of(" "), boost::token_compress_on);
        methode = _map.find(action)->second;
        (this->*methode)(name, words);
      }
      tmp.clear();
      buf.assign(0);
    }
    if (error == boost::asio::error::eof)
      break; // Connection closed cleanly by peer.
    else if (error)
      throw boost::system::system_error(error); // Some other error.
    tmp.append(buf.data(), len);
  }
  ClearMaps();
}

void Service::CreateMap() {
  _map["CREATE_DEVICE"] = &Service::CreateDevice;
  _map["RFG"] = &Service::CreateRFG;
  _map["BAList"] = &Service::AddBA;
  _map["ID"] = &Service::CreateIdentity;
  _map["RFA"] = &Service::CreateRFA;
  _map["Emission"] = &Service::CreateEmission;
  _map["Result"] = &Service::CreateResult;
}
