

int solution(vector<int> &A) 
{
    const size_t rangeSize = A.size() + 1;
    
    const size_t fullSum = rangeSize * (1 + rangeSize) / 2;
    
    size_t tmpSum = 0;
    
    for(auto num : A)
    {
        tmpSum += num;
    }
    
    return fullSum - tmpSum;
}

