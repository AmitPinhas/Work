#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include <string>
#include <iostream> // ostream
#include "cdr.hpp"

typedef unsigned int uint;
typedef uint MCCMNC;
namespace advcpp
{

class Operator
{

public:  
    Operator();  
    explicit Operator(uint a_mccAndMnc, std::string const& a_name = "\0", uint a_totalMinutesIn = 0, uint a_totalMinutesOut = 0,
             uint a_totalSmsIn = 0, uint a_totalSmsOut = 0);
    //~Client() = default;  
    //Client(Client const&) = default;
    //Client& operator=(Client const&) = default;
    Operator& operator+=(Operator const& a_operator);

    static bool CdrToOperatorIn(Cdr const& a_cdr, Operator& a_operatorIn); //if a_cdr is gprs returns false
    static bool CdrToOperatorOut(Cdr const& a_cdr, Operator& a_operatorOut);

    std::string const& Brand() const;
    uint MccMnc() const;
    uint MinutesIn() const;
    uint MinutesOut() const;
    uint SmsIn() const;
    uint SmsOut() const;

private:
    static void cdrToDataOut(Cdr const& a_cdr, Operator& a_operatorOut);
    static void cdrToDataIn(Cdr const& a_cdr, Operator& a_operatorIn);

private:
    uint m_mccAndMnc;
    std::string m_name;
	uint m_totalMinutesIn;
	uint m_totalMinutesOut;
	uint m_totalSmsIn;
	uint m_totalSmsOut;
};

std::ostream& operator<<(std::ostream& a_os, Operator const& a_operator);

struct UpdateOperator
{
    void operator()(Operator& a_operator, Operator const& a_infoToAdd);
};

struct HashingOperator
{
    size_t operator()(uint a_key) const;
};

}//namespace advcpp 


#endif //OPERATOR_HPP