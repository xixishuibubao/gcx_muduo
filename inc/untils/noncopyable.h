#ifndef GCX_MUDUO_NONCOPYABLE_H
#define GCX_MUDUO_NONCOPYABLE_H

class noncopyable {
protected:
  noncopyable() = default;
  ~noncopyable() = default;

  noncopyable(const noncopyable &) = delete;
  noncopyable &operator=(const noncopyable &) = delete;
};

#endif // GCX_MUDUO_NONCOPYABLE_H
