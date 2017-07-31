#ifndef SERVICE_HPP_
#define SERVICE_HPP_

#include "../includes/core/core.hpp"
#include "../includes/Communication/Modes.hpp"
#include "../includes/Communication/Requests.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp> // Include boost::for is_any_of
#include <boost/algorithm/string/split.hpp>
//#include <unistd.h>
//#include <iostream>
#include <boost/lexical_cast.hpp>
using boost::lexical_cast;

// typedef void (Service::*Action)(std::vector<std::string> &);

class Service {
  typedef void (Service::*Action)(const std::string &, std::vector<std::string> &);
  typedef std::map<std::string, Action> ActionMap;

  Core _core;
  ActionMap _map;
  boost::asio::ip::tcp::socket *_socket = NULL;
  std::map<std::string, System *> _systemMap;
  std::map<std::string, RFGenerate> _RFGMap;
  std::map<std::string, GSMBAList> _listMap;
  std::map<std::string, GSMNetworkIdentity> _IdMap;
  std::map<std::string, RFAnalyze> _RFAMap;
  std::map<std::string, EmissionCell> _emissionMap;
  std::map<std::string, RFResults> _resultMap;

  void CreateDevice(const std::string & name, std::vector<std::string> &data);
  void CreateRFG(const std::string & name, std::vector<std::string> &data);
  void CreateBAList(const std::string & name);
  void AddBA(const std::string & name, std::vector<std::string> &data);
  void CreateIdentity(const std::string & name, std::vector<std::string> &data);
  void CreateRFA(const std::string & name, std::vector<std::string> &data);
  void CreateEmission(const std::string & name, std::vector<std::string> &data);
  void CreateResult(const std::string & name, std::vector<std::string> &data);
  void ClearMaps();

  void CreateMap();

public:
  Service() { CreateMap(); }
  void PerformActions(tcp::socket *socket);
  ~Service() { ClearMaps(); }
};

#endif
