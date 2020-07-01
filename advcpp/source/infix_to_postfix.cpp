#include "infix_to_postfix.hpp"

namespace advcpp
{
/*
InfixToPostfix::InfixToPostfix()
{
    initLookupOperators();
}
*/
std::vector<std::string> InfixToPostfix::Convert(const std::vector<std::string>& a_infix)
{
    std::vector<std::string>::const_iterator begin = a_infix.begin();
    std::vector<std::string>::const_iterator end = a_infix.end();  

    while(begin != end)
    {
        if(isNum(*begin))
        {
            m_postfix.push_back(*begin);
        }
        else 
        {
            pushOperator(*begin);
        }     
        ++begin;    
    }

    m_postfix.push_back(m_stack.top());
    m_stack.pop();

    return m_postfix;
}

void InfixToPostfix::pushRightBracket(const std::string& )
{
    std::string first;
    std::string second;

    if(stackNotEmpty())
    {
        first = m_stack.top();
        while(stackNotEmpty() && first != "(")
        {   
            second = m_stack.top();
            m_stack.pop();
            m_postfix.push_back(second);
            first = m_stack.top();            
        }
    }
    if(first == "(")
    {
        second = m_stack.top();
        m_stack.pop();
    }   
}

void InfixToPostfix::pushMulOrDiv(const std::string& a_MulOrDiv)
{
    if(stackNotEmpty())
    {
        std::string first = m_stack.top();
        while(stackNotEmpty() && first != "(" && first != "+" && first != "-" )
        {   
            std::string second = m_stack.top();
            m_stack.pop();
            m_postfix.push_back(second);
            first = m_stack.top();            
        }
    }
    m_stack.push(a_MulOrDiv);  
}

void InfixToPostfix::pushAddOrSub(const std::string& a_addOrSub)
{
    if(stackNotEmpty())
    {
        std::string first = m_stack.top();
        while(stackNotEmpty() && first != "(")
        {   
            std::string second = m_stack.top();
            m_stack.pop();
            m_postfix.push_back(second);
            first = m_stack.top();            
        }
    }
    m_stack.push(a_addOrSub);
}
/*
void InfixToPostfix::initLookupOperators()
{
    m_operators['+'] = pushAddOrSub;
    m_operators['-'] = pushAddOrSub;   
    m_operators['*'] = pushMulOrDiv;   
    m_operators['/'] = pushMulOrDiv; 
    m_operators['('] = pushLeftBracket;  
    m_operators[')'] = pushRightBracket;                    
}
*/
void InfixToPostfix::pushOperator(const std::string& a_operator)
{
    char currOperator = a_operator[0];

    //m_operators[currOperator](a_operator);

    switch(currOperator)
    {
        case '+':
        case '-':
                    pushAddOrSub(a_operator);
                    break;
        case '*':
        case '/':
                   pushMulOrDiv(a_operator);
                   break;
        case '(':
                   pushLeftBracket(a_operator);
                   break;
        case ')':
                    pushRightBracket(a_operator);
                    break;                                     
        default:
                break;
    }
}

} // namespace advcpp