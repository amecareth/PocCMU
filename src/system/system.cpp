#include "../../includes/system/system.hpp"

int System::SendData(const boost::asio::streambuf &b) {
  if (_socket != NULL)
    _socket->send(b.data());
  else
    _port->write_some(b.data());
};

const std::string System::ProcessResponse() {
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
