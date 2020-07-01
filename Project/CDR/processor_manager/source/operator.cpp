#include "operator.hpp"
#include <cmath> //pow
#include <cstring> //strcmp
#include <cassert> //assert
#include <sstream> //std::stringstream
namespace advcpp
{

static uint MyAtoi(char const* a_cStr);



Operator::Operator()
: m_mccAndMnc()
, m_name()
, m_totalMinutesIn()
, m_totalMinutesOut()
, m_totalSmsIn()
, m_totalSmsOut()
{
}


Operator::Operator(uint a_mccAndMnc, std::string const& a_name, uint a_totalMinutesIn, uint a_totalMinutesOut,
        uint a_totalSmsIn, uint a_totalSmsOut)
: m_mccAndMnc(a_mccAndMnc)
, m_name(a_name)
, m_totalMinutesIn(a_totalMinutesIn)
, m_totalMinutesOut(a_totalMinutesOut)
, m_totalSmsIn(a_totalSmsIn)
, m_totalSmsOut(a_totalSmsOut)
{
}

std::string const& Operator::Brand() const
{
    return m_name;
}

uint Operator::MccMnc() const
{
    return m_mccAndMnc;
}

uint Operator::MinutesIn() const
{
    return m_totalMinutesIn;
}

uint Operator::MinutesOut() const
{
    return m_totalMinutesOut;
}

uint Operator::SmsIn() const
{
    return m_totalSmsIn;
}

uint Operator::SmsOut() const
{
    return m_totalSmsOut;
}

bool Operator::CdrToOperatorIn(Cdr const& a_cdr, Operator& a_operatorIn)
{
    if(a_cdr.m_type == GPRS)
    {
        return false;
    }

    Operator op(MyAtoi(a_cdr.m_mccMncDes));
    a_operatorIn = op;
    cdrToDataIn(a_cdr, a_operatorIn);
    return true;
}

void Operator::cdrToDataIn(Cdr const& a_cdr, Operator& a_operatorIn)
{
    switch(a_cdr.m_type)
    {
        case CALL:
                a_operatorIn.m_totalMinutesIn = MyAtoi(a_cdr.m_duration);
                return;
        case SMS:
                ++a_operatorIn.m_totalSmsIn;
                return;
        default:
            assert("CDR to data out fail"&& false);
            break;
    }
}

bool Operator::CdrToOperatorOut(Cdr const& a_cdr, Operator& a_operatorOut)
{
    if(a_cdr.m_type == GPRS)
    {
        return false;
    }
    Operator op( MyAtoi(a_cdr.m_mccMnc), a_cdr.m_operatorName);
    a_operatorOut = op;
    cdrToDataOut(a_cdr, a_operatorOut);
    return true;
}

void Operator::cdrToDataOut(Cdr const& a_cdr, Operator& a_operatorOut)
{
    switch(a_cdr.m_type)
    {
        case CALL:
                a_operatorOut.m_totalMinutesOut = MyAtoi(a_cdr.m_duration);
                return;
        case SMS:
                ++a_operatorOut.m_totalSmsOut;
                return;
        default:
                assert("CDR to data in fail"&& false);
                break;
    }
}

Operator& Operator::operator+=(Operator const& a_operator)
{
    if(m_name.empty())
    {
        m_name = a_operator.m_name;
    }
    m_totalMinutesIn += a_operator.m_totalMinutesIn;
    m_totalMinutesOut += a_operator.m_totalMinutesOut;
    m_totalSmsIn += a_operator.m_totalSmsIn;
    m_totalSmsOut += a_operator.m_totalSmsOut;
    return *this;
}

std::ostream& operator<<(std::ostream& a_os, Operator const& a_operator)
{
    a_os<<"Mcc/Mnc: "<< a_operator.MccMnc()<<"\nOperator name: "<< a_operator.Brand();
    a_os<<"\nMinutes In: "<<a_operator.MinutesIn()<<"\nMinutes Out: "<<a_operator.MinutesOut();
    a_os<<"\nSms In: "<<a_operator.SmsIn()<<"\nSms Out: "<<a_operator.SmsOut();
    return a_os;
}


void UpdateOperator::operator()(Operator& a_operator, Operator const& a_infoToAdd)
{
    a_operator += a_infoToAdd;
}

size_t HashingOperator::operator()(uint a_key) const
{
    const size_t num = 2654435761;
    return (a_key * num) % static_cast<size_t>(pow(2, 32));
}

static uint MyAtoi(char const* a_cStr)
{
    assert(a_cStr != 0);
    std::stringstream ss(a_cStr);
    uint r;
    ss>>r;
    return r;
}


}//namespace advcpp
