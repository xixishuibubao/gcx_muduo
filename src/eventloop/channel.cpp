#include <event_loop/channel.h>
#include <event_loop/even_tloop.h>

void Channel::UpdateEvent() {
  if (auto p =loop_.lock()) {
     //p->func();
  }
}