#ifndef SAFEQUEUE_H
#define SAFEQUEUE_H
#include<mutex>
#include<queue>

template<typename T>
class SafeQueue{
public:

  bool push(T& elm)
  {
    std::lock_guard<std::mutex> lock(_mutex);
    _queue.push(elm);
    return true;
  }

  bool pop(T& elm)
  {
    std::lock_guard<std::mutex> lock(_mutex);
    if(_queue.empty())
      return false;
    elm=_queue.front();
    _queue.pop();
    return true;
  }

  size_t size() const
  {
    return _queue.size();
  }

  bool empty() const
  {
    return _queue.empty();
  }

private:
  std::queue<T> _queue;
  std::mutex _mutex;
};
#endif