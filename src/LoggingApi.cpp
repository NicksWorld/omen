#include "LoggingApi.h"

#include <format>
#include <iostream>
#include <mutex>
#include <string>

void Omen::LoggingApi::log(LogLevel level, const std::string &msg) {
  std::string levelStr;
  switch (level) {
  case LogLevel::DEBUG:
    levelStr = "DEBUG";
    break;
  case LogLevel::INFO:
    levelStr = "INFO";
    break;
  case LogLevel::WARN:
    levelStr = "WARN";
    break;
  case LogLevel::ERROR:
    levelStr = "ERROR";
    break;
  case LogLevel::CRITICAL:
    levelStr = "CRITICAL";
    break;
  }

  // Prevent multiple threads from logging at the same time
  const std::scoped_lock lck(m_lock);
  std::cout << std::format("[{}] {}\n", levelStr, msg);
}
