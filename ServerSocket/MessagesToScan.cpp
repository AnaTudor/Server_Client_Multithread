#include "stdafx.h"
#include "MessagesToScan.h"

MessagesToScan::MessagesToScan(std::vector<std::string> priorityFiles):
   m_priorityFiles(priorityFiles)
{}

void MessagesToScan::addMessage(MessageBuffer message)
{
   bool hasPriority = false;
   for (size_t i = 0; i < m_priorityFiles.size(); ++i)
   {
      if (message.getFileExtension() == m_priorityFiles[i])
      {
         hasPriority = true;
         break;
      }
   }

   if (hasPriority)
   {
      std::unique_lock<std::mutex> lock(m_mutex);
      m_messages.push_back(message);
   }
   else
   {
      std::unique_lock<std::mutex> lock(m_mutex);
      m_messages.push_front(message);
   }
}

bool MessagesToScan::isEmpty()
{
   std::unique_lock<std::mutex> lock(m_mutex);
   if (m_messages.empty())
      return true;
   else 
      return false;
}

MessageBuffer MessagesToScan::popMessage()
{
   MessageBuffer message;
   {
      std::unique_lock<std::mutex> lock(m_mutex);
      message = std::move(m_messages.back());
      m_messages.pop_back();
   }
   return message;
}
