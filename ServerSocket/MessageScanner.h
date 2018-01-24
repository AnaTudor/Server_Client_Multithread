#pragma once
#include<vector>
#include<thread>
#include<queue>
#include<deque>
#include<mutex>
#include<condition_variable>
#include "MessageBuffer.h"

class MessageScanner
{
public:
   MessageScanner(size_t nrThreads);
   void addMessageToScan(MessageBuffer message); // check the priority
   

private :
   void doScan();

private:
   size_t m_nrThreads;
   std::mutex m_scannedMessagesMutex;
   std::vector<std::thread> m_scannersPool;
   std::queue<MessageBuffer> m_scannedMessages;
};