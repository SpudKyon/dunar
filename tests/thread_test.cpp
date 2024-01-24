//
// Created by spud on 24-1-24.
//

#include "config.h"
#include "log.h"
#include "thread.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

dunar::Logger::ptr g_logger = DUNAR_LOG_ROOT();

void fun1() {
  DUNAR_LOG_INFO(g_logger) << "name: " << dunar::Thread::GetName()
                           << " this.name: "
                           << dunar::Thread::GetThis()->getName()
                           << " id: " << dunar::GetThreadId()
                           << " this.id: " << dunar::Thread::GetThis()->getId();
  sleep(20);
}

void fun2() {}

TEST(ThreadTest, TEST1) {
  DUNAR_LOG_INFO(g_logger) << "thread test begin";
  std::vector<dunar::Thread::ptr> thrs;
  for (int i = 0; i < 5; ++i) {
    dunar::Thread::ptr thr(
        new dunar::Thread(&fun1, "name_" + std::to_string(i)));
    thrs.push_back(thr);
  }

  for (int i = 0; i < 5; ++i) {
    thrs[i]->join();
  }
  DUNAR_LOG_INFO(g_logger) << "thread test end";
}