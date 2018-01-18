// ServerSocket.cpp : Defines the entry point for the console application.


#include "stdafx.h"
#include "SocketConnection.h"

int main()
{
   SocketConnection socketConnection;
   socketConnection.getServerInfo();
   socketConnection.createListenSocket();
   if (socketConnection.enableListening())
   {
      if (socketConnection.acceptClient())
      {
         std::string message;
         socketConnection.receiveMessage(message);
      }
   }

    socketConnection.closeSockets();
    return 0;
}

