//
// Created by spud on 24-2-14.
//

#ifndef DUNAR_NONCOPYABLE_H
#define DUNAR_NONCOPYABLE_H

namespace dunar {

class Noncopyable {
 public:
  Noncopyable() = default;
  ~Noncopyable() = default;
  Noncopyable(const Noncopyable&) = delete;
  Noncopyable& operator=(const Noncopyable&) = delete;
};
}  // namespace dunar

#endif  // DUNAR_NONCOPYABLE_H
