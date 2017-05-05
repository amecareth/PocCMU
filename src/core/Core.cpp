#include "../../includes/core/core.hpp"
#include <iostream>
using boost::asio::ip::tcp;

System *Core::GetDevice(const TCPMode &mode) {
  boost::asio::io_service io_service;

  tcp::resolver resolver(io_service);
  tcp::resolver::query query(mode.GetIp(), mode.GetPort());
  tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

  tcp::socket *socket = new tcp::socket(io_service);
  boost::asio::connect(*socket, endpoint_iterator);
  boost::asio::streambuf b;
  std::ostream os(&b);
  os << "*IDN?\n";
  socket->send(b.data());
  std::string tmp;

  boost::array<char, 128> buf;
  size_t len = 1;

  for (;;) {
    boost::system::error_code error;

    if (buf[len - 1] != '\n')
      len = socket->read_some(boost::asio::buffer(buf), error);
    else
      break;
    if (error == boost::asio::error::eof)
      break; // Connection closed cleanly by peer.
    else if (error)
      throw boost::system::system_error(error); // Some other error.
    tmp.append(buf.data(), len);
  }
  std::cout << tmp;
  return _factory.CreateSystem(socket, tmp);
}

System *Core::GetDevice(const SerialMode &mode){};
