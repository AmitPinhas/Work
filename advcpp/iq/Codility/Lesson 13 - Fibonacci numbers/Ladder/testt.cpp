// remove leetcode !!!!

#include "mu_test.h"

#include <algorithm>  // std::min, std::max
#include <vector>
#include <stack>

using std::vector;
using std::stack;
using std::min;

class Solution 
{
public:
    int largestRectangleArea(vector<int>& heights);
};

int Solution::largestRectangleArea(vector<int>& heights)
{
    const int vectorSize = heights.size();
    int areaOfLargestRectangle = 0;
    
    if(0 == vectorSize)
    {
        return areaOfLargestRectangle;
    }
    
    if(1 == vectorSize)
    {
        const size_t indexFirstElement = 0;
        
        areaOfLargestRectangle = heights[indexFirstElement];
        
        return areaOfLargestRectangle;
    }
    
    int i = 0;
    stack<int> indexs;
    
    while(i < vectorSize)
    {
        if(indexs.empty())
        {
            indexs.push(i);
            ++i;            
        }
 
        int top = heights[indexs.top()];
        
        if(top <= heights[i])
        {
            indexs.push(i);
            ++i;
        }
        else
        {      
            int area = 0;
            indexs.push(i);

            while(!indexs.empty())
            {
                top = heights[indexs.top()];
                indexs.pop();
                if(indexs.empty())
                {
                   area = top * i; 
                }
                else
                {
                   area = top * (i - indexs.top() - 1);
                }
                
                if(area > areaOfLargestRectangle)
                {
                    areaOfLargestRectangle = area;
                }
            }
        }
    }
    
    while(!indexs.empty())
    {
        int top = heights[indexs.top()];
        int area = 0;
        indexs.pop();
        if(indexs.empty())
        {
           area = top * i; 
        }
        else
        {
           area = top * (i - indexs.top() - 1);
        }

        if(area > areaOfLargestRectangle)
        {
            areaOfLargestRectangle = area;
        }
    }    
    
    return areaOfLargestRectangle;
       
}

UNIT(smoke)

    Solution solutionVar;

    vector<int> v = {2, 1, 5, 6, 2, 3};

    ASSERT_EQUAL(solutionVar.largestRectangleArea(v), 10);
    
END_UNIT

TEST_SUITE(leetcode)

    TEST(smoke)

END_SUITE    

