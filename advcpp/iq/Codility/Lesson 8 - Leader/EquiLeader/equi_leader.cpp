// https://app.codility.com/demo/results/trainingQC4CGH-JRN/

int solution(vector<int> &A) 
{
    const size_t vectorSize = A.size();
    int indexDominator = -1;
    int equiLeader = 0;
    
    if(0 == vectorSize)
    {
        return equiLeader;
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
        return equiLeader;
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
         return equiLeader;
    }
    
    const int Dominator = A[indexDominator];
    size_t leftCounter = 0;
    
    for(size_t i = 0; i < vectorSize - 1; ++i)
    {
        const size_t half = (i + 1) / 2;
        const int secondHalf = (vectorSize - 1 - i) / 2;
        
        if(A[i] == Dominator)
        {
            ++leftCounter;
        }
        
        const int rightCounter = counterDominator - leftCounter;
        
        if(leftCounter > half && rightCounter > secondHalf)
        {
            ++equiLeader;
        }
    }
    
    return equiLeader;    
}

