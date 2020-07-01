// https://app.codility.com/demo/results/trainingB7Y77F-R9P/

#include <stack>

int solution(vector<int> &A, vector<int> &B) 
{
    int alive = 0;
    stack<int> downstream;
    
    for(size_t i = 0; i < A.size(); ++i)
    {
        if(B[i])
        {
            downstream.push(A[i]);
        }
        else
        {
            if(downstream.empty())
            {
                ++alive;
            }
            else
            {
                while(!downstream.empty() && downstream.top() < A[i])
                {
                    downstream.pop();
                }
                if(downstream.empty())
                {
                    ++alive;
                }
            }
        }
    }
    
    alive += downstream.size();
    
    return alive;
}