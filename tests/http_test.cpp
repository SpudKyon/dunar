//
// Created by spud on 24-2-21.
//

#include "http.h"
#include "log.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

extern dunar::Logger::ptr test_logger;

TEST(TestHttp, TEST_REQUEST) {
  dunar::http::HttpRequest::ptr req(new dunar::http::HttpRequest);
  req->setHeader("host", "www.dunar.top");
  req->setBody("hello dunar");
  req->dump(std::cout) << std::endl;
}

TEST(TestHttp, TEST_RESPONSE) {
  dunar::http::HttpResponse::ptr rsp(new dunar::http::HttpResponse);
  rsp->setHeader("X-X", "dunar");
  rsp->setBody("hello dunar");
  rsp->setStatus((dunar::http::HttpStatus)400);
  rsp->setClose(false);

  rsp->dump(std::cout) << std::endl;
}