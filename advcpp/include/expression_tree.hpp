#ifndef EXPRESSION_TREE_HPP
#define EXPRESSION_TREE_HPP

#include<string>
#include "infix_to_postfix.hpp"
#include "i_parser.hpp"
//#include "record_parser_by_delim.hpp"
#include "postfix_to_tree.hpp"

namespace advcpp
{

template <typename T>
class ExpressionTree
{
public:
    ExpressionTree(const std::string& a_infix, 
                   std::tr1::shared_ptr<IParser> a_parser, 
                   InfixToPostfix& a_infixToPostfix, 
                   PostfixToTree<T>& a_postfixToTree);

    // ~ExpressionTree(); = default
    // ExpressionTree(const ExpressionTree& a_rhs); = default
    // ExpressionTree& operator =(const ExpressionTree& a_rhs); = defaultS

    T Result();

    void PrintInorder();
    void PrintPreorder();
    void Postorder();

private:
    void initExpressionTree(const std::string& a_infix, 
                            std::tr1::shared_ptr<IParser> a_parser, 
                            InfixToPostfix& a_infixToPostfix, 
                            PostfixToTree<T>& a_postfixToTree);

private:
    std::tr1::shared_ptr<IExpression<T> > m_expressionTree;

};

} // namespace advcpp

#include "inl/expression_tree.inl"

#endif // EXPRESSION_TREE_HPP