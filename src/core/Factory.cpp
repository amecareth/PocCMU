#include "../../includes/core/Factory.hpp"
#include <iostream>
System *Factory::CreateSystem(boost::asio::ip::tcp::socket *socket,
                              const std::string name) {
  System *tmp;
  for (std::map<std::string, CreateSys>::iterator it = _factoryMap.begin();
       it != _factoryMap.end(); ++it) {
    if (name.find(it->first) != std::string::npos) {
      tmp = it->second();
      tmp->SetSocket(socket);
      return tmp;
    }
  }
  return NULL;
}

System *Factory::CreateSystem(boost::asio::serial_port *port,
                              const std::string name) {
  System *tmp;
  for (std::map<std::string, CreateSys>::iterator it = _factoryMap.begin();
       it != _factoryMap.end(); ++it) {
    if (name.find(it->first) != std::string::npos) {
      tmp = it->second();
      tmp->SetSocket(port);
      return tmp;
    }
  }
  return NULL;
}
