#ifndef EXPRESSION_TREE_INL
#define EXPRESSION_TREE_INL

namespace advcpp
{

template <typename T>
ExpressionTree<T>::ExpressionTree(const std::string& a_infix, 
                                  std::tr1::shared_ptr<IParser> a_parser,
                                  InfixToPostfix& a_infixToPostfix, 
                                  PostfixToTree<T>& a_postfixToTree)
{
    initExpressionTree(a_infix, a_parser, a_infixToPostfix, a_postfixToTree);
}                   

template <typename T>
T ExpressionTree<T>::Result()
{
    return (*m_expressionTree).Value();
}

template <typename T>
void ExpressionTree<T>::initExpressionTree(const std::string& a_infix, 
                                           std::tr1::shared_ptr<IParser> a_parser, 
                                           InfixToPostfix& a_infixToPostfix, 
                                           PostfixToTree<T>& a_postfixToTree)
{
    std::vector<std::string> infix;

    a_parser->Delim(a_infix, infix);
    std::vector<std::string> postfix = a_infixToPostfix.Convert(infix); 
    m_expressionTree = a_postfixToTree.Convert(postfix);
}                                           


} // namespace advcpp

#endif // EXPRESSION_TREE_INL