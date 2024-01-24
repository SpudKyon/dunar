//
// Created by spud on 24-1-24.
//

#ifndef DUNAR_THREAD_H
#define DUNAR_THREAD_H

#include <functional>
#include <memory>
#include <string>
namespace dunar {

class Thread {
 public:
  using ptr = std::shared_ptr<Thread>;
  Thread(std::function<void()> cb, const std::string& name);
  ~Thread();

  pid_t getId() const { return m_id; }
  const std::string& getName() const { return m_name; }

  void join();

  static Thread* GetThis();
  static const std::string& GetName();
  static void SetName(const std::string& name);

 private:
  Thread(const Thread&) = delete;
  Thread(const Thread&&) = delete;
  Thread& operator=(const Thread&) = delete;

  static void* run(void* arg);

 private:
  pid_t m_id = -1;
  pthread_t m_thread = 0;
  std::function<void()> m_cb;
  std::string m_name;
};

}  // namespace dunar

#endif  // DUNAR_THREAD_H
