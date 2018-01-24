#pragma once

#include<string>
#include<ostream>

class MessageBuffer
{
public:
   MessageBuffer() = default;
   MessageBuffer(std::string clientIP,std::string fileExtension);
   friend std::ostream& operator<< (std::ostream& out, MessageBuffer& message);
   friend std::istream& operator>> (std::istream& in, MessageBuffer& message);
   void setMainMessage(std::string mainMessage);
   void setInfected(short infected);
   void setInfectedOffset(short infectedOffset);
   void setPlugin(std::string plugin);
   std::string getFileExtension();

private:
   std::string m_clientIP;
   std::string m_fileExtension;
   std::string m_mainMessage;
   std::string m_plugin;
   short       m_infected;
   short       m_infectedOffset;


};