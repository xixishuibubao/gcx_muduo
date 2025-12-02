#ifndef GCX_MUDUO_CHANNEL_H
#define GCX_MUDUO_CHANNEL_H

#include <functional>
#include <memory>
#include <sys/epoll.h>
#include <untils/noncopyable.h>
class TimeStamp;
class EventLoop;
/*
 * Channel即和客户端的链接，封装fd和epoll事件
 *
 */
class Channel : noncopyable {
public:
  using GeneralEventCbFunc = std::function<void()>;
  using ReadEventCbFunc = std::function<void(TimeStamp)>;

  Channel(const std::shared_ptr<EventLoop> &loop, int fd)
      : loop_(loop), fd_(fd), listen_events_(), recv_events_() {}
  ~Channel() {}

  int fd() const { return fd_; }
  int listen_event() const { return listen_events_; }
  void SetRecvEvent(int event) { recv_events_ = event; }

public:
  void SetReadCallback(ReadEventCbFunc func) { read_cb_ = std::move(func); }
  void SetWriteCallback(GeneralEventCbFunc func) {
    write_cb_ = std::move(func);
  }
  void SetCloseCallback(GeneralEventCbFunc func) {
    close_cb_ = std::move(func);
  }
  void SetErrorCallback(GeneralEventCbFunc func) {
    error_cb_ = std::move(func);
  }

  void EnableListenWriteEvent() {
    listen_events_ |= kWriteEvent;
    UpdateEvent();
  }
  void DisableListenWriteEvent() {
    listen_events_ &= ~kWriteEvent;
    UpdateEvent();
  }
  void EnableListenReadEvent() {
    listen_events_ |= kReadEvent;
    UpdateEvent();
  }
  void DisableListenReadEvent() {
    listen_events_ &= ~kReadEvent;
    UpdateEvent();
  }
  void DisableListenAllEvent() {
    listen_events_ &= ~kNoneEvent;
    UpdateEvent();
  }
  void UpdateEvent();

  bool IsReadEvent() const { return listen_events_ & kReadEvent; }
  bool IsWriteEvent() const { return listen_events_ & kWriteEvent; }
  bool IsNoneEvent() const { return listen_events_ == kNoneEvent; }

private:
  static constexpr int kNoneEvent{0};
  static constexpr int kReadEvent{EPOLLIN | EPOLLPRI};
  static constexpr int kWriteEvent{EPOLLOUT};

  std::weak_ptr<EventLoop> loop_;
  const int fd_;

  int listen_events_; /*监听的事件 */
  int recv_events_;   /* epoll返回的事件 */

  ReadEventCbFunc read_cb_;
  GeneralEventCbFunc write_cb_;
  GeneralEventCbFunc close_cb_;
  GeneralEventCbFunc error_cb_;
};

#endif // GCX_MUDUO_CHANNEL_H
