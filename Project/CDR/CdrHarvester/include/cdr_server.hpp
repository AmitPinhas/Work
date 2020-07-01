#ifndef CDR_SERVER
#define CDR_SERVER
#include "common.hpp"
#include "safe_queue.hpp"
#include "msg_hendler.hpp"

namespace advcpp
{


class CdrServer : private UnCopyAble
{
public:
    CdrServer(size_t a_queueSize);
    ~CdrServer();

    void Pause();
    void Resume();
    void ShutDown();

private:
    SafeQueue<Cdr> m_queue;
    CdrMsgHendler m_msgHendler;

};

CdrServer::CdrServer(size_t a_queueSize)
: m_queue(a_queueSize)
{
}

CdrServer::~CdrServer()
{
}






}//advcpp namespace

#endif // !CDR_SERVER