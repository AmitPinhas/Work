#include "mu_test.h"

#include <string>
#include <vector>
#include <tr1/memory> // std::tr1::shared_ptr
#include "operators.hpp"
#include "expressions.hpp"
//#include "shared_ptr.hpp"
#include "postfix_to_tree.hpp"
#include "infix_to_postfix.hpp"
#include "record_parser_by_delim.hpp"
#include "expression_tree.hpp"
#include "i_parser.hpp"
#include "logics.hpp"

using namespace advcpp;
using namespace std;

UNIT(addition)
    // 5 + 6

    std::tr1::shared_ptr<Addition<int> > operatorPtr(new Addition<int>);
    std::tr1::shared_ptr<Num<int> > lhsNum(new Num<int>(5));
    std::tr1::shared_ptr<Num<int> > rhsNum(new Num<int>(6));

    BinaryExp<int> addExp(lhsNum, rhsNum, operatorPtr);

    ASSERT_THAT(addExp.Value() == 11);

END_UNIT

UNIT(addition_with_multiplication)
    // 5 + 6 * 8

    std::tr1::shared_ptr<Addition<int> > operatorPtr(new Addition<int>);
    std::tr1::shared_ptr<Multiplication<int> > operatorMulPtr(new Multiplication<int>);
    std::tr1::shared_ptr<Num<int> > f(new Num<int>(5));
    std::tr1::shared_ptr<Num<int> > s(new Num<int>(6));
    std::tr1::shared_ptr<Num<int> > e(new Num<int>(8));

    std::tr1::shared_ptr<BinaryExp<int> > mulExp(new BinaryExp<int>(s, e, operatorMulPtr));

    BinaryExp<int> addExp(f, mulExp, operatorPtr);

    ASSERT_THAT(addExp.Value() == 53);

END_UNIT

UNIT(long_test)
    // ( ( 1 + 2) * (3 - 1) + 6 )/ (2 + 4)

    std::tr1::shared_ptr<Addition<int> > operatorAddPtr(new Addition<int>);
    std::tr1::shared_ptr<Multiplication<int> > operatorMulPtr(new Multiplication<int>);
    std::tr1::shared_ptr<Division<int> > operatorDivPtr(new Division<int>);
    std::tr1::shared_ptr<Subtraction<int> > operatorSubPtr(new Subtraction<int>);    
    std::tr1::shared_ptr<Num<int> > one(new Num<int>(1));
    std::tr1::shared_ptr<Num<int> > two(new Num<int>(2));
    std::tr1::shared_ptr<Num<int> > three(new Num<int>(3));
    std::tr1::shared_ptr<Num<int> > six(new Num<int>(6));
    std::tr1::shared_ptr<Num<int> > four(new Num<int>(4));

    std::tr1::shared_ptr<BinaryExp<int> > Exp1(new BinaryExp<int>(one, two, operatorAddPtr));
    std::tr1::shared_ptr<BinaryExp<int> > Exp2(new BinaryExp<int>(three, one, operatorSubPtr));    
    std::tr1::shared_ptr<BinaryExp<int> > Exp3(new BinaryExp<int>(Exp1, Exp2, operatorMulPtr));
    std::tr1::shared_ptr<BinaryExp<int> > Exp4(new BinaryExp<int>(Exp3, six, operatorAddPtr));
    std::tr1::shared_ptr<BinaryExp<int> > Exp5(new BinaryExp<int>(two, four, operatorAddPtr));
    std::tr1::shared_ptr<BinaryExp<int> > Exp6(new BinaryExp<int>(Exp4, Exp5, operatorDivPtr));
    //IExpression * a = new Num(8);
    ASSERT_THAT((*Exp6).Value() == 2);

END_UNIT

UNIT(postfix_to_tree_addition)
    // 5 + 6
    // 56+

    PostfixToTree<int> postToTree; 

    vector<string> postfix;

    RecordParserByDelim parserByDelim(' ');

    parserByDelim.Delim("5 6 +", postfix);
    
    std::tr1::shared_ptr<IExpression<int> > myTree = postToTree.Convert(postfix);

    ASSERT_THAT(myTree->Value() == 11);

END_UNIT

UNIT(postfix_to_tree_addition_with_multiplication)
    // 5 + 6 * 8
    //5 6 8 * +

    PostfixToTree<int> postToTree; 

    vector<string> postfix;

    RecordParserByDelim parserByDelim(' ');

    parserByDelim.Delim("5 6 8 * +", postfix);

    std::tr1::shared_ptr<IExpression<int> > myTree = postToTree.Convert(postfix);

    ASSERT_THAT((*myTree).Value() == 53);

END_UNIT

UNIT(postfix_to_tree_long_test)
    // ( ( 1 + 2) * (3 - 1) + 6 )/ (2 + 4)
    // 1 2 + 3 1 - * 6 + 2 4 + /

    PostfixToTree<int> postToTree;

    vector<string> postfix;

    RecordParserByDelim parserByDelim(' ');

    parserByDelim.Delim("1 2 + 3 1 - * 6 + 2 4 + /", postfix);

    std::tr1::shared_ptr<IExpression<int> > myTree = postToTree.Convert(postfix);

    ASSERT_THAT((*myTree).Value() == 2);

