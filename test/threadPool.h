#ifndef THREADPOOL_H
#define THREADPOOL_H

#include<iostream>
#include<vector>
#include<queue>
#include<memory>
#include<condition_variable>
#include<mutex>
#include<atomic>
#include<thread>
#include<functional>
#include<future>

class ThreadPool{
  public:
    ThreadPool(int size=std::thread::hardware_concurrency()):thread_pool_size_(size),stop_(false){
      for(int i=0;i<thread_pool_size_;++i){
        //threads_.push_back(std::thread(&ThreadPool::worker,this));
        threads_.emplace_back(
            [this](){
              this->worker();
            }
        );
      }
    }

    ~ThreadPool(){
      stop_=true;
      not_empty_cond_.notify_all();

      for(auto& thread:threads_){
        if(thread.joinable())
            thread.join();
      }
    }

    template<typename F,typename ...Args>
    auto submit(F&& f,Args&&... args) -> std::future<decltype(f(args...))> {
      using func_type=decltype(f(args...));
      //将任务函数包装成一个异步任务，但并不执行
      //之所以使用智能指针进行管理，是为了防止后续业务逻辑如何有对指针的操作从而造成不可避免的错误
      auto task_ptr=std::make_shared<std::packaged_task<func_type()>>(
          std::bind(std::forward<F>(f),std::forward<Args>(args)...)
        );
      std::future<func_type> func_future=task_ptr->get_future();
      
      {
        std::lock_guard<std::mutex>lock(mtx_);
        if(stop_)
          throw std::runtime_error("error: thread pool has stop!!!");
        task_queue_.emplace(
              [task_ptr](){
                (*task_ptr)();
              }
            );
      }
      not_empty_cond_.notify_one();

      return func_future;
    }

  private:
    std::atomic_bool stop_;
    std::atomic_int thread_pool_size_;

    using Task=std::function<void()>;
    std::vector<std::thread> threads_;
    std::queue<Task> task_queue_;
    std::mutex mtx_;
    std::condition_variable not_empty_cond_;

#if 1

    void worker() {
        while (true) {
            Task task;
            {
                std::unique_lock<std::mutex> lock(mtx_);
                
                not_empty_cond_.wait(lock, [this]() {
                    return stop_ || !task_queue_.empty();
                });

                if (stop_ && task_queue_.empty()) {
                    return;
                }

                task = task_queue_.front();
                task_queue_.pop();
            }

            std::cout << __TIME__ << " - Executing task..." << std::endl;
            task();
        }
    }

#endif
};

#endif//THREADPOOL_H
