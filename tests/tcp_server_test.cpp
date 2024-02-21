//
// Created by spud on 24-2-21.
//

#include "address.h"
#include "http.h"
#include "http_parser.h"
#include "log.h"
#include "tcp_server.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

extern dunar::Logger::ptr test_logger;

void run() {
  auto addr = dunar::Address::lookupAny("0.0.0.0:8033");
  // auto addr2 = dunar::UnixAddress::ptr(new
  // dunar::UnixAddress("/tmp/unix_addr"));
  std::vector<dunar::Address::ptr> addrs;
  addrs.push_back(addr);
  // addrs.push_back(addr2);

  dunar::TcpServer::ptr tcp_server(new dunar::TcpServer);
  std::vector<dunar::Address::ptr> fails;
  while (!tcp_server->bind(addrs, fails)) {
    sleep(2);
  }
  tcp_server->start();
}
