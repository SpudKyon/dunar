//
// Created by spud on 24-2-18.
//

#include "address.h"
#include "log.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

extern dunar::Logger::ptr test_logger;


TEST(TestAddress, TEST1) {
  std::vector<dunar::Address::ptr> addrs;

  DUNAR_LOG_INFO(test_logger) << "begin";
  bool v = dunar::Address::lookup(addrs, "www.dunar.top");
  DUNAR_LOG_INFO(test_logger) << "end";
  if (!v) {
    DUNAR_LOG_ERROR(test_logger) << "lookup fail";
    return;
  }

  for (size_t i = 0; i < addrs.size(); ++i) {
    DUNAR_LOG_INFO(test_logger) << i << " - " << addrs[i]->toString();
  }
}

TEST(TestAddress, IFACE) {
  std::multimap<std::string, std::pair<dunar::Address::ptr, uint32_t> > results;
  
  bool v = dunar::Address::getInterfaceAddresses(results);
  if(!v) {
    DUNAR_LOG_ERROR(test_logger) << "GetInterfaceAddresses fail";
    return;
  }

  for(auto& i: results) {
    DUNAR_LOG_INFO(test_logger) << i.first << " - " << i.second.first->toString() << " - "
                             << i.second.second;
  }
}

TEST(TestAddress, IPV4) {
  auto addr = dunar::IPAddress::create("127.0.0.8");
  if(addr) {
    DUNAR_LOG_INFO(test_logger) << addr->toString();
  }
}