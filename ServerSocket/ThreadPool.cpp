#include "stdafx.h"
#include"ThreadPool.h"

ThreadPool::ThreadPool(size_t nrThreads)
   : mNrThreads(nrThreads)
   , mStop(false)
{
}

void ThreadPool::addTask(std::function<void()> task)
{
   std::unique_lock<std::mutex> lock(mMutex);
   mTasks.emplace(task);
   mConditionVariable.notify_one();
}

void ThreadPool::startProcessing()
{
   for (size_t i = 0; i < mNrThreads; ++i)
   {
      mThreadPool.emplace_back([this]()
      {
         while (true)
         {
            std::function<void()> task;

            {
               std::unique_lock<std::mutex> lock(this->mMutex);
               this->mConditionVariable.wait(lock, [this] 
               {
                  return this->mStop || !this->mTasks.empty();
               });

               if (this->mStop && this->mTasks.empty())
                  return;

               task = std::move(this->mTasks.front());
               this->mTasks.pop();
            }

            task();
         }
      });
   }
}

ThreadPool::~ThreadPool()
{
   {
      std::unique_lock<std::mutex> lock(mMutex);
      mStop = true;
   }
   mConditionVariable.notify_all();
   for (std::thread &worker : mThreadPool)
   {
      worker.join();
   }
}