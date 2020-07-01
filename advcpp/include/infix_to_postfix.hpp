#ifndef INFIX_TO_POSTFIX
#define INFIX_TO_POSTFIX

#include <stack>
#include <string>
#include <vector>
#include <map>

namespace advcpp
{

class InfixToPostfix
{
public:
    //InfixToPostfix(); 

    // ~InfixToPostfix(); = default
    // InfixToPostfix(const InfixToPostfix& a_rhs); = default
    // InfixToPostfix& operator =(const InfixToPostfix& a_rhs); = default

    std::vector<std::string> Convert(const std::vector<std::string>& a_infix);

private:
    bool isNum(const std::string& a_string);
    void pushOperator(const std::string& a_operator);  
    void pushAddOrSub(const std::string& a_addOrSub);  
    void pushMulOrDiv(const std::string& a_MulOrDiv);
    void pushLeftBracket(const std::string& a_leftBracket);
    void pushRightBracket(const std::string& a_rightBracket);
    //void initLookupOperators();
    bool stackNotEmpty();

private:
    std::stack<std::string> m_stack;
    std::vector<std::string> m_postfix;
    //std::map<char,  void (*)(const std::string&) > m_operators;    

};

} // namespace advcpp

#include "inl/infix_to_postfix.inl"

#endif // INFIX_TO_POSTFIX