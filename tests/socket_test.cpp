//
// Created by spud on 24-2-19.
//

#include "iomanager.h"
#include "log.h"
#include "socket.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

extern dunar::Logger::ptr test_logger;

TEST(TestSocket, TEST1) {
  // std::vector<dunar::Address::ptr> addrs;
  // dunar::Address::Lookup(addrs, "www.baidu.com", AF_INET);
  // dunar::IPAddress::ptr addr;
  // for(auto& i : addrs) {
  //     DUNAR_LOG_INFO(test_logger) << i->toString();
  //     addr = std::dynamic_pointer_cast<dunar::IPAddress>(i);
  //     if(addr) {
  //         break;
  //     }
  // }
  dunar::IPAddress::ptr addr =
      dunar::Address::lookupAnyIPAddress("www.baidu.com");
  if (addr) {
    DUNAR_LOG_INFO(test_logger) << "get address: " << addr->toString();
  } else {
    DUNAR_LOG_ERROR(test_logger) << "get address fail";
    return;
  }

  dunar::Socket::ptr sock = dunar::Socket::CreateTCP(addr);
  addr->setPort(80);
  DUNAR_LOG_INFO(test_logger) << "addr=" << addr->toString();
  if (!sock->connect(addr)) {
    DUNAR_LOG_ERROR(test_logger) << "connect " << addr->toString() << " fail";
    return;
  } else {
    DUNAR_LOG_INFO(test_logger)
        << "connect " << addr->toString() << " connected";
  }

  const char buff[] = "GET / HTTP/1.0\r\n\r\n";
  int rt = sock->send(buff, sizeof(buff));
  if (rt <= 0) {
    DUNAR_LOG_INFO(test_logger) << "send fail rt=" << rt;
    return;
  }

  std::string buffs;
  buffs.resize(4096);
  rt = sock->recv(&buffs[0], buffs.size());

  if (rt <= 0) {
    DUNAR_LOG_INFO(test_logger) << "recv fail rt=" << rt;
    return;
  }

  buffs.resize(rt);
  DUNAR_LOG_INFO(test_logger) << buffs;
}
