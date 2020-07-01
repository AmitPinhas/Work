// https://app.codility.com/demo/results/trainingMYXKE8-X6K/

#include "mu_test.h"

#include <stack>

int solution(string &S) 
{
    stack<char> leftBrackets;
    
    for(auto element: S)
    {
        if(element == '(' || element == '[' || element == '{')
        {
            leftBrackets.push(element);
        }
        if(element == ')' || element == ']' || element == '}')
        {
            if(!leftBrackets.empty())
            {
                const char left = leftBrackets.top();
                leftBrackets.pop();
            
                switch(element)
                {
                    case ')':
                                if(left != '(')
                                {
                                    return 0;
                                }
                                break;
                    case ']':
                                if(left != '[')
                                {
                                    return 0;
                                }
                                break;
                    case '}':
                                if(left != '{')
                                {
                                    return 0;
                                }                    
                                break;                            
                    default:
                                break;
                }
            }
            else
            {
                return 0;
            }
        }
    }
    
    if(leftBrackets.empty())
    {
        return 1;
    }
    
    return 0;

}


UNIT(smoke)

    ASSERT_PASS();

END_UNIT

TEST_SUITE(test_brackets)

    TEST(smoke)

END_SUITE