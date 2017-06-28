#include "../../includes/core/core.hpp"

System *Core::GetDevice(const TCPMode &mode) {

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
  buf.assign(0);
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

System *Core::GetDevice(const SerialMode &mode) {
//boost::asio::io_service io_service;
  boost::asio::serial_port *port =
      new boost::asio::serial_port(io_service, mode.GetPort());
  port->set_option(boost::asio::serial_port_base::baud_rate(9600));
  port->set_option(boost::asio::serial_port_base::flow_control(
      boost::asio::serial_port_base::flow_control::software));
  port->set_option(boost::asio::serial_port_base::parity(
      boost::asio::serial_port_base::parity::none));
  port->set_option(boost::asio::serial_port_base::stop_bits(
      boost::asio::serial_port_base::stop_bits::one));
  port->set_option(boost::asio::serial_port_base::character_size(8));

  boost::asio::streambuf b;
  std::ostream os(&b);
  os << "*IDN?\n";
  port->write_some(b.data());
  std::string tmp;

  boost::array<char, 128> buf;
  size_t len = 1;
  std::cout << "TMP = " + tmp << std::endl;

  for (;;) {
    boost::system::error_code error;
    if (buf[len - 1] != '\n')
      len = port->read_some(boost::asio::buffer(buf), error);
    else
      break;
    if (error == boost::asio::error::eof)
      break; // Connection closed cleanly by peer.
    else if (error)
      throw boost::system::system_error(error); // Some other error.
    tmp.append(buf.data(), len);
  }
  std::cout << tmp;
  return _factory.CreateSystem(port, tmp);
};
