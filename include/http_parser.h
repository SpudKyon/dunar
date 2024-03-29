#ifndef DUNAR_HTTP_PARSER_H_
#define DUNAR_HTTP_PARSER_H_

#include "http.h"
#include "http11_parser.h"
#include "httpclient_parser.h"

namespace dunar::http {

class HttpRequestParser {
 public:
  using ptr = std::shared_ptr<HttpRequestParser>;
  HttpRequestParser();
  size_t execute(char* data, size_t len);
  int isFinished();
  int hasError();

  HttpRequest::ptr getData() const { return m_data; }
  void setError(int v) { m_error = v; }

  uint64_t getContentLength();

 private:
  http_parser m_parser;
  HttpRequest::ptr m_data;
  // 1000: invalid method
  // 1001: invalid version
  // 1002: invalid field
  int m_error;
};

class HttpResponseParser {
 public:
  typedef std::shared_ptr<HttpResponseParser> ptr;
  HttpResponseParser();
  size_t execute(char* data, size_t len);
  int isFinished();
  int hasError();

  HttpResponse::ptr getData() const { return m_data; }
  void setError(int v) { m_error = v; }

  uint64_t getContentLength();

 private:
  httpclient_parser m_parser;
  HttpResponse::ptr m_data;
  // 1001: invalid version
  // 1002: invalid field
  int m_error;
};

}  // namespace dunar::http

#endif
