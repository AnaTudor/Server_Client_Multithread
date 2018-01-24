#pragma once
#include<deque>
#include<mutex>
#include<vector>
#include"MessageBuffer.h"

class MessagesToScan
{
public:
   MessagesToScan() = default;
   MessagesToScan(std::vector<std::string> priorityFiles);
   void addMessage(MessageBuffer message);
   MessageBuffer popMessage();
   bool isEmpty();
private:
   std::deque<MessageBuffer> m_messages;
   std::mutex m_mutex;
   std::vector<std::string> m_priorityFiles;
};