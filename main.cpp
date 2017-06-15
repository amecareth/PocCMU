#include "./includes/core/core.hpp"
#include "./includes/Communication/Modes.hpp"
#include "./includes/Communication/Requests.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp> // Include boost::for is_any_of
#include <boost/algorithm/string/split.hpp>
#include <unistd.h>

//#include <gnuplot-iostream.h>

#include <iostream>
#include <boost/lexical_cast.hpp>
using boost::lexical_cast;

typedef void (*Action)(std::vector<std::string> &);
typedef std::map<std::string, Action> ActionMap;

Core core;
ActionMap map;
std::map<std::string, System *> systemMap;
std::map<std::string, RFGenerate> RFGMap;
std::map<std::string, GSMBAList> listMap;
std::map<std::string, GSMNetworkIdentity> IdMap;
std::map<std::string, RFAnalyze> RFAMap;
std::map<std::string, EmissionCell> emissionMap;
std::map<std::string, RFResults> resultMap;

void createDevice(std::vector<std::string> &data) {
  if (data.size() > 3)
  {
    std::cout << "TCP" << std::endl;
    TCPMode tmp(data[2], data[3]);
    systemMap[data[1]] = core.GetDevice(tmp);
  }
  else
  {
    std::cout << "SERIAL" << std::endl;
    SerialMode tmp(data[2]);
    systemMap[data[1]] = core.GetDevice(tmp);
  }
}

void createRFG(std::vector<std::string> &data) {
  if (data.size() > 4)
    RFGMap[data[1]] =
        RFGenerate(lexical_cast<float>(data[2]), lexical_cast<int>(data[3]), data[4]);
  else
    RFGMap[data[1]] = RFGenerate(lexical_cast<float>(data[2]), lexical_cast<int>(data[3]));
}

void createBAList(std::vector<std::string> &data) {
  listMap[data[1]] = GSMBAList();
}

void addBA(std::vector<std::string> &data) {
  for (size_t i = 2; i < data.size(); ++i) {
    listMap[data[1]].AddCell(data[i]);
  }
}

void createIdentity(std::vector<std::string> &data) {
  IdMap[data[1]] =
      GSMNetworkIdentity(data[2], data[3], data[4], data[5], data[6], data[7]);
}

void createRFA(std::vector<std::string> &data) {
  RFAMap[data[1]] = RFAnalyze(lexical_cast<float>(data[2]), lexical_cast<int>(data[3]),
                              lexical_cast<float>(data[4]), data[5]);
}

void createEmission(std::vector<std::string> &data) {
  emissionMap[data[1]] =
      EmissionCell(IdMap[data[1]], listMap[data[1]], data[2], data[3]);
      systemMap[data[1]]->Request(emissionMap[data[1]]);
}

void createResult(std::vector<std::string> &data) {
  resultMap[data[1]] = RFResults(data[2]);
}

void clearMaps()
{
  std::map<std::string, System*>::iterator iter;

  for (iter = systemMap.begin(); iter != systemMap.end(); ++iter){
    delete iter->second;
  }
  RFGMap.clear();
  listMap.clear();
  IdMap.clear();
  RFAMap.clear();
  emissionMap.clear();
  resultMap.clear();
}

void performActions(tcp::socket *socket) {
  std::string tmp;

  boost::array<char, 128> buf;
  buf.assign(0);
  size_t len = 1;

  for (;;) {
    boost::system::error_code error;

    if (buf[len - 1] != '\n')
      len = socket->read_some(boost::asio::buffer(buf), error);
    else {
      std::vector<std::string> cmd;
      std::vector<std::string> words;
      std::cout << tmp;
      boost::split(cmd, tmp, boost::is_any_of("\n"), boost::token_compress_on);
      cmd.pop_back();
      for (size_t i = 0; i < cmd.size();++i){
        boost::split(words, cmd[i], boost::is_any_of(" "), boost::token_compress_on);
        map[words[0]](words);
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
  clearMaps();
}

int main(int argc, char **argv) {
  boost::asio::io_service io_service;

  tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13));
  map["CREATE_DEVICE"] = &createDevice;
  map["CREATE_RFG"] = &createRFG;
  map["CREATE_BALIST"] = &createBAList;
  map["ADD_BA"] = &addBA;
  map["CREATE_ID"] = &createIdentity;
  map["CREATE_RFA"] = &createRFA;
  map["CREATE_EMISSION"] = &createEmission;
  map["CREATE_RESULT"] = &createResult;
  for (;;) {
    tcp::socket socket(io_service);

    acceptor.accept(socket);
    performActions(&socket);
  }
  return 0;
}
