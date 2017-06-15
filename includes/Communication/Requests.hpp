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

class GSMBAList{
  std::vector<std::string> _cells;

public:
  GSMBAList(){};
  ~GSMBAList(){};
  void AddCell(std::string bcchNum){ _cells.push_back(bcchNum); };
  const std::vector<std::string> &GetCells() const { return _cells; };
};

class GSMNetworkIdentity {
  std::string _ncc;
  std::string _bcc;
  std::string _mcc;
  std::string _mncNbDigits;
  std::string _mnc;
  std::string _lac;
  std::string _cellID;

public:
  GSMNetworkIdentity(){};
  GSMNetworkIdentity(const std::string &ncc, const std::string &bcc,
                     const std::string &mcc, const std::string &mnc,
		     const std::string &lac, const std::string &cellID)
      : _ncc(ncc), _bcc(bcc), _mcc(mcc), _mnc(mnc), _lac(lac),_cellID(cellID){};

  void SetNCC(const std::string &newNCC){ _ncc = newNCC; };
  void SetBCC(const std::string &newBCC){ _bcc = newBCC; };
  void SetMCC(const std::string &newMCC){ _mcc = newMCC; };
  void SetMNC(const std::string &newMNC){ _mnc = newMNC; };
  void SetLAC(const std::string &newLAC){ _lac = newLAC; };
  void SetCellID(const std::string &newCellID){ _cellID = newCellID; };

  const std::string GetNCC() const { return _ncc; };
  const std::string GetBCC() const { return _bcc; };
  const std::string GetMCC() const { return _mcc; };
  const std::string GetMNC() const { return _mnc; };
  const std::string GetLAC() const { return _lac; };
  const std::string GetCellID() const { return _cellID; };
};

class EmissionCell{
  GSMNetworkIdentity _netId;
  GSMBAList _BAList;
  std::string _channel;
  std::string _level;

public:
  EmissionCell(){};
  EmissionCell(const GSMNetworkIdentity &netId, const GSMBAList &BAList,
    const std::string &channel, const std::string &level): _netId(netId), _BAList(BAList), _channel(channel), _level(level){};
  const GSMNetworkIdentity &GetNetId() const { return _netId; };
  const GSMBAList &GetBAList() const { return _BAList; };
  const std::string &GetChannel() const { return _channel; };
  const std::string &GetLevel() const { return _level; };
  ~EmissionCell(){};
};

class RFResults {
  std::map<std::string, std::string> _requests;
  std::string _mode;

public:
  RFResults(){};
  RFResults(const std::string mode) : _mode(mode) {
    _requests["avg"] = "1;READ:ARR:SPEC:AVER?\n";
    _requests["max"] = "1;READ:ARR:SPEC:MAX?\n";
    _requests["min"] = "1;READ:ARR:SPEC:MIN?\n";
  };
  const std::string GetRequest(){ return _requests[_mode]; };
};

#endif
