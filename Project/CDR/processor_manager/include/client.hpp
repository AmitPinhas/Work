#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string> // std::string
#include <iostream> //std::ostream
#include "cdr.hpp"

typedef unsigned int uint;
typedef std::string IMSI;

namespace advcpp
{

class Client
{

public:
    Client();
    explicit Client(IMSI const& a_imsi, uint a_totalMinutesIn = 0, uint a_totalMinutesOut = 0, uint a_totalMinutesInOutside = 0,
           uint a_totalMinutesOutOutside = 0, uint a_totalSmsIn = 0, uint a_totalSmsOut = 0, uint m_totalSmsInOutside = 0,
           uint a_totalSmsOutOutside = 0, uint a_download = 0, uint a_upload = 0);
    //~Client() = default;
    //Client(Client const&) = default;
    //Client& operator=(Client const&) = default;
    Client& operator+=(Client const& a_client);
    static bool CdrToClientIn(Cdr const& a_cdr, Client& a_clientIn); //if a_cdr is gprs returns false
    static void CdrToClientOut(Cdr const& a_cdr, Client& a_clientOut);

    IMSI const& Imsi() const;
    uint MinutesIn() const;
    uint MinutesOut() const;
    uint MinutesInOutside() const;
    uint MinutesOutOutside() const;
    uint SmsIn() const;
    uint SmsOut() const;
    uint SmsInOutside() const;
    uint SmsOutOutside() const;
    uint Download() const;
    uint Upload() const;

private:
    static void cdrToDataOut(Cdr const& a_cdr, Client& a_clientOut);
    static void cdrToDataIn(Cdr const& a_cdr, Client& a_clientIn);
private:
	IMSI m_imsi;
	uint m_totalMinutesIn;
	uint m_totalMinutesOut;
    uint m_totalMinutesInOutside;
	uint m_totalMinutesOutOutside;
	uint m_totalSmsIn;
	uint m_totalSmsOut;
    uint m_totalSmsInOutside;
	uint m_totalSmsOutOutside;
	uint m_download;
	uint m_upload;
};

std::ostream& operator<<(std::ostream& a_os, Client const& a_client);
struct UpdateClient
{
    void operator()(Client& a_client, Client const& a_infoToAdd);
};

struct HashingClient
{
    size_t operator()(IMSI const& a_key) const;
};

}

#endif //CLIENT_HPP