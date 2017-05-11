#ifndef CMU_HPP_
#define CMU_HPP_

#include "../system/system.hpp"
#include <boost/lexical_cast.hpp>
#include <iostream>

class CMU : protected System {
public:
  CMU(){};
  ~CMU(){};
  const std::string Request(const RFAnalyze &conf) {
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
    return "";
  };

  const std::string Request(RFResults &request) {
    boost::asio::streambuf b;
    std::ostream os(&b);
    std::string tmp;

    tmp = request.GetRequest();
    os.write(tmp.c_str(), tmp.length());
    SendData(b);
    return ProcessResponse();
  };

  const std::string Request(const RFGenerate &conf) {
    boost::asio::streambuf b;
    std::ostream os(&b);
    std::string tmp = "1;SOUR:RFG:TX:FREQ " +
                      boost::lexical_cast<std::string>(conf.GetFreq()) +
                      "MHz\n";
    os.write(tmp.c_str(), tmp.length());
    tmp = "1;OUTP:TX:STAT " + conf.GetOutput() + "\n";
    os.write(tmp.c_str(), tmp.length());
    tmp = "1;SOUR:RFG:TX:LEV " +
          boost::lexical_cast<std::string>(conf.GetPow()) + ".0\n";
    os.write(tmp.c_str(), tmp.length());
    tmp = "1;INIT:RFG:TX\n";
    os.write(tmp.c_str(), tmp.length());
    SendData(b);
    return "";
  };

  static System *Create() { return new CMU(); };
};

#endif
