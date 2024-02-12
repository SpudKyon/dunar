//
// Created by spud on 24-1-19.
//

#ifndef DUNAR_UTIL_H
#define DUNAR_UTIL_H

#include "log.h"
#include <cstdint>
#include <cstdio>
#include <pthread.h>
#include <string>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

namespace dunar {

pid_t GetThreadId();
uint32_t GetFiberId();
void Backtrace(std::vector<std::string>& bt, int size = 64, int skip = 1);
std::string BacktraceToString(int size = 64, int skip = 2, const std::string& prefix = "");
uint64_t GetCurrentMS();
uint64_t GetCurrentUS();
}  // namespace dunar

#endif  // DUNAR_UTIL_H
