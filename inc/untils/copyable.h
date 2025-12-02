
#ifndef GCX_MUDUO_COPYABLE_H
#define GCX_MUDUO_COPYABLE_H
class copyable {
public:
  copyable() = default;
  ~copyable() = default;

  copyable(const copyable &) = default;
  copyable &operator=(const copyable &) = default;
};

#endif // GCX_MUDUO_COPYABLE_H
