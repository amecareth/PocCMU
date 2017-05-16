#ifndef SML_HPP_
#define SML_HPP_

#include "../system/system.hpp"
#include <boost/lexical_cast.hpp>
#include <iostream>

class SML : protected System {
public:
  SML(){};
  ~SML(){};
  const Result<RFGenerate> Request(const RFGenerate &conf);

  static System *Create() { return new SML(); };
};

#endif
