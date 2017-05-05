#ifndef SML_HPP_
#define SML_HPP_

#include "../system/system.hpp"
#include <boost/lexical_cast.hpp>
#include <iostream>

class SML : protected System {
public:
  SML(){};
  ~SML(){};
  void toto() { std::cout << "coucou\n"; };
  const std::string Request(const RFGenerate &conf) {
    boost::asio::streambuf b;
    std::ostream os(&b);
    std::string tmp =
        "FREQ " + boost::lexical_cast<std::string>(conf.GetFreq()) + "MHz\n";
    os.write(tmp.c_str(), tmp.length());
    tmp = "POW " + boost::lexical_cast<std::string>(conf.GetPow()) + "dBm\n";
    os.write(tmp.c_str(), tmp.length());
    tmp = "OUTP:STAT ON\n";
    os.write(tmp.c_str(), tmp.length());
    _socket->send(b.data());
    return "";
  };

  static System *Create() { return new SML(); };

private:
  int SendData(){};
  void ProcessResponse(){};
};

#endif
