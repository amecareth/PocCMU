#include "./includes/core/core.hpp"
#include "./includes/Communication/Modes.hpp"
#include "./includes/Communication/Requests.hpp"

int main() {
  Core core;
  RFGenerate rfg(150, 9);
  RFAnalyze rfa(150, 5, 100);
  TCPMode mode1("172.23.240.105", "10002");
  TCPMode mode2("172.23.240.105", "10001");
  SerialMode test("/dev/ttyUSB0");
  System *analyzer = core.GetDevice(test);
  System *generator = core.GetDevice(mode2);
  generator->Request(rfg);
  analyzer->Request(rfa);
}
