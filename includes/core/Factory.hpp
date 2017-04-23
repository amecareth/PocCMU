#ifndef FACTORY_HPP_
#define FACTORY_HPP_

#include "../system/system.hpp"

class Factory
{
public:
  Factory();
  System *CreateSystem(boost::asio::ip::tcp::socket const &, const std::string);
  ~Factory();
};

#endif
