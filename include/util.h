//
// Created by spud on 24-1-19.
//

#ifndef DUNAR_UTIL_H
#define DUNAR_UTIL_H

#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

namespace dunar {

pid_t GetThreadId();
uint32_t GetFiberId();

}  // namespace dunar

#endif  // DUNAR_UTIL_H
