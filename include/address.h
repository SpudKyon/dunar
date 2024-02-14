//
// Created by spud on 24-2-14.
//

#ifndef DUNAR_ADDRESS_H
#define DUNAR_ADDRESS_H

#include <map>
#include <memory>
#include <netinet/in.h>
#include <sys/socket.h>
#include <vector>
namespace dunar {

class IPAddress;

class Address {
 public:
  using ptr = std::shared_ptr<Address>;

  static Address::ptr create(const sockaddr* addr, socklen_t addrlen);
  static bool lookup(std::vector<Address::ptr>& result, const std::string& host,
                     int family = AF_UNSPEC, int type = 0, int protocol = 0);
  static Address::ptr lookupAny(const std::string& host, int family = AF_UNSPEC,
                                int type = 0, int protocol = 0);
  static std::shared_ptr<IPAddress> lookupAnyIPAddress(const std::string& host,
                                                       int family = AF_UNSPEC,
                                                       int type = 0,
                                                       int protocol = 0);
  static bool getInterfaceAddresses(
      std::multimap<std::string, std::pair<Address::ptr, uint32_t>>& result,
      int family = AF_UNSPEC);
  static bool getInterfaceAddresses(
      std::vector<std::pair<Address::ptr, uint32_t>>& result,
      const std::string& iface, int family = AF_UNSPEC);

  virtual ~Address() {}

  int getFamily() const;

  virtual const sockaddr* getAddr() const = 0;
  virtual socklen_t getAddrLen() const = 0;

  virtual std::ostream& insert(std::ostream& os) const = 0;
  std::string toString();

  bool operator<(const Address& rhs) const;
  bool operator==(const Address& rhs) const;
  bool operator!=(const Address& rhs) const;
};

class IPAddress : public Address {
 public:
  using ptr = std::shared_ptr<IPAddress>;

  static IPAddress::ptr create(const char* address, uint32_t port = 0);

  virtual IPAddress::ptr broadcastAddress(uint32_t prefix_len) = 0;
  virtual IPAddress::ptr networdAddress(uint32_t prefix_len) = 0;
  virtual IPAddress::ptr subnetMask(uint32_t prefix_len) = 0;

  virtual uint32_t getPort() const = 0;
  virtual void setPort(uint32_t v) = 0;
};

class IPv4Address : public IPAddress {
 public:
  using ptr = std::shared_ptr<IPv4Address>;

  static IPv4Address::ptr create(const char* address, uint32_t port = 0);

  IPv4Address(const sockaddr_in& address);
  IPv4Address(uint32_t address = INADDR_ANY, uint32_t port = 0);

  const sockaddr* getAddr() const override;
  socklen_t getAddrLen() const override;
  std::ostream& insert(std::ostream& os) const override;

  IPAddress::ptr broadcastAddress(uint32_t prefix_len) override;
  IPAddress::ptr networdAddress(uint32_t prefix_len) override;
  IPAddress::ptr subnetMask(uint32_t prefix_len) override;
  uint32_t getPort() const override;
  void setPort(uint32_t v) override;

 private:
  sockaddr_in m_addr;
};

class IPv6Address : public IPAddress {
 public:
  using ptr = std::shared_ptr<IPv6Address>;

  static IPv6Address::ptr create(const char* address, uint32_t port = 0);

  IPv6Address();
  IPv6Address(const sockaddr_in6& address);
  IPv6Address(const uint8_t address[16], uint32_t port = 0);

  const sockaddr* getAddr() const override;
  socklen_t getAddrLen() const override;
  std::ostream& insert(std::ostream& os) const override;
  IPAddress::ptr broadcastAddress(uint32_t prefix_len) override;
  IPAddress::ptr networdAddress(uint32_t prefix_len) override;
  IPAddress::ptr subnetMask(uint32_t prefix_len) override;
  uint32_t getPort() const override;
  void setPort(uint32_t v) override;

 private:
  sockaddr_in6 m_addr;
};

class UnixAddress : public Address {
 public:
  using ptr = std::shared_ptr<UnixAddress>;

  UnixAddress();
  UnixAddress(const std::string& path);

  const sockaddr* getAddr() const override;
  socklen_t getAddrLen() const override;
  std::ostream& insert(std::ostream& os) const override;

 private:
  sockaddr_in m_addr;
  socklen_t m_length;
};

class UnknownAddress : public Address {
 public:
  using ptr = std::shared_ptr<UnknownAddress>;

  UnknownAddress(int family);
  UnknownAddress(const sockaddr& addr);

  const sockaddr* getAddr() const override;
  socklen_t getAddrLen() const override;
  std::ostream& insert(std::ostream& os) const override;

 private:
  sockaddr m_addr;
};

}  // namespace dunar

#endif  // DUNAR_ADDRESS_H
