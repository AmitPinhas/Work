#include "client.hpp"
#include <cstring> //strcmp
#include <cassert> //assert
#include <sstream>//std::stringstream
namespace advcpp
{

static uint MyAtoi(char const* a_cStr);
static inline bool IsSameOperator(Cdr const& a_cdr);

Client::Client(IMSI const& a_imsi, uint a_totalMinutesIn, uint a_totalMinutesOut, uint a_totalMinutesInOutside,
           uint a_totalMinutesOutOutside, uint a_totalSmsIn, uint a_totalSmsOut, uint m_totalSmsInOutside,
           uint a_totalSmsOutOutside, uint a_download, uint a_upload)
: m_imsi(a_imsi)
, m_totalMinutesIn(a_totalMinutesIn)
, m_totalMinutesOut(a_totalMinutesOut)
, m_totalMinutesInOutside(a_totalMinutesInOutside)
, m_totalMinutesOutOutside(a_totalMinutesOutOutside)
, m_totalSmsIn(a_totalSmsIn)
, m_totalSmsOut(a_totalSmsOut)
, m_totalSmsInOutside(m_totalSmsInOutside)
, m_totalSmsOutOutside(a_totalSmsOutOutside)
, m_download(a_download)
, m_upload(a_upload)
{
}

Client::Client()
: m_imsi()
, m_totalMinutesIn(0)
, m_totalMinutesOut(0)
, m_totalMinutesInOutside(0)
, m_totalMinutesOutOutside(0)
, m_totalSmsIn(0)
, m_totalSmsOut(0)
, m_totalSmsInOutside(0)
, m_totalSmsOutOutside(0)
, m_download(0)
, m_upload(0)
{
}


bool Client::CdrToClientIn(Cdr const& a_cdr, Client& a_clientIn)
{
    if(a_cdr.m_type == GPRS)
    {
        return false;
    }

    Client client(a_cdr.m_msisdnDes);
    a_clientIn = client;
    cdrToDataIn(a_cdr, a_clientIn);
    return true;
}

void Client::CdrToClientOut(Cdr const& a_cdr, Client& a_clientOut)
{
    Client client(a_cdr.m_imsi);
    a_clientOut = client;
    cdrToDataOut(a_cdr, a_clientOut);
}


void Client::cdrToDataOut(Cdr const& a_cdr, Client& a_clientOut)
{
    switch(a_cdr.m_type)
    {
        case CALL:
            if(IsSameOperator(a_cdr))
            {//call same operator
                a_clientOut.m_totalMinutesOut = MyAtoi(a_cdr.m_duration);
                return;
            }
            a_clientOut.m_totalMinutesOutOutside = MyAtoi(a_cdr.m_duration);
            break;
        case SMS:
            if(IsSameOperator(a_cdr))
            {//sms same operator
                ++a_clientOut.m_totalSmsOut;
                return;
            }
            ++a_clientOut.m_totalSmsOutOutside;
            break;
        case GPRS:
            a_clientOut.m_download = MyAtoi(a_cdr.m_download);
            a_clientOut.m_upload = MyAtoi(a_cdr.m_upload);
            break;
        default:
            assert("CDR to data in fail"&& false);
            break;
    }
}

void Client::cdrToDataIn(Cdr const& a_cdr, Client& a_clientIn)
{
    switch(a_cdr.m_type)
    {
        case CALL:
            if(IsSameOperator(a_cdr))
            {//call inside
                a_clientIn.m_totalMinutesIn = MyAtoi(a_cdr.m_duration);
                return;
            }
            a_clientIn.m_totalMinutesInOutside = MyAtoi(a_cdr.m_duration);
            break;
        case SMS:
            if(IsSameOperator(a_cdr))
            {//sms inside
                ++a_clientIn.m_totalSmsIn;
                return;
            }
            ++a_clientIn.m_totalSmsInOutside;
            break;
        default:
            assert("CDR to data out fail"&& false);
            break;
    }
}

IMSI const& Client::Imsi() const
{
    return m_imsi;
}

uint Client::MinutesIn() const
{
    return m_totalMinutesIn;
}

uint Client::MinutesOut() const
{
    return m_totalMinutesOut;
}

uint Client::MinutesInOutside() const
{
    return m_totalMinutesInOutside;
}

uint Client::MinutesOutOutside() const
{
    return m_totalMinutesOutOutside;
}

uint Client::SmsIn() const
{
    return m_totalSmsIn;
}

uint Client::SmsOut() const
{
    return m_totalSmsOut;
}

uint Client::SmsInOutside() const
{
    return m_totalSmsInOutside;
}

uint Client::SmsOutOutside() const
{
    return m_totalSmsOutOutside;
}

uint Client::Download() const
{
    return m_download;

}

uint Client::Upload() const
{
    return m_upload;
}

std::ostream& operator<<(std::ostream& a_os, Client const& a_client)
{
    a_os<<"Imsi: "<< a_client.Imsi()<<"\nMinutesIn "<<a_client.MinutesIn()<<"\nMinutesOut: "<< a_client.MinutesOut();
    a_os<<"\nMinutesInOutside "<<a_client.MinutesInOutside()<<"\nMinutesOutOutside"<<a_client.MinutesInOutside();
    a_os<<"\nSmsIn "<<a_client.SmsIn()<<"\nSmsOut "<<a_client.SmsOut()<<"\nUpload "<<a_client.Upload();
    return a_os;
}

Client& Client::operator+=(Client const& a_client)
{
    m_totalMinutesIn += a_client.m_totalMinutesIn;
    m_totalMinutesOut += a_client.m_totalMinutesOut;
    m_totalMinutesInOutside += a_client.m_totalMinutesInOutside;
    m_totalMinutesOutOutside += a_client.m_totalMinutesOutOutside;
    m_totalSmsIn += a_client.m_totalSmsIn;
    m_totalSmsOut += a_client.m_totalSmsOut;
    m_totalSmsInOutside += a_client.m_totalSmsInOutside;
    m_totalSmsOutOutside += a_client.m_totalSmsOutOutside;
    m_download += a_client.m_download;
    m_upload += a_client.m_upload;

    return *this;
}

void UpdateClient::operator()(Client& a_client, Client const& a_infoToAdd)
{
    a_client += a_infoToAdd;
}

size_t HashingClient::operator()(IMSI const& a_key) const
{
    unsigned long hash = 5381;

    for(size_t i = 0; i < a_key.size(); ++i)
    {
            hash = ((hash << 5) + hash) + a_key[i];
    }

    return hash;
}

static uint MyAtoi(char const* a_cStr)
{
    assert(a_cStr != 0);
    std::stringstream ss(a_cStr);
    uint r;
    ss>>r;
    return r;
}

static inline bool IsSameOperator(Cdr const& a_cdr)
{
    return !strcmp(a_cdr.m_mccMnc, a_cdr.m_mccMncDes);
}

} //namespace advcpp