END_UNIT

UNIT(infix_addition)
    // 5 + 6
    // 56+

    InfixToPostfix infixPostfix;

    vector<string> infix;

    RecordParserByDelim parserByDelim(' ');

    parserByDelim.Delim("5 + 6", infix);

    vector<string> postfix = infixPostfix.Convert(infix);

    size_t index = postfix.size();

    vector<string> check;

    parserByDelim.Delim("5 6 +", check);

    while(index-- > 0)   
    {
        ASSERT_THAT(postfix[index] == check[index]);
    }  

END_UNIT

UNIT(infix_addition_with_multiplication)
    // 5 + 6 * 8
    // 5 6 8 * +

    InfixToPostfix infixPostfix;

    vector<string> infix;

    RecordParserByDelim parserByDelim(' ');

    parserByDelim.Delim("5 + 6 * 8", infix);    

    vector<string> postfix = infixPostfix.Convert(infix); 

    vector<string> check;

    parserByDelim.Delim("5 6 8 * +", check);

    size_t index = postfix.size();

    while(index-- > 0)   
    {
        ASSERT_THAT(postfix[index] == check[index]);
    } 

END_UNIT

UNIT(infix_long_test)
    // ( ( 1 + 2) * (3 - 1) + 6 )/ (2 + 4)
    // 1 2 + 3 1 - * 6 + 2 4 + /

    InfixToPostfix infixPostfix;   

    vector<string> infix;

    RecordParserByDelim parserByDelim(' ');

    parserByDelim.Delim("( ( 1 + 2 ) * ( 3 - 1 ) + 6 ) / ( 2 + 4 )", infix);

    vector<string> postfix = infixPostfix.Convert(infix); 

    vector<string> check;

    parserByDelim.Delim("1 2 + 3 1 - * 6 + 2 4 + /", check);   

    size_t index = postfix.size();

    while(index-- > 0)   
    {
        ASSERT_THAT(postfix[index] == check[index]);
    }

END_UNIT

UNIT(class_tree_add)
    std::tr1::shared_ptr<IParser> parser(new RecordParserByDelim(' '));

    InfixToPostfix infixPostfix;

    PostfixToTree<int> postToTree;

    ExpressionTree<int> tree("5 + 6", parser, infixPostfix, postToTree);

    ASSERT_EQUAL(tree.Result(), 11);

END_UNIT

UNIT(postorder_print)
    // 5 + 6
    // 56+
    
    Printer<int> printLogic(cout);
    
    PostfixToTree<int> postToTree;

    vector<string> postfix;

    RecordParserByDelim parserByDelim(' ');

    parserByDelim.Delim("5 6 +", postfix);
    
    std::tr1::shared_ptr<IExpression<int> > myTree = postToTree.Convert(postfix);

    PostOrder<int> postOrder(printLogic);

    postOrder.Execute(*myTree);

    ASSERT_PASS();
END_UNIT

UNIT(postorder_print_addition_with_multiplication)
    // 5 + 6 * 8
    // 5 6 8 * +
    
    Printer<int> printLogic(cout);

    PostfixToTree<int> postToTree;

    vector<string> postfix;

    RecordParserByDelim parserByDelim(' ');

    parserByDelim.Delim("5 6 8 * +", postfix);
    
    std::tr1::shared_ptr<IExpression<int> > myTree = postToTree.Convert(postfix);

    PostOrder<int> postOrder(printLogic);

    postOrder.Execute(*myTree);

    ASSERT_PASS();
END_UNIT

UNIT(postorder_print_long_test)
    // ( ( 1 + 2) * (3 - 1) + 6 )/ (2 + 4)
    // 1 2 + 3 1 - * 6 + 2 4 + /
    
    Printer<int> printLogic(cout);

    PostfixToTree<int> postToTree;

    vector<string> postfix;

    RecordParserByDelim parserByDelim(' ');

    parserByDelim.Delim("1 2 + 3 1 - * 6 + 2 4 + /", postfix);
    
    std::tr1::shared_ptr<IExpression<int> > myTree = postToTree.Convert(postfix);

    PostOrder<int> postOrder(printLogic);

    postOrder.Execute(*myTree);

    ASSERT_PASS();
END_UNIT

TEST_SUITE(test the expression on fire)

    TEST(addition)
    TEST(addition_with_multiplication)
    TEST(long_test)
    TEST(postfix_to_tree_addition)
    TEST(postfix_to_tree_addition_with_multiplication)
    TEST(postfix_to_tree_long_test)
    TEST(infix_addition)
    TEST(infix_addition_with_multiplication)
    TEST(infix_long_test)
    TEST(class_tree_add)
    TEST(postorder_print)
    TEST(postorder_print_addition_with_multiplication)
    TEST(postorder_print_long_test)

END_SUITE
