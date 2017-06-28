#ifndef CORE_HPP_
#define CORE_HPP_

#include "Factory.hpp"
#include <iostream>

using boost::asio::ip::tcp;

class Core {
  boost::asio::io_service io_service;

  Factory _factory;

public:
  Core(){};
  System *GetDevice(const TCPMode &mode);
  System *GetDevice(const SerialMode &mode);
  ~Core(){};
};

#endif
