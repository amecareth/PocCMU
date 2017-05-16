#include "../../includes/SML/sml.hpp"

const Result<RFGenerate> SML::Request(const RFGenerate &conf) {
  Result<RFGenerate> res;
  boost::asio::streambuf b;
  std::ostream os(&b);
  std::string tmp =
      "FREQ " + boost::lexical_cast<std::string>(conf.GetFreq()) + "MHz\n";
  os.write(tmp.c_str(), tmp.length());
  tmp = "POW " + boost::lexical_cast<std::string>(conf.GetPow()) + "dBm\n";
  os.write(tmp.c_str(), tmp.length());
  tmp = "OUTP:STAT ON\n";
  os.write(tmp.c_str(), tmp.length());
  SendData(b);
  res.SetParam(conf);
  return res;
};
