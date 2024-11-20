#include<iostream>
#include "threadPool.h"

int add(const int& num1,const int& num2){
  return num1+num2;
}

int main(){
  ThreadPool pool;
  auto task1=pool.Submit(add,1,2);
  auto task2=pool.Submit(add,3,4);
  int sum=task1.get()+task2.get();
  std::cout<<"sum="<<sum<<std::endl;

  return 0;
}
