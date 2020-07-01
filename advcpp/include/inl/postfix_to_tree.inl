#ifndef POSTFIX_TO_TREE_INL
#define POSTFIX_TO_TREE_INL

#include <stack>
#include <cctype> // isdigit
#include <cstdlib> // atoi
#include <algorithm> // for_each
#include "i_expression.hpp"

namespace advcpp
{

template <typename T>  
PostfixToTree<T>::PostfixToTree()
{
    initLookupTableOperators();
}    

template <typename T>    
typename PostfixToTree<T>::ExpressionTree PostfixToTree<T>::Convert(const std::vector<std::string>& a_postfix)
{
    std::vector<std::string>::const_iterator begin = a_postfix.begin();
    std::vector<std::string>::const_iterator end = a_postfix.end();

   // std::for_each(begin, end, *this); bug!!

    while(begin != end)
    {
        if(isNum(*begin))
        {
            pushNum(*begin);
        }
        else 
        {
            pushOperator(*begin);
        }     
        ++begin;    
    }

    std::tr1::shared_ptr<IExpression<T> > expressionTree = popExpression();

    return expressionTree;
}

template <typename T> 
void PostfixToTree<T>::operator()(const std::string& a_string)
{
    std::cout << "size stack " << m_expPtrTree.size() << '\n';    
    if(isNum(a_string))
    {
        pushNum(a_string);
    }
    else 
    {
        pushOperator(a_string);
    }     
}

template <typename T>  
void PostfixToTree<T>::pushNum(const std::string& a_num)
{
    std::tr1::shared_ptr<IExpression<T> > numExp = numCreator(a_num);
    m_expPtrTree.push(numExp);
}

template <typename T>  
void PostfixToTree<T>::pushOperator(const std::string& a_operator)
{
    std::tr1::shared_ptr<IExpression<T> > rhs = popExpression();
    std::tr1::shared_ptr<IExpression<T> > lhs = popExpression();
    std::tr1::shared_ptr<IOperator<T> > currOperator = operatorCreator(a_operator);
    std::tr1::shared_ptr<IExpression<T> > newExpression(new BinaryExp<T>(lhs, rhs, currOperator));

    m_expPtrTree.push(newExpression);
}

template <typename T> 
std::tr1::shared_ptr<IOperator<T> > PostfixToTree<T>::operatorCreator(const std::string& a_operator)
{
    return m_operators[a_operator[0]];
}

template <typename T> 
std::tr1::shared_ptr<IExpression<T> > PostfixToTree<T>::popExpression()
{
    std::tr1::shared_ptr<IExpression<T> > tmpExp = m_expPtrTree.top();
    m_expPtrTree.pop();
    return tmpExp;
}

template <typename T>
std::tr1::shared_ptr<IExpression<T> > PostfixToTree<T>::numCreator(const std::string& a_num)
{
    int number = atoi(a_num.c_str());

    std::tr1::shared_ptr<IExpression<T> > numPtr(new Num<T>(number));

    return numPtr;
}

template <typename T> 
bool PostfixToTree<T>::isNum(const std::string& a_string)
{
    char firstChar = a_string[0];

    return isdigit(firstChar);
}

template <typename T> 
void PostfixToTree<T>::initLookupTableOperators()
{
    std::tr1::shared_ptr<Addition<int> > add(new Addition<int>);
    std::tr1::shared_ptr<Subtraction<int> > sub(new Subtraction<int>);
    std::tr1::shared_ptr<Multiplication<int> > mul(new Multiplication<int>);
    std::tr1::shared_ptr<Division<int> > div(new Division<int>);    

    m_operators['+'] = add;
    m_operators['-'] = sub;
    m_operators['*'] = mul;
    m_operators['/'] = div;    
}

} // namespace advcpp

#endif // POSTFIX_TO_TREE_INL