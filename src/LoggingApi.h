#pragma once

#include <cstdint>
#include <mutex>
#include <string>

namespace Omen {
  class ComponentLocator;

  /// Log verbosity levels, used for filtering which messages to display
  enum class LogLevel : std::uint8_t { DEBUG, INFO, WARN, ERROR, CRITICAL };

  /// Provides a basic thread-safe logging API
  class LoggingApi {
  public:
    LoggingApi() = default;
    ~LoggingApi() = default;

    /// Log a message to the console with the given log level and message.
    void log(LogLevel level, const std::string &msg);

  private:
    // Used to ensure only one thread is outputting to stdout at a time.
    std::mutex m_lock;
  };
} // namespace Omen
