#include "stdafx.h"
#include "SocketConnection.h"

SocketConnection::SocketConnection()
   : mListenSocket(INVALID_SOCKET)
   , mClientSocket(INVALID_SOCKET)
   , mResultInfo(nullptr)
{
   if (initializeSocket())
   {
      initializeSocketSpecific();
   }
}

bool SocketConnection::initializeSocket()
{
   int resultCode = WSAStartup(MAKEWORD(2, 2), &mWsaData);
   if (resultCode != 0)
   {
      std::cout << "WSAStartup failed with error code " << resultCode<<std::endl;
      return false;
   }
   return true;
}

void SocketConnection::initializeSocketSpecific()
{
   ZeroMemory(&mServerSpecific, sizeof(mServerSpecific));
   mServerSpecific.ai_family = AF_INET;
   mServerSpecific.ai_socktype = SOCK_STREAM;
   mServerSpecific.ai_protocol = IPPROTO_TCP;
   mServerSpecific.ai_flags = AI_PASSIVE;
}

bool SocketConnection::getServerInfo()
{
   int resultCode = getaddrinfo(NULL,mNrPort.c_str() , &mServerSpecific, &mResultInfo);
   if (resultCode != 0) 
   {
      std::cout << "getServerInfo failed with error code " << resultCode << std::endl;
      WSACleanup();
      return false;
   }
   return true;
}

bool SocketConnection::createListenSocket()
{
   mListenSocket = socket(mResultInfo->ai_family, mResultInfo->ai_socktype, mResultInfo->ai_protocol);
   if (mListenSocket == INVALID_SOCKET)
   {
      std::cout<<" Listen socket failed with error "<< WSAGetLastError()<<std::endl;
      freeaddrinfo(mResultInfo);
      WSACleanup();
      return false;
   }
   return true;
}

bool SocketConnection::enableListening()
{
   int resultCode = bind(mListenSocket, mResultInfo->ai_addr, static_cast<int>(mResultInfo->ai_addrlen));
   if (resultCode == SOCKET_ERROR) 
   {
      std::cout<<"bind failed with error " << WSAGetLastError() << std::endl;
      freeaddrinfo(mResultInfo);
      closesocket(mListenSocket);
      WSACleanup();
      return false;
   }

   freeaddrinfo(mResultInfo);

   resultCode = listen(mListenSocket, SOMAXCONN);
   if (resultCode == SOCKET_ERROR) 
   {
      std::cout << "Listening failed with error " << WSAGetLastError() << std::endl;
      closesocket(mListenSocket);
      WSACleanup();
      return false;
   }
   return true;
}

bool SocketConnection::acceptClient()
{
   mClientSocket = accept(mListenSocket, NULL, NULL);
   if (mClientSocket == INVALID_SOCKET) 
   {
      std::cout << "Accept client failed with error " << WSAGetLastError() << std::endl;
      closesocket(mListenSocket);
      WSACleanup();
      return false;
   }
   return true;
}

bool SocketConnection::receiveMessage(std::string &message)
{
   char messageBuffer[mBufferLength];
   int resultCode = recv(mClientSocket, messageBuffer, mBufferLength, 0);
   if (resultCode > 0) 
   {
      std::cout<<"Bytes received: "<< resultCode<<std::endl;

      // Echo the buffer back to the sender
      int sendResultCode = send(mClientSocket, messageBuffer, resultCode, 0);
      if (sendResultCode == SOCKET_ERROR) 
      {
         std::cout<<"send failed with error: "<< WSAGetLastError()<<std::endl;
         closesocket(mClientSocket);
         WSACleanup();
         return false;
      }
      std::cout<<"Bytes sent: "<< sendResultCode<<std::endl;
   }
   else if (resultCode == 0)
      std::cout<<"Connection closing...\n"<<std::endl;
   else 
   {
      std::cout<<"receiving failed with error:"<< WSAGetLastError();
      closesocket(mClientSocket);
      WSACleanup();
      return false;
   }
   return true;
}

bool SocketConnection::closeSockets()
{
   closesocket(mListenSocket);
   int resultCode = shutdown(mClientSocket, SD_SEND);
   if (resultCode == SOCKET_ERROR)
   {
      std::cout<<"shutdown failed with error: "<< WSAGetLastError()<<std::endl;
      closesocket(mClientSocket);
      WSACleanup();
      return false;
   }

   // cleanup
   closesocket(mClientSocket);
   WSACleanup();

   return true;
}