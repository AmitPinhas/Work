// https://app.codility.com/demo/results/trainingMN4GND-WX9/

int solution(vector<int> &A) 
{
    int indexDominator = -1;
    
    const size_t vectorSize = A.size();
    
    if(0 == vectorSize)
    {
        return indexDominator;
    }
    
    if(1 == vectorSize)
    {
        indexDominator = 0;
        return indexDominator;
    }
    
    int candidateDominator = A[0];
    indexDominator = 0;
    size_t countPairsDominator = 0;
    
    for(size_t i = 1; i < vectorSize; i += 2)
    {
        if(A[i - 1] == A[i])
        {
            if(A[i] == candidateDominator)
            {
                ++countPairsDominator;
            }
            else
            {
                if(countPairsDominator > 0)
                {
                    --countPairsDominator;
                }
                else
                {
                    candidateDominator = A[i];
                    indexDominator = i;
                    ++countPairsDominator;
                }
            }
        }
    }
    
    if(0 == countPairsDominator)
    {
        candidateDominator = A[vectorSize - 1];
        indexDominator = vectorSize - 1;
    }
    
    size_t counter = 0;
    
    for(auto num: A)
    {
        if(num == candidateDominator)
        {
            ++counter;
        }
    }
    
    if(counter <= vectorSize / 2)
    {
        indexDominator = -1;
    }
    
    return indexDominator;
}

// https://app.codility.com/demo/results/training8FFR7C-NCH/

int solution2(vector<int> &A) 
{
    const size_t vectorSize = A.size();
    int indexDominator = -1;
    
    if(0 == vectorSize)
    {
        return indexDominator;
    }

    indexDominator = 0;
    size_t counterDominator = 0;
    
    for(size_t i = 0; i < vectorSize; ++i)
    {
        if(A[i] == A[indexDominator])
        {
            ++counterDominator;
        }
        else if(counterDominator == 0)
        {
            indexDominator = i;
            ++counterDominator;
        }
        else
        {
            --counterDominator;
        }
    }
    
    if(0 == counterDominator)
    {
        indexDominator = -1;
    }
    
    counterDominator = 0;
    
    for(auto num: A)
    {
        if(num == A[indexDominator])
        {
            ++counterDominator;
        }
    }
    
    if(!(counterDominator > vectorSize / 2))
    {
        indexDominator = -1;
    }
    
    return indexDominator;
}