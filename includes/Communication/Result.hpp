#ifndef RESULT_HPP_
#define RESULT_HPP_

template <typename T> class Result {
  T _params;
  std::string _data;

public:
  Result(){};
  Result<T>(const Result<T> &res){_params = res.GetParam(); _data = res.GetData();};
  ~Result(){};
  const std::string GetData() const { return _data; };
  void SetData(std::string data) { _data = data; };
  const T &GetParam() const { return _params; };
  void SetParam(const T &params) { _params = params; };
};

#endif
