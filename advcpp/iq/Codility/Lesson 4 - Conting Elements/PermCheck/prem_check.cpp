
int solution(vector<int> &A) 
{
    const int vectorSize = A.size();
    int result = 1;
    
    for(auto num : A)
    {
        if(num > vectorSize)
        {
            result = 0;
            break;
        }
        else
        {
            size_t index = abs(num) - 1;
            if (A[index] < 0)
            {
                result = 0;
                break;
            }
            A[index] *= -1;
        }
    }
    
    if(!result)
    {
        for(auto & num : A)
        {
            num = abs(num);
        }
        return result;
    }
    
    for(auto & num : A)
    {
        if(num > 0)
        {
            result = 0;
        }
        num = abs(num);
    }

    return result;
}



int solution2(vector<int> &A) 
{
    const int vectorSize = A.size();
    
    if(1 == vectorSize)
    {
        if(1 == A[0])
        {
            return 1;
        }
        return 0;
    }
    
    vector<bool> exists(vectorSize, false);
    
    for(auto num : A)
    {
        if(num > vectorSize)
        {
            return 0;
        }
        
        if(exists[num - 1])
        {
            return 0;
        }
        
        exists[num - 1] = true;
    }
    
    return 1;
}

