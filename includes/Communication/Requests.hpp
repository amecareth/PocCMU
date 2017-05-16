#ifndef REQUESTS_HPP_
#define REQUESTS_HPP_

class RFAnalyze {
  float _centerFreq;
  int _level;
  float _span;
  std::string _input;
  float _startF;
  float _stopF;

public:
  RFAnalyze(){};
  RFAnalyze(const float centerFreq, const int level, const float span,
            const std::string input)
      : _centerFreq(centerFreq), _level(level), _span(span), _input(input){};
  const float GetCenterFreq() const { return _centerFreq; };
  const int GetLevel() const { return _level; };
  const float GetSpan() const { return _span; };
  const float GetStartFreq() const { return _startF; };
  const float GetStopFreq() const { return _stopF; };
  const std::string GetInput() const { return _input; };
};

class RFGenerate {
  float _freq;
  int _pow;
  std::string _output;

public:
  RFGenerate(){};
  RFGenerate(const float freq, const int pow) : _freq(freq), _pow(pow){};
  RFGenerate(const float freq, const int pow, const std::string output)
      : _freq(freq), _pow(pow), _output(output){};
  const float GetFreq() const { return _freq; };
  const int GetPow() const { return _pow; };
  const std::string GetOutput() const { return _output; };
  ~RFGenerate(){};
};

class RFResults {
  std::map<std::string, std::string> _requests;
  const std::string _mode;
  RFResults();
  
public:
  RFResults(const std::string mode) : _mode(mode) {
    _requests["avg"] = "1;READ:ARR:SPEC:AVER?\n";
    _requests["max"] = "1;READ:ARR:SPEC:MAX?\n";
    _requests["min"] = "1;READ:ARR:SPEC:MIN?\n";
  };
  const std::string GetRequest() { return _requests[_mode]; };
};

#endif
