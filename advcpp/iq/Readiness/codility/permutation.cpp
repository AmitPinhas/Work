int solution(vector<int> &A)
{
    const size_t sizeVector = A.size();

    for(auto element: A)
    {
        size_t index = abs(element);
        if(index <= sizeVector)
        {
            if(A[index] > 0)
            {
                A[index] *= -1;
            }

        }
    }

    for(auto a : A)
    {
        if(a > 0)
        {
            return 0;
        }
        else
        {
            a *= -1;
        }
        
    }

    return 1;
}