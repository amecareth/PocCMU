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
  int SendData(const boost::asio::streambuf &b) {
    if (_socket != NULL)
      _socket->send(b.data());
    else
      _port->write_some(b.data());
  };
  const std::string ProcessResponse() {
    std::string tmp;
    if (_socket != NULL) {
      boost::array<char, 128> buf;
      size_t len = 1;

      for (;;) {
        boost::system::error_code error;

        if (buf[len - 1] != '\n')
          len = _socket->read_some(boost::asio::buffer(buf), error);
        else
          break;
        if (error == boost::asio::error::eof)
          break; // Connection closed cleanly by peer.
        else if (error)
          throw boost::system::system_error(error); // Some other error.
        tmp.append(buf.data(), len);
      }
    } else {
      boost::array<char, 128> buf;
      size_t len = 1;

      for (;;) {
        boost::system::error_code error;

        if (buf[len - 1] != '\n')
          len = _port->read_some(boost::asio::buffer(buf), error);
        else
          break;
        if (error == boost::asio::error::eof)
          break; // Connection closed cleanly by peer.
        else if (error)
          throw boost::system::system_error(error); // Some other error.
        tmp.append(buf.data(), len);
      }
    }
    return tmp;
  };

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
  virtual const std::string Request(RFResults &request){};
};

typedef System *(*CreateSys)(void);

#endif
