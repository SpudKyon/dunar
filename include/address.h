//
// Created by spud on 24-2-14.
//

#ifndef DUNAR_ADDRESS_H
#define DUNAR_ADDRESS_H

#include <arpa/inet.h>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include <vector>

namespace dunar {

class IPAddress;

class Address {
 public:
  using ptr = std::shared_ptr<Address>;

  static Address::ptr create(const sockaddr* addr, socklen_t addrlen);
  static bool lookup(std::vector<Address::ptr>& result, const std::string& host,
                     int family = AF_INET, int type = 0, int protocol = 0);
  static Address::ptr lookupAny(const std::string& host, int family = AF_INET,
                                int type = 0, int protocol = 0);
  static std::shared_ptr<IPAddress> lookupAnyIPAddress(const std::string& host,
                                                       int family = AF_INET,
                                                       int type = 0,
                                                       int protocol = 0);
  static bool getInterfaceAddresses(
      std::multimap<std::string, std::pair<Address::ptr, uint32_t>>& result,
      int family = AF_INET);
  static bool getInterfaceAddresses(
      std::vector<std::pair<Address::ptr, uint32_t>>& result,
      const std::string& iface, int family = AF_INET);

  virtual ~Address() {}

  int getFamily() const;
  virtual sockaddr* getAddr() = 0;
  virtual const sockaddr* getAddr() const = 0;
  virtual socklen_t getAddrLen() const = 0;

  virtual std::ostream& insert(std::ostream& os) const = 0;
  std::string toString() const;

  bool operator<(const Address& rhs) const;
  bool operator==(const Address& rhs) const;
  bool operator!=(const Address& rhs) const;
};

class IPAddress : public Address {
 public:
  using ptr = std::shared_ptr<IPAddress>;

  static IPAddress::ptr create(const char* address, uint16_t port = 0);

  virtual IPAddress::ptr broadcastAddress(uint32_t prefix_len) = 0;
  virtual IPAddress::ptr networdAddress(uint32_t prefix_len) = 0;
  virtual IPAddress::ptr subnetMask(uint32_t prefix_len) = 0;

  virtual uint32_t getPort() const = 0;
  virtual void setPort(uint16_t v) = 0;
};

class IPv4Address : public IPAddress {
 public:
  using ptr = std::shared_ptr<IPv4Address>;

  static IPv4Address::ptr create(const char* address, uint16_t port = 0);
  sockaddr* getAddr() override;
  IPv4Address(const sockaddr_in& address);
  IPv4Address(uint32_t address = INADDR_ANY, uint32_t port = 0);

  const sockaddr* getAddr() const override;
  socklen_t getAddrLen() const override;
  std::ostream& insert(std::ostream& os) const override;

  IPAddress::ptr broadcastAddress(uint32_t prefix_len) override;
  IPAddress::ptr networdAddress(uint32_t prefix_len) override;
  IPAddress::ptr subnetMask(uint32_t prefix_len) override;
  uint32_t getPort() const override;
  void setPort(uint16_t v) override;

 private:
  sockaddr_in m_addr;
};

class IPv6Address : public IPAddress {
 public:
  using ptr = std::shared_ptr<IPv6Address>;

  static IPv6Address::ptr create(const char* address, uint16_t port = 0);

  IPv6Address();
  IPv6Address(const sockaddr_in6& address);
  IPv6Address(const uint8_t address[16], uint16_t port = 0);

  const sockaddr* getAddr() const override;
  sockaddr* getAddr() override;
  socklen_t getAddrLen() const override;
  std::ostream& insert(std::ostream& os) const override;
  IPAddress::ptr broadcastAddress(uint32_t prefix_len) override;
  IPAddress::ptr networdAddress(uint32_t prefix_len) override;
  IPAddress::ptr subnetMask(uint32_t prefix_len) override;
  uint32_t getPort() const override;
  void setPort(uint16_t v) override;

 private:
  sockaddr_in6 m_addr;
};

class UnixAddress : public Address {
 public:
  using ptr = std::shared_ptr<UnixAddress>;

  UnixAddress();
  UnixAddress(const std::string& path);
  sockaddr* getAddr() override;
  void setAddrLen(uint32_t v);
  const sockaddr* getAddr() const override;
  socklen_t getAddrLen() const override;
  std::ostream& insert(std::ostream& os) const override;

 private:
  sockaddr_un m_addr;
  socklen_t m_length;
};

class UnknownAddress : public Address {
 public:
  using ptr = std::shared_ptr<UnknownAddress>;

  UnknownAddress(int family);
  UnknownAddress(const sockaddr& addr);

  sockaddr* getAddr() override;
  const sockaddr* getAddr() const override;
  socklen_t getAddrLen() const override;
  std::ostream& insert(std::ostream& os) const override;

  friend std::ostream& operator<<(std::ostream& os, const Address& addr);

 private:
  sockaddr m_addr;
};

}  // namespace dunar

#endif  // DUNAR_ADDRESS_H
