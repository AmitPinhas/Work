#ifndef MSG_HENDLER_HPP
#define MSG_HENDLER_HPP

#include "safe_queue.hpp"
#include "server_net.hpp"
#include "protocol.hpp"

#define Cdr int//////delete

namespace advcpp
{

class CdrMsgHendler
{
public:
    CdrMsgHendler(SafeQueue<Cdr>& a_queue);
    ~CdrMsgHendler();

    void Run();
    void CdrIn(char* a_msgIn);

private:
    SafeQueue<Cdr>& m_queue;
    ServerNet<void (*)(char*)> m_server;
    Idecoder* m_decoder;
};


inline CdrMsgHendler::CdrMsgHendler(SafeQueue<Cdr>& a_queue)
: m_queue(a_queue)
, m_server(CdrIn, CdrServerMsgSize, CdrServerPort, CdrServerQueueLen)
, m_decoder(CdrDecoder)
{
}


inline CdrMsgHendler::~CdrMsgHendler()
{
}


inline void CdrMsgHendler::Run()
{
    m_server.Run();
}

inline void CdrMsgHendler::CdrIn(char* a_msgIn)
{
    Cdr curr = m_decoder-> Decode();
}


}//advcpp namespace


#endif // MSG_HENDLER_HPP