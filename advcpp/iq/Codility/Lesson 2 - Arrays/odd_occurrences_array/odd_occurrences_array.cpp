int solution(vector<int> &A)
{
    int result = 0;
    
    for(auto element : A)
    {
        result ^= element;
    }
    
    return result;
}

