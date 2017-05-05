#ifndef REQUESTS_HPP_
#define REQUESTS_HPP_

class RFAnalyze {
  int _centerFreq;
  int _level;
  int _span;
  int _startF;
  int _stopF;

public:
  RFAnalyze(const int centerFreq, const int level, const int span)
      : _centerFreq(centerFreq), _level(level), _span(span){};
  const int GetCenterFreq() const { return _centerFreq; };
  const int GetLevel() const { return _level; };
  const int GetSpan() const { return _span; };
  const int GetStartFreq() const { return _startF; };
  const int GetStopFreq() const { return _stopF; };
};

class RFGenerate {
  int _freq;
  int _pow;
  RFGenerate();

public:
  RFGenerate(const int freq, const int pow) : _freq(freq), _pow(pow){};
  const int GetFreq() const { return _freq; };
  const int GetPow() const { return _pow; };
  ~RFGenerate(){};
};

#endif
