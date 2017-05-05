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
    tmp = "1;INITiate:SPECtrum\n";
    os.write(tmp.c_str(), tmp.length());
    _socket->send(b.data());
    return "";
  };
  static System *Create() { return new CMU(); };

private:
  int SendData(){};
  void ProcessResponse(){};
};

#endif
