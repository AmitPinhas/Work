#ifndef INFIX_TO_POSTFIX_INL
#define INFIX_TO_POSTFIX_INL

#include "infix_to_postfix.hpp"

#include <cctype> // isdigit

namespace advcpp
{

inline bool InfixToPostfix::isNum(const std::string& a_string)
{
    char firstChar = a_string[0];

    return isdigit(firstChar);    
}

inline void InfixToPostfix::pushLeftBracket(const std::string& a_leftBracket)
{
    m_stack.push(a_leftBracket);
}

inline bool InfixToPostfix::stackNotEmpty()
{
    return !m_stack.empty();
}

} // namespace advcpp

#endif // INFIX_TO_POSTFIX_INL