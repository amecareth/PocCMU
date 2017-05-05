#ifndef FACTORY_HPP_
#define FACTORY_HPP_

#include "../Communication/Modes.hpp"
#include "../CMU/cmu.hpp"
#include "../SML/sml.hpp"

class Factory {
  typedef std::map<std::string, CreateSys> SystemMap;
  SystemMap _factoryMap;

private:
  void Register(const std::string deviceName, CreateSys func) {
    _factoryMap[deviceName] = func;
  };

public:
  Factory() {
    Register("CMU 200", &CMU::Create);
    Register("SML", &SML::Create);
  };
  System *CreateSystem(boost::asio::ip::tcp::socket *socket,
                       const std::string name);
  System *CreateSystem(boost::asio::serial_port *port, const std::string name);
  ~Factory(){};
};

#endif
