#include "../../includes/CMU/cmu.hpp"

const Result<RFAnalyze> CMU::Request(const RFAnalyze &conf) {
  Result<RFAnalyze> res;
  boost::asio::streambuf b;
  std::ostream os(&b);
  std::string tmp;
  if (conf.GetCenterFreq() != 0) {
    tmp = "1;SENS:SPEC:FREQ:CENT " +
          boost::lexical_cast<std::string>(conf.GetCenterFreq()) + "MHz\n";
    os.write(tmp.c_str(), tmp.length());
    tmp = "1;SENS:SPEC:FREQ:SPAN " +
          boost::lexical_cast<std::string>(conf.GetSpan()) + "MHz\n";
    os.write(tmp.c_str(), tmp.length());
    tmp = "1;SENS:SPEC:LEV:RANG " +
          boost::lexical_cast<std::string>(conf.GetLevel()) + "\n";
    os.write(tmp.c_str(), tmp.length());
  } else {
  }
  tmp = "1;INP:STAT " + conf.GetInput() + "\n";
  os.write(tmp.c_str(), tmp.length());
  tmp = "1;INITiate:SPECtrum\n";
  os.write(tmp.c_str(), tmp.length());
  SendData(b);
  res.SetParam(conf);
  return res;
};

const Result<RFAnalyze> CMU::Request(RFResults &request) {
  Result<RFAnalyze> res;
  boost::asio::streambuf b;
  std::ostream os(&b);
  std::string tmp;

  tmp = request.GetRequest();
  os.write(tmp.c_str(), tmp.length());
  SendData(b);
  res.SetParam(GetConf());
  res.SetData(ProcessResponse());
  return res;
};

const Result<RFGenerate> CMU::Request(const RFGenerate &conf) {
  Result<RFGenerate> res;
  boost::asio::streambuf b;
  std::ostream os(&b);
  std::string tmp = "1;SOUR:RFG:TX:FREQ " +
                    boost::lexical_cast<std::string>(conf.GetFreq()) + "MHz\n";
  os.write(tmp.c_str(), tmp.length());
  tmp = "1;OUTP:TX:STAT " + conf.GetOutput() + "\n";
  os.write(tmp.c_str(), tmp.length());
  tmp = "1;SOUR:RFG:TX:LEV " + boost::lexical_cast<std::string>(conf.GetPow()) +
        ".0\n";
  os.write(tmp.c_str(), tmp.length());
  tmp = "1;INIT:RFG:TX\n";
  os.write(tmp.c_str(), tmp.length());
  SendData(b);
  res.SetParam(conf);
  return res;
};
