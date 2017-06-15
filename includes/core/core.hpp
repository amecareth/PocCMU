#ifndef CORE_HPP_
#define CORE_HPP_

#include "Factory.hpp"
#include <iostream>

using boost::asio::ip::tcp;

class Core {
  Factory _factory;

public:
  Core(){};
  System *GetDevice(const TCPMode &mode);
  System *GetDevice(const SerialMode &mode);
  ~Core(){};
};

#endif
