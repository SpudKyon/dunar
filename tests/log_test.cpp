//
// Created by spud on 24-1-19.
//
#include "log.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(LogTest, TEST1) {
  dunar::Logger::ptr logger(new dunar::Logger);
  logger->addAppender(dunar::LogAppender::ptr(new dunar::StdoutLogAppender));

  // std log
  std::cout << "std log" << std::endl;
  DUNAR_LOG_DEBUG(logger) << "debug";
  DUNAR_LOG_INFO(logger) << "info";
  DUNAR_LOG_WARN(logger) << "warn";
  DUNAR_LOG_ERROR(logger) << "error";
  DUNAR_LOG_FATAL(logger) << "fatal";

  dunar::FileLogAppender::ptr file_appender(
      new dunar::FileLogAppender("./log.txt"));
  dunar::LogFormatter::ptr fmt(new dunar::LogFormatter("%d%T%p%T%m%n"));
  file_appender->setFormatter(fmt);
  file_appender->setLevel(dunar::LogLevel::DEBUG);

  logger->addAppender(file_appender);

  // file log
  DUNAR_LOG_DEBUG(logger) << "debug";
  DUNAR_LOG_INFO(logger) << "info";
  DUNAR_LOG_WARN(logger) << "warn";
  DUNAR_LOG_ERROR(logger) << "error";
  DUNAR_LOG_FATAL(logger) << "fatal";

  DUNAR_LOG_FMT_ERROR(logger, "test macro fmt error %s", "aa");

  auto l = dunar::LoggerMgr::GetInstance()->getLogger("xx");
  DUNAR_LOG_INFO(l) << "xxx";
}