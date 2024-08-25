#include"./threadpool.h"

int add(int begin,int end)
{
    int sum=0;
    for(int i=begin;i<end;i++)
        sum+=i;
    return sum;
}

void test()
{
    ThreadPool pool;
    pool.start();
    std::future<int> future1=pool.submitTask(add,1,1000);
    std::future<int> future2=pool.submitTask(add,1001,2000);
    std::future<int> future3=pool.submitTask(add,2001,3000);
    int sum1=future1.get();
    int sum2=future2.get();
    int sum3=future3.get();
    int sum=sum1+sum2+sum3;
    std::cout<<"sum="<<sum<<std::endl;
}

int main()
{
    test();
    return 1;
}