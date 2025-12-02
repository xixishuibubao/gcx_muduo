#ifndef GCX_MUDUO_EVEN_TLOOP_H
#define GCX_MUDUO_EVEN_TLOOP_H
#include <untils/noncopyable.h>
/*事件循环器，包含2层级模块，事件循环的本质就是epoll的循环，而epoll就是管理的通信链接(Channel)
 *
 */
class EventLoop : noncopyable {};

#endif // GCX_MUDUO_EVEN_TLOOP_H
