//
// Created by spud on 24-2-7.
//

#include <memory>

#include "fiber.h"
#include "log.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

dunar::Logger::ptr fiber_logger = DUNAR_LOG_ROOT();

void run_in_fiber() {
  DUNAR_LOG_INFO(fiber_logger) << "run_in_fiber begin";
  dunar::Fiber::YieldToHold();
  DUNAR_LOG_INFO(fiber_logger) << "run_in_fiber end";
  dunar::Fiber::YieldToHold();
}

void test_fiber() {
  DUNAR_LOG_INFO(fiber_logger) << "main begin -1";
  {
    dunar::Fiber::GetThis();
    DUNAR_LOG_INFO(fiber_logger) << "main begin";
    dunar::Fiber::ptr fiber(new dunar::Fiber(run_in_fiber));
    fiber->swapIn();
    DUNAR_LOG_INFO(fiber_logger) << "main after swapIn";
    fiber->swapIn();
    DUNAR_LOG_INFO(fiber_logger) << "main after end";
    fiber->swapIn();
  }
  DUNAR_LOG_INFO(fiber_logger) << "main after end2";
}

TEST(FiberTest, TestRun) {
  dunar::Thread::SetName("main");

  std::vector<dunar::Thread::ptr> thrs;
  for (int i = 0; i < 3; ++i) {
    thrs.push_back(std::make_shared<dunar::Thread>(
        &test_fiber, "name_" + std::to_string(i)));
  }
  for (const auto& i : thrs) {
    i->join();
  }
}