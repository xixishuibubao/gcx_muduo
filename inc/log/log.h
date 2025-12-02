#ifndef GCX_MUDUO_LOG_H
#define GCX_MUDUO_LOG_H

#include <timestamp/time_stamp.h>
#include <unordered_map>
#include <untils/noncopyable.h>

class Logger : noncopyable {

public:
  enum LogLevel {
    INFO,
    ERROR,
    FATAL,
    DEBUG,
  };

  static Logger &getInstance() {
    static Logger instance;
    return instance;
  }

  [[nodiscard]] LogLevel log_level() const { return log_level_; }
  void SetLogLevel(LogLevel log_level) { log_level_ = log_level; }
  void Log(const std::string &str) {
    std::cout << log_level_str_map_[log_level_];
    std::cout << TimeStamp().ToString() << ":";
    std::cout << str << std::endl;
  }

private:
  std::unordered_map<LogLevel, std::string> log_level_str_map_{
      {INFO, "[INFO] "},
      {ERROR, "[ERROR] "},
      {FATAL, "[FATAL] "},
      {DEBUG, "[DEBUG] "},
  };
  LogLevel log_level_;

private:
  Logger() : log_level_(INFO) {}
};

#endif // GCX_MUDUO_LOG_H
