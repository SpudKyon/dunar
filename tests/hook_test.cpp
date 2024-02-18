//
// Created by spud on 24-2-18.
//

#include "hook.h"
#include "iomanager.h"
#include "log.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

extern dunar::Logger::ptr test_logger;

TEST(HookTest, SLEEP) {
  dunar::IOManager iom(1);
  iom.schedule([]() {
    sleep(2);
    DUNAR_LOG_INFO(test_logger) << "sleep 2";
  });

  iom.schedule([]() {
    sleep(3);
    DUNAR_LOG_INFO(test_logger) << "sleep 3";
  });
  DUNAR_LOG_INFO(test_logger) << "test_sleep";
}

TEST(HookTest, SOCK) {
  int sock = socket(AF_INET, SOCK_STREAM, 0);

  sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(80);
  inet_pton(AF_INET, "115.239.210.27", &addr.sin_addr.s_addr);

  DUNAR_LOG_INFO(test_logger) << "begin connect";
  int rt = connect(sock, (const sockaddr*)&addr, sizeof(addr));
  DUNAR_LOG_INFO(test_logger) << "connect rt=" << rt << " errno=" << errno;

  if (rt) {
    return;
  }

  const char data[] = "GET / HTTP/1.0\r\n\r\n";
  rt = send(sock, data, sizeof(data), 0);
  DUNAR_LOG_INFO(test_logger) << "send rt=" << rt << " errno=" << errno;

  if (rt <= 0) {
    return;
  }

  std::string buff;
  buff.resize(4096);

  rt = recv(sock, &buff[0], buff.size(), 0);
  DUNAR_LOG_INFO(test_logger) << "recv rt=" << rt << " errno=" << errno;

  if (rt <= 0) {
    return;
  }

  buff.resize(rt);
  DUNAR_LOG_INFO(test_logger) << buff;
}