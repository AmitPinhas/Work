int solution(int A, int B, int K) 
{
    int first(A);
    
    while(first % K != 0)
    {
        ++first;
    }
    
    int last(B);
    
    while(last % K != 0)
    {
        --last;
    }
    
    return (last - first) / K + 1;
}


int solution2(int A, int B, int K) 
{
    if(A % K != 0)
    {
        A += (K - (A % K));
    }
    
    B -= (B % K);

    return (B - A) / K + 1;
}



