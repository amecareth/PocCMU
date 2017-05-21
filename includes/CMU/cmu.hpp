#ifndef CMU_HPP_
#define CMU_HPP_

#include "../system/system.hpp"
#include <boost/lexical_cast.hpp>
#include <iostream>

class CMU : protected System {
  RFAnalyze _conf;
  EmissionCell _gsmConf;

  const RFAnalyze &GetConf() { return _conf; };
  void SetConf(RFAnalyze &conf) { _conf = conf; };

  void WriteNetInf(const GSMNetworkIdentity &request);
  void WriteBAList(const GSMBAList &request);

public:
  CMU(){};
  ~CMU(){};
  const Result<RFAnalyze> Request(const RFAnalyze &conf);
  const Result<RFAnalyze> Request(RFResults &request);
  const Result<RFGenerate> Request(const RFGenerate &conf);
  const Result<EmissionCell> Request(const EmissionCell &request);
  static System *Create() { return new CMU(); };
};

#endif
