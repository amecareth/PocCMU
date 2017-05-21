#include "./includes/core/core.hpp"
#include "./includes/Communication/Modes.hpp"
#include "./includes/Communication/Requests.hpp"

#include <boost/algorithm/string.hpp>

#include <unistd.h>

#include <gnuplot-iostream.h>

#include <iostream>




int main(int argc, char ** argv) {
  Core core;
  float freq = 42;
  
  if (argc == 2) {
    freq = atof(argv[1]);
  }
 

  SerialMode test("/dev/ttyUSB0");
  System *analyzer = core.GetDevice(test);

  GSMNetworkIdentity id("5", "7", "555", "05", "1", "2");
  GSMBAList list;
  list.AddCell("40");
  list.AddCell("42");
  EmissionCell cell(id, list, "1", "-50");
  analyzer->Request(cell);
  /*
  //RFAnalyze rfa(freq, 0, 1 /*SPAN (MHz), "RF1");
  //analyzer->Request(rfa);
  
  //RFResults rfs("max");
  //std::string response = analyzer->Request(rfs);

  
  Gnuplot gp;
  std::vector<std::string> plots;
  boost::split(plots, response, boost::is_any_of(","));
  std::vector<double> plots_f;
  for (std::vector<std::string>::iterator it = plots.begin(); it != plots.end(); it++) {
    plots_f.push_back(atof((*it).c_str()));
  }
  
  gp << "plot " << gp.file1d(plots_f) << " with lines title '" << "spectre : " << freq << " MHz' " << std::endl;*/
  
 
  return 0;  
}
