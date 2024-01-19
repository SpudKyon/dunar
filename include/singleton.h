//
// Created by spud on 24-1-19.
//

#ifndef DUNAR_SINGLETON_H
#define DUNAR_SINGLETON_H

#include <memory>
namespace dunar {

template <class T, class X = void, int N = 0>
class Singleton {
 public:
  static T* GetInstance() {
    static T v;
    return &v;
  }
};

template <class T, class X = void, int N = 0>
class SingletonPtr {
 public:
  static std::shared_ptr<T> GetInstance() {
    static std::shared_ptr<T> v(new T);
    return v;
  }
};

}  // namespace dunar

#endif  // DUNAR_SINGLETON_H
