#include "stdafx.h"
#include "MessageScanner.h"

MessageScanner::MessageScanner(size_t nrThreads):
   m_nrThreads(nrThreads)
{
   for (size_t i = 1; i <= m_nrThreads; ++i)
   {
      m_scannersPool.emplace_back([this] { doScan();/* maybe I should write the implace function and only to use this for accesingthe queueu*/ });
   }
}

void MessageScanner::doScan()
{
   // TO DO - must scan the message with all the plugins and decide if is infected or not
   // after that must add the messaje with the result in the scannedMessage queue.
}

void MessageScanner::addMessageToScan(MessageBuffer message)
{
   // TO DO check if the message comes from priority file 
 
   std::unique_lock<std::mutex> lock(m_scannedMessagesMutex);
   m_scannedMessages.push(message);
}