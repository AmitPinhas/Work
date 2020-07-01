int solution(vector<int> &A) 
{
    int result = 0;
    size_t countOnes = 0;
    
    for(int i = A.size() - 1; i >= 0; --i)
    {
        if(A[i])
        {
            ++countOnes;
        }
        else
        {
            result += countOnes;
            if(result > 1000000000)
            {
                return -1;
            }
        }
    }
    
    return result;
}