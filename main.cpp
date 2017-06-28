#include "./includes/system/Service.hpp"

int main(int argc, char **argv) {
  Service service;
  boost::asio::io_service io_service;

  tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13));
  for (;;) {
    tcp::socket socket(io_service);

    acceptor.accept(socket);
    service.PerformActions(&socket);
    socket.close();
  }
  return 0;
}
