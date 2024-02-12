//
// Created by spud on 24-1-19.
//

#include "util.h"
#include "fiber.h"
#include "log.h"
#include <execinfo.h>
#include <sys/time.h>

namespace dunar {

Logger::ptr g_logger = DUNAR_LOG_NAME("system");

pid_t GetThreadId() { return syscall(SYS_gettid); }

uint32_t GetFiberId() { return Fiber::GetFiberId(); }

void Backtrace(std::vector<std::string>& bt, int size, int skip) {
  void** array = (void**)malloc((sizeof(void*) * size));
  size_t s = ::backtrace(array, size);

  char** strings = backtrace_symbols(array, s);
  if (strings == nullptr) {
    DUNAR_LOG_ERROR(g_logger) << "backtrace_symbols error";
    return;
  }

  for (size_t i = skip; i < s; ++i) {
    bt.push_back(strings[i]);
  }

  free(strings);
  free(array);
}

std::string BacktraceToString(int size, int skip, const std::string& prefix) {
  std::vector<std::string> bt;
  Backtrace(bt, size, skip);
  std::stringstream ss;
  for (const auto& i : bt) {
    ss << prefix << i << std::endl;
  }
  return ss.str();
}

uint64_t GetCurrentMS() {
  struct timeval tv{};
  gettimeofday(&tv, nullptr);
  return tv.tv_sec * 1000ul + tv.tv_usec / 1000;
}

uint64_t GetCurrentUS() {
  struct timeval tv{};
  gettimeofday(&tv, nullptr);
  return tv.tv_sec * 1000 * 1000ul + tv.tv_usec;
}

}  // namespace dunar