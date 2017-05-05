#ifndef MODES_HPP_
#define MODES_HPP_

#include <string>

class TCPMode {
  std::string _ip;
  std::string _port;

public:
  TCPMode(const std::string ip, const std::string port)
      : _ip(ip), _port(port){};
  ~TCPMode(){};
  const std::string &GetIp(void) const { return _ip; };
  const std::string &GetPort(void) const { return _port; };

private:
  TCPMode();
};

class SerialMode {
  std::string _port;

public:
  SerialMode(const std::string port) : _port(port){};
  ~SerialMode(){};
  const std::string &GetPort(void) const { return _port; };
};

#endif
