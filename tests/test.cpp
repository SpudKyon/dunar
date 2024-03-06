//
// Created by spud on 24-1-19.
//

#include "log.h"
#include <gtest/gtest.h>
#include <iostream>

dunar::Logger::ptr test_logger = DUNAR_LOG_NAME("test");

int main(int argc, char **argv) {
  if (false)  // make false to run unit-tests
  {
    // debug section

  } else {
    ::testing::InitGoogleTest(&argc, argv);
    std::cout << "RUNNING TESTS ..." << std::endl;
    int ret{RUN_ALL_TESTS()};
    if (!ret)
      std::cout << "<<<SUCCESS>>>" << std::endl;
    else
      std::cout << "FAILED" << std::endl;
  }
  return 0;
}