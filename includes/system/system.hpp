#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include <boost/asio/io_service.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio.hpp>
#include "../Communication/Requests.hpp"
#include "../Communication/Result.hpp"

class System {
protected:
//  std::string _deviceName = "";
  boost::asio::ip::tcp::socket *_socket = NULL;
  boost::asio::serial_port *_port = NULL;

  int SendData(const boost::asio::streambuf &b);
  const std::string ProcessResponse();

public:
  System(){};
  virtual ~System() {
    if (_socket != NULL) {
      _socket->close();
    } else if (_port != NULL) {
      _port->close();
      delete _port;
    }
  };
  void SetSocket(boost::asio::ip::tcp::socket *socket) { _socket = socket; };
  void SetSocket(boost::asio::serial_port *socket) { _port = socket; };
  virtual const Result<RFGenerate> Request(const RFGenerate &conf){};
  virtual const Result<RFAnalyze> Request(const RFAnalyze &conf){};
  virtual const Result<RFAnalyze> Request(RFResults &request){};
  virtual const Result<EmissionCell> Request(const EmissionCell &request){};
};

typedef System *(*CreateSys)(void);

#endif
