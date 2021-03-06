// ServerSocket.cpp : Defines the entry point for the console application.


#include "stdafx.h"
#include "SocketConnection.h"
#include "MessagesToScan.h"
#include<thread>
#include<vector>
#include<condition_variable>
#include<mutex>



void Do_job()
{
   // fiecare thread trebuie sa aiba coada lui de mesaje si sa le proceseze 
   // fiecare thread trebuie sa aiba un socket cu care comunica cu clientul, 
   // Mesajele primite le baga in coada

   std::condition_variable condV;
   std::mutex mtx;
   std::unique_lock<std::mutex> lck(mtx);

   //while (!terminate)
   //{
    //  condV.wait(lck);
      
   //}
}

int main()
{
   int nrThread = 5;
   std::cout << "Nr optim este" << std::thread::hardware_concurrency()<< std::endl;
   std::vector<std::thread> threadPool;
   for (size_t i = 1; i <= nrThread; ++i)
   {
      threadPool.emplace_back(Do_job);
   }
   
   SOCKET client1;

   // Here is the starting point
   std::vector<std::string> priorities;
   priorities.emplace_back("bin");
   priorities.emplace_back("txt");
   auto messagesList = std::make_shared<MessagesToScan>(priorities);

   SocketConnection socketConnection(messagesList);
   socketConnection.startServer();
    
    return 0;
}

