#include "safeQueue.h"
#include<vector>
#include<mutex>
#include<thread>
#include<future>
#include<utility>
#include<memory>
#include<functional>
#include<atomic>
#include<iostream>
class ThreadPool
{
public:
  //初始化线程池大小，并设置线程池的关闭标记为false
  ThreadPool(size_t size=std::thread::hardware_concurrency())
            :_threads(size),_shutdown(false)
            {}
  //析构函数，关闭线程池
  ~ThreadPool(){
    shutdown();
  }
  //初始化线程池
  void init()
  {
    std::lock_guard<std::mutex> lock(_mutexPool);
    for(int i=0;i<_threads.size();++i)
      _threads[i]=std::thread(&ThreadPool::threadWork,this,i);
  }

  //任务提交函数
  template<typename F,typename... Args>
  auto submit(F&& f,Args&&... args) -> std::future<decltype(f(args...))>
  {
    using retType=decltype(f(args...));
    std::function<retType()> function=std::bind(std::forward<F>(f),std::forward<Args>(args)...);
    auto task_ptr=std::make_shared<std::packaged_task<retType()>>(function);
    std::future<retType> future=task_ptr->get_future();
    Task wrapper_ptr=[task_ptr](){
      (*task_ptr)();
    };
    _taskQ.push(wrapper_ptr);
    _condLock.notify_one();
    return future;
  }

  //线程工作函数
  void threadWork(int id){
    while(!_shutdown){
      std::unique_lock<std::mutex> lock(_mutexPool);
      if(_taskQ.empty()){
        _condLock.wait(lock);
      }
      Task task;
      bool is_task=_taskQ.pop(std::ref(task));
      if(is_task)
        task();
    }
  }

  //关闭线程池
  bool shutdown()
  {
    _shutdown=true;
    _condLock.notify_all();
    for(auto& thread:_threads)
    {
      if(thread.joinable())
      {
        std::cout<<"join thread "<<std::this_thread::get_id()<<std::endl;
        thread.join();
      }
    }
  }
private:
  using Task=std::function<void()>;
  std::vector<std::thread> _threads;
  SafeQueue<Task> _taskQ;
  std::mutex _mutexPool;
  std::condition_variable _condLock;
  std::atomic<bool> _shutdown;
};