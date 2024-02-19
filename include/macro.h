//
// Created by spud on 24-2-4.
//

#ifndef DUNAR_MACRO_H
#define DUNAR_MACRO_H

#include "util.h"
#include <cassert>
#include <cstring>

#if defined __GNUC__ || defined __llvm__
#define DUNAR_LICKLY(x) __builtin_expect(!!(x), 1)
#define DUNAR_UNLICKLY(x) __builtin_expect(!!(x), 0)
#else
#define DUNAR_LICKLY(x) (x)
#define DUNAR_UNLICKLY(x) (x)
#endif

#define DUNAR_ASSERT(x)                              \
  if (DUNAR_UNLICKLY(!(x))) {                        \
    DUNAR_LOG_ERROR(DUNAR_LOG_ROOT())                \
        << "ASSERTION: " #x << "\nbacktrace:\n"      \
        << dunar::BacktraceToString(100, 2, "    "); \
    assert(x);                                       \
  }
/**
 *
 */
#define DUNAR_ASSERT2(x, w)                          \
  if (DUNAR_UNLICKLY(!(x))) {                        \
    DUNAR_LOG_ERROR(DUNAR_LOG_ROOT())                \
        << "ASSERTION: " #x << "\n"                  \
        << w << "\nbacktrace:\n"                     \
        << dunar::BacktraceToString(100, 2, "    "); \
    assert(x);                                       \
  }

#endif  // DUNAR_MACRO_H
