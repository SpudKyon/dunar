//
// Created by spud on 24-2-3.
//

#ifndef DUNAR_FIBER_H
#define DUNAR_FIBER_H

#include "thread.h"
#include <functional>
#include <memory>
#include <ucontext.h>

namespace dunar {

class Scheduler;

class Fiber : public std::enable_shared_from_this<Fiber> {
  friend class Scheduler;

 public:
  using ptr = std::shared_ptr<Fiber>;
  enum STATE { INIT, HOLD, EXEC, TERM, READY, EXCEPT };

 private:
  Fiber();

 public:
  Fiber(std::function<void()> cb, size_t stacksize = 0, bool use_caller = false);
  ~Fiber();

  // 重置协程函数，并重置状态
  // INIT，TERM
  void reset(std::function<void()> cb);
  // 切换到当前协程执行
  void swapIn();
  // 切换到后台执行
  void swapOut();
  void call();
  void back();

  uint64_t getId() const { return m_id; }
  STATE getState() const { return m_state; }

 public:
  // 设置当前协程
  static void SetThis(Fiber* f);
  // 返回当前协程
  static Fiber::ptr GetThis();
  // 协程切换到后台，并且设置为Ready状态
  static void YieldToReady();
  // 协程切换到后台，并且设置为Hold状态
  static void YieldToHold();
  // 总协程数
  static uint64_t TotalFibers();

  static void MainFunc();
  static void CallerMainFunc();
  static uint64_t GetFiberId();

 private:
  uint64_t m_id = 0;          // 协程id
  uint32_t m_stacksize = 0;   // 协程栈大小
  STATE m_state = INIT;       // 协程状态

  ucontext_t m_ctx;           // 协程上下文
  void* m_stack = nullptr;    // 协程栈指针

  std::function<void()> m_cb; // 协程执行函数
};
}  // namespace dunar

#endif  // DUNAR_FIBER_H
