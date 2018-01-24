#pragma once

#include<mutex>
#include<condition_variable>
#include<vector>
#include<functional>
#include<thread>
#include<queue>

class ThreadPool
{
public:
   ThreadPool(size_t nrThread = 5);
   void addTask(std::function<void()> task);
   void startProcessing();
   ~ThreadPool();
private:
   size_t mNrThreads;
   std::mutex mMutex;
   bool mStop;
   std::condition_variable mConditionVariable;
   std::vector<std::thread> mThreadPool;
   std::queue <std::function<void()>> mTasks;
};
