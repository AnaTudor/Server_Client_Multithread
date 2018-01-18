#pragma once
/*
#include<string>
#include <winsock2.h>
#include <ws2tcpip.h>
*/
class SocketConnection
{
public:
   SocketConnection();
   bool initializeSocket();
   void initializeSocketSpecific();
   bool getServerInfo();
   bool createListenSocket();
   bool enableListening();
   bool acceptClient();
   bool receiveMessage(std::string &message);
   bool closeSockets();

private:
   const std::string mNrPort = "27015";
   constexpr static unsigned int mBufferLength = 512;
   WSADATA   mWsaData;
   SOCKET    mListenSocket;
   SOCKET    mClientSocket;
   addrinfo* mResultInfo;
   addrinfo  mServerSpecific;


};