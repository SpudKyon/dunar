//
// Created by spud on 24-3-2.
//

#ifndef DUNAR_SOCKET_STREAM_H
#define DUNAR_SOCKET_STREAM_H

#include "socket.h"
#include "stream.h"

namespace dunar {

class SocketStream : public Stream {
 public:
  using ptr = std::shared_ptr<SocketStream>;

  SocketStream(Socket::ptr sock, bool owner = true);
  ~SocketStream();

  virtual int read(void* buffer, size_t length) override;
  virtual int read(ByteArray::ptr ba, size_t length) override;
  virtual int write(const void* buffer, size_t length) override;
  virtual int write(ByteArray::ptr ba, size_t length) override;
  virtual void close() override;

  Socket::ptr getSocket() const { return m_socket; }
  bool isConnected() const;

 protected:
  Socket::ptr m_socket;
  bool m_owner;
};
}  // namespace dunar

#endif  // DUNAR_SOCKET_STREAM_H
