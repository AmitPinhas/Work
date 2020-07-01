// https://app.codility.com/demo/results/trainingDT86NM-GAC/

#include <stack>

int solution(vector<int> &H) 
{
    int blocks = 0;
    stack<int> stackBlocks;

    stackBlocks.push(H[0]);
    
    for(size_t i = 1; i < H.size(); ++i)
    {
        if(stackBlocks.top() < H[i])
        {
           stackBlocks.push(H[i]); 
        }
        else if(stackBlocks.top() > H[i])
        {
            while(!stackBlocks.empty() && stackBlocks.top() > H[i])
            {
                ++blocks;
                stackBlocks.pop();
            }
            if(stackBlocks.empty() || stackBlocks.top() != H[i])
            {
                stackBlocks.push(H[i]); 
            }
        }
    }
    
    blocks += stackBlocks.size();
    
    return blocks;
}

// https://app.codility.com/demo/results/trainingMUZPHS-D6U/

int solution2(vector<int> &H) 
{
    int blocks = 0;
    stack<int> stackBlocks;
    
    for(auto block: H)
    {
        while(!stackBlocks.empty() && stackBlocks.top() > block)
        {
            stackBlocks.pop();
        }
        if(stackBlocks.empty() || stackBlocks.top() != block)
        {
            stackBlocks.push(block);
            ++blocks;
        }
    }
    
   