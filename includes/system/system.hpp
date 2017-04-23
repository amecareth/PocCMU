#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include <string>

class System
{
  std::string _deviceName;
  std::string _data;
  std::string _response;
  boost::asio::ip::tcp::socket socket;

public:
  System();
  virtual ~System();
  virtual const std::string & Request(const std::string &);

private:
  virtual int SendData() = 0;
  virtual void ProcessResponse() = 0;
};

#endif
