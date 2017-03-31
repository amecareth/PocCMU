#ifndef CORE_HPP_
#define CORE_HPP_

#include "system.hpp"

class Core
{
  System _device;

private:
  int openPort(void);
  int configurePort(int);
public:
  Core();
  Initilize();
  ~Core();
};

#endif
