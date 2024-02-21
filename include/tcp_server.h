//
// Created by spud on 24-2-20.
//

#ifndef DUNAR_TCP_SERVER_H
#define DUNAR_TCP_SERVER_H

#include "address.h"
#include "iomanager.h"
#include "noncopyable.h"
#include "socket.h"
#include <functional>
#include <memory>

namespace dunar {

class TcpServer : public std::enable_shared_from_this<TcpServer>, Noncopyable {
 public:
  using ptr = std::shared_ptr<TcpServer>;

  TcpServer(dunar::IOManager* woker = dunar::IOManager::GetThis(),
            dunar::IOManager* accept_woker = dunar::IOManager::GetThis());
  virtual ~TcpServer();

  virtual bool bind(dunar::Address::ptr addr);
  virtual bool bind(const std::vector<Address::ptr>& addrs,
                    std::vector<Address::ptr>& fails);
  virtual bool start();
  virtual void stop();

  uint64_t getRecvTimeout() const { return m_recvTimeout; }
  std::string getName() const { return m_name; }
  void setRecvTimeout(uint64_t v) { m_recvTimeout = v; }
  void setName(const std::string& v) { m_name = v; }

  bool isStop() const { return m_isStop; }

 protected:
  virtual void handleClient(Socket::ptr client);
  virtual void startAccept(Socket::ptr sock);

 private:
  std::vector<Socket::ptr> m_socks;
  IOManager* m_worker;
  IOManager* m_acceptWorker;
  uint64_t m_recvTimeout;
  std::string m_name;
  bool m_isStop;
};

}  // namespace dunar

#endif  // DUNAR_TCP_SERVER_H
