//
// Created by spud on 24-2-4.
//

#ifndef DUNAR_MACRO_H
#define DUNAR_MACRO_H

#include <string.h>
#include <assert.h>
#include "util.h"

#define DUNAR_ASSERT(x)                              \
  if (!(x)) {                                        \
    DUNAR_LOG_ERROR(DUNAR_LOG_ROOT())                \
        << "ASSERTION: " #x << "\nbacktrace:\n"      \
        << dunar::BacktraceToString(100, 2, "    "); \
    assert(x);                                       \
  }

#define DUNAR_ASSERT2(x, w)                          \
  if (!(x)) {                                        \
    DUNAR_LOG_ERROR(DUNAR_LOG_ROOT())                \
        << "ASSERTION: " #x << "\n"                  \
        << w << "\nbacktrace:\n"                     \
        << dunar::BacktraceToString(100, 2, "    "); \
    assert(x);                                       \
  }

#endif  // DUNAR_MACRO_H
