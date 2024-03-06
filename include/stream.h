//
// Created by spud on 24-3-2.
//

#ifndef DUNAR_STREAM_H
#define DUNAR_STREAM_H

#include <memory>
#include "bytearray.h"

namespace dunar {

class Stream {
 public:
  using ptr = std::shared_ptr<Stream>;

  virtual ~Stream() = 0;
  virtual int read(void* buffer, size_t length) = 0;
  virtual int read(ByteArray::ptr ba, size_t length) = 0;
  virtual int readFixSize(void* buffer, size_t length);
  virtual int readFixSize(ByteArray::ptr ba, size_t length);
  virtual int write(const void* buffer, size_t length) = 0;
  virtual int write(ByteArray::ptr ba, size_t length) = 0;
  virtual int writeFixSize(const void* buffer, size_t length);
  virtual int writeFixSize(ByteArray::ptr ba, size_t length);
  virtual void close() = 0;
};
};  // namespace duanr

#endif  // DUNAR_STREAM_H
