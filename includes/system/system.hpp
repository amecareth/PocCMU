#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include <string>
#include <boost/asio/io_service.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio.hpp>
#include "../Communication/Requests.hpp"

class System {
protected:
  std::string _deviceName = "";
  std::string _data = "";
  std::string _response = "";
  boost::asio::ip::tcp::socket *_socket = NULL;
  boost::asio::serial_port *_port = NULL;
  virtual int SendData() = 0;
  virtual void ProcessResponse() = 0;

public:
  System(){};
  virtual ~System() {
    if (_socket != NULL) {
      _socket->close();
      delete _socket;
    } else if (_port != NULL) {
      _port->close();
      delete _port;
    }
  };
  void SetSocket(boost::asio::ip::tcp::socket *socket) { _socket = socket; };
  void SetSocket(boost::asio::serial_port *socket) { _port = socket; };
  virtual const std::string Request(const RFGenerate &conf){};
  virtual const std::string Request(const RFAnalyze &conf){};
};

typedef System *(*CreateSys)(void);

#endif
