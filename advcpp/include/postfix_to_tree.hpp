#ifndef POSTFIX_TO_TREE_HPP
#define POSTFIX_TO_TREE_HPP

#include <vector>
#include <string>
#include <map>
#include <stack>
#include "i_operator.hpp"
#include "i_expression.hpp"
#include "shared_ptr.hpp"
#include "expressions.hpp"

namespace advcpp
{

template <typename T>
class PostfixToTree
{
public:
    typedef std::tr1::shared_ptr<IExpression<T> > ExpressionTree;

    PostfixToTree(); 

    //PostfixToTree(const & PostfixToTree a_rhs); = delete
    //PostfixToTree& operator =(const & PostfixToTree a_rhs); = delete

    ExpressionTree Convert(const std::vector<std::string>& a_postfix); 
    
    void operator()(const std::string& a_string);

private:
    void initLookupTableOperators();
    std::tr1::shared_ptr<BinaryExp<T> > binaryExpCreator(std::string a_lhs, std::string a_rhs, std::string a_operator);
    std::tr1::shared_ptr<IExpression<T> > numCreator(const std::string& a_num);
    std::tr1::shared_ptr<IOperator<T> > operatorCreator(const std::string& a_operator); 
    bool isNum(const std::string& a_string);
    void pushNum(const std::string& a_num);
    void pushOperator(const std::string& a_operator);
    std::tr1::shared_ptr<IExpression<T> > popExpression();

private:
    std::map<char, std::tr1::shared_ptr<IOperator<T> > > m_operators;
    std::stack< std::tr1::shared_ptr<IExpression<T> > > m_expPtrTree;
};

} // namespace advcpp

#include "inl/postfix_to_tree.inl"

#endif // POSTFIX_TO_TREE_HPP