#include "stdafx.h"
#include "MessageBuffer.h"

MessageBuffer::MessageBuffer(std::string clientIP, std::string fileExtension):
     m_clientIP(clientIP)
   , m_fileExtension(fileExtension)
{
}

void MessageBuffer::setMainMessage(std::string mainMessage)
{
   m_mainMessage = mainMessage;
}

void MessageBuffer::setInfected(short infected)
{
   m_infected = infected;
}

void MessageBuffer::setInfectedOffset(short infectedOffset)
{
   m_infectedOffset = infectedOffset;
}

void MessageBuffer::setPlugin(std::string plugin)
{
   m_plugin = plugin;
}

std::string MessageBuffer::getFileExtension()
{
   return m_fileExtension;
}

 std::ostream& operator<< (std::ostream& out, MessageBuffer& message) 
{
   out << message.m_clientIP << " " << message.m_fileExtension<<" "<<message.m_mainMessage; 
   return out;
}

std::istream& operator>> (std::istream& in, MessageBuffer& message) 
{
   in >> message.m_clientIP;
   in >> message.m_fileExtension;
   in >> message.m_infected;
   if (message.m_infected == 1)
   {
      in >> message.m_infectedOffset;
      in >> message.m_plugin;
   }
   return in;
}
