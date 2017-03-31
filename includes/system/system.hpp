#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include <string>

class System
{
  std::string _deviceName;
  std::string _data;
  std::string _response;

public:
  System();
  virtual ~System();
  int LoadDevice();
  virtual int SendData() = 0;
  virtual void ProcessResponse() = 0;

};

#endif
