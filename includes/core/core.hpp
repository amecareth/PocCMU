#ifndef CORE_HPP_
#define CORE_HPP_

#include "Factory.hpp"

class Core {
  boost::asio::ip::tcp::socket *_socket
  Factory _factory;

public:
  Core(){};
  System *GetDevice(const TCPMode &mode);
  System *GetDevice(const SerialMode &mode);
  ~Core(){};
};

#endif
