#ifndef CORE_HPP_
#define CORE_HPP_

#include "Factory.hpp"

class Core
{
  Factory _factory;

public:
  Core();
  System *GetDevice(const std::string &, int)
  ~Core();
};

#endif
