#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <mutex>  
#include <thread> 
#include <condition_variable>
#include <functional>

class ThreadPool
{
public:
    //线程池任务类型
    typedef std::function<void()> Task;

    ThreadPool(int threadnum = 0);
    ~ThreadPool();

    //启动线程池
    void Start();

    //暂停线程池
    void Stop();

    //添加任务
    void AddTask(Task task);

    //线程池执行的函数
    void ThreadFunc();

    //获取线程数量
    int GetThreadNum()
    { return threadnum_; }

private:
    //运行状态
    bool started_;

    //线程数量
    int threadnum_;

    //线程列表
    std::vector<std::thread*> threadlist_;

    //任务队列
    std::queue<Task> taskqueue_;

    //任务队列互斥量
    std::mutex mutex_;

    //任务队列同步的条件变量
    std::condition_variable condition_;
};
