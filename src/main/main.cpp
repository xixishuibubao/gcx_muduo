#include <inet_address/inet_address.h>
#include <iostream>

int main() {

  InetAddress ip1(8080);

  std::cout << ip1.ToIpv4Ip() << std::endl;
  std::cout << ip1.ToIpv4IpPort() << std::endl;
}
