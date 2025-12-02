#ifndef GCX_MUDUO_INET_ADDRESS_H
#define GCX_MUDUO_INET_ADDRESS_H
#include <arpa/inet.h>

#include <memory>
#include <netinet/in.h>
#include <string>
#include <untils/copyable.h>
class InetAddress : copyable {
public:
  explicit InetAddress(const std::string &ip, const uint32_t port) : addr_{} {
    addr_.sin_family = AF_INET;
    addr_.sin_port = ::htons(port);
    addr_.sin_addr.s_addr = ::inet_addr(ip.c_str());
  }
  explicit InetAddress(const uint32_t port) : InetAddress("127.0.0.1", port) {}
  explicit InetAddress(const sockaddr_in &addr) : addr_(addr) {}
  [[nodiscard]] std::string ToIpv4Ip() const {
    char buf[16]{};
    ::inet_ntop(AF_INET, &addr_.sin_addr, buf, 16);
    return std::string{buf};
  }

  [[nodiscard]] uint16_t ToIpv4Port() const { return ::ntohs(addr_.sin_port); }

  [[nodiscard]] std::string ToIpv4IpPort() const {
    auto str = ToIpv4Ip();
    str.reserve(22);
    std::sprintf(str.data() + str.size(), ":%u", ToIpv4Port());
    return std::string{str.data()};
  }

private:
  sockaddr_in addr_;
};
#endif // GCX_MUDUO_INET_ADDRESS_H
