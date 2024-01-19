//
// Created by spud on 24-1-19.
//

#include "util.h"

namespace dunar {
pid_t GetThreadId() { return syscall(SYS_gettid); }

uint32_t GetFiberId() { return 0; }

}  // namespace dunar