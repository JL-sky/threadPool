// safequeue.h
#ifndef SAFEQUEUE_H
#define SAFEQUEUE_H

#include <mutex>
#include <queue>
#include <stdexcept>

template <typename E>
class Queue {
 public:
    Queue() = default; // 在此定义默认构造函数

    void Enqueue(const E &element) {
        std::lock_guard<std::mutex> lock(mtx_);
        queue_.emplace(element);
    }

    E Dequeue() {
        std::lock_guard<std::mutex> lock(mtx_);
        if (!queue_.empty()) {
            E data = queue_.front();
            queue_.pop();
            return data;
        }
        throw std::runtime_error("Queue is empty");
    }

    size_t size() const { return queue_.size(); }

 private:
    std::queue<E> queue_;
    std::mutex mtx_;
};

#endif // SAFEQUEUE_H