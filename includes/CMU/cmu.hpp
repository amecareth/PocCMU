#ifndef CMU_HPP_
#define CMU_HPP_

#include "../system/system.hpp"
#include <boost/lexical_cast.hpp>
#include <iostream>

class CMU : protected System {
  RFAnalyze _conf;

public:
  CMU(){};
  ~CMU(){};
  const RFAnalyze &GetConf() { return _conf; };
  void SetConf(RFAnalyze &conf) { _conf = conf; };
  const Result<RFAnalyze> Request(const RFAnalyze &conf);
  const Result<RFAnalyze> Request(RFResults &request);
  const Result<RFGenerate> Request(const RFGenerate &conf);
  static System *Create() { return new CMU(); };
};

#endif
