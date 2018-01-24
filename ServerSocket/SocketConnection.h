#pragma once
/*
#include<string>
#include <winsock2.h>
#include <ws2tcpip.h>
*/
#include "MessagesToScan.h"
#include "ThreadPool.h"
#include<mutex>

class SocketConnection
{
public:
   SocketConnection(std::weak_ptr<MessagesToScan> messagesToScanPtr);
   void startServer();
private:
   bool initializeSocket();
   void initializeSocketSpecific();
   bool getServerInfo();
   bool createListenSocket();
   bool enableListening();
   bool acceptClient();
   bool receiveMessage(MessageBuffer& message, SOCKET& clientSocket);
   bool sendMessage(MessageBuffer message, SOCKET& clientSocket);
   bool closeSockets();
  

private:
   const std::string mNrPort = "27015";
   constexpr static size_t mBufferLength = 512;
   const size_t mNrThreads = 5;
   WSADATA   mWsaData;
   SOCKET    mListenSocket;
   SOCKET    mClientSocket;
   addrinfo* mResultInfo;
   addrinfo  mServerSpecific;
   std::weak_ptr<MessagesToScan> mMessageToScanPtr;
   ThreadPool mThreadPool;
};