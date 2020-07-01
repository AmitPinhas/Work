#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#include <iostream>
#include "IReader.hpp"
#include "Itransformer.hpp"
#include "encoder.hpp"
#include "client_net.hpp"
#include "threads.hpp"
#include "exeption.hpp"

namespace advcpp
{

class ConnectionLostExeption : public MyExeption
{
public:
	ConnectionLostExeption(const char* a_msg, InfoExeption a_info) NO_EXEPTION;
};


class FileHandler : public advcpp::IRunAble
{
public:
    FileHandler(const char* a_ip, size_t a_port, std::string a_fileName, std::string a_from, std::string a_to);
    ~FileHandler();

    void Run();

private:
    void MoveFile();

private:
    Encoder m_encoder;
    client_net m_client;
    std::string m_fileName;
    std::string m_from;
    std::string m_to;

    static const size_t MaxMsgLen = 160;
};


}//advcpp namespace


#endif// FILE_HANDLER_HPP