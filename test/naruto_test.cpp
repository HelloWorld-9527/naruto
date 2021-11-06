#include "async_file_appender.h"
#include "log.h"
#include "log_appender_interface.h"
#include "log_config.h"
#include "gtest/gtest.h"
#include <chrono>
#include <iostream>

TEST(Benchmarks, append) {
  LogConfig log_config;
  // 1. 设置配置
  hardcode::naruto::Logger::setGlobalConfig(log_config);
  // 2. 注册异步日志
  hardcode::naruto::Logger::getLogger()->addAppender(
      "asyncfile", LogAppenderInterface::Ptr(new AsyncFileAppender("./lg/")));
  // 即新建一个 AsyncFileAppender对象，添加到Logger的一个map中：appenders_，
  // 其中 appenders_["asyncfile"] = 对象 AsyncFileAppender("./lg/") 的指针(智能指针)


  const int32_t count = 100000;
  auto start = std::chrono::system_clock::now(); // 开始计时
  for (int32_t index = 0; index < count; ++index) {
    hardcode::naruto::Logger::getLogger()->fatal("%d hello world", index);
  }
  auto end = std::chrono::system_clock::now(); // 结束计时
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start); // 耗时
  std::cout << count << "次运行耗时" << duration.count() << "us" << std::endl;
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
