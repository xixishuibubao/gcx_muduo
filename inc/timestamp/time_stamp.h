#ifndef GCX_MUDUO_TIME_STAMP_H
#define GCX_MUDUO_TIME_STAMP_H
#include <chrono>
#include <string>
class TimeStamp {
public:
  explicit TimeStamp(std::chrono::system_clock::time_point time)
      : time_(time) {}
  TimeStamp() : time_(std::chrono::system_clock::now()) {}
  static TimeStamp now() { return TimeStamp{}; }
  [[nodiscard]] std::string ToString() const {
    std::time_t now_ = std::chrono::system_clock::to_time_t(time_);
    char buf[64]{};
    std::strftime(buf, 64, "%Y-%m-%d %H:%M:%S", std::localtime(&now_));
    return buf;
  }

private:
  std::chrono::system_clock::time_point time_;
};

#endif // GCX_MUDUO_TIME_STAMP_H
