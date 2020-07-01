#include "file_handler.hpp"
#include <iostream>
#include "IReader.hpp"
#include "Itransformer.hpp"
#include "encoder.hpp"
#include "client_net.hpp"
#include "threads.hpp"
#include "exeption.hpp"

namespace advcpp
{ 

ConnectionLostExeption::ConnectionLostExeption(const char* a_msg, InfoExeption a_info) NO_EXEPTION
: MyExeption(a_msg, a_info)
{
}

FileHandler::FileHandler(const char* a_ip, size_t a_port, std::string a_fileName, std::string a_from, std::string a_to)
: m_client(a_ip, a_port)
, m_fileName(a_fileName)
, m_from(a_from)
, m_to(a_to)
{
}

FileHandler::~FileHandler()
{
}

void FileHandler::Run()
{
    std::string tempFileName = m_from + m_fileName;

    cpp::FileReader reader(tempFileName);
    cpp::LowerCaseTransform execute;
    char buffer[MaxMsgLen];

    reader.Open();

    std::string lineFromFile = execute.Transform( reader.Read() );

    int n = 0;
    while ( !reader.IsEnd() )
    {
        std::string line = reader.Read();
        if(line.size() == 0){
            std::cout << "empty line" << std::endl;
            continue;
        }
        lineFromFile = execute.Transform(line);
        
        if(m_encoder.MakeMsg(buffer, lineFromFile))
        {
            ++n;     
            try
            {
                m_client.MsgSend(buffer, MaxMsgLen);        
                std::cout << "#:" << n << "\t" << lineFromFile << std::endl;

                char test;
                m_client.MsgRecive(&test, 1);   
  
            }
            catch(...)
            {
                XTHROW(ConnectionLostExeption, "connection failed");
            }
        }
        else
        {
            std::cout << "#:" << n << "\tbad cdr in file\n";            
        }
    }
    reader.Close();

    MoveFile();
}

void FileHandler::MoveFile()
{
    std::string oldName = m_from + m_fileName;
    std::string newName = m_to + m_fileName;

    rename(&oldName[0], &newName[0]);
}



}//namespace advcpp