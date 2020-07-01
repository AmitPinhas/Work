

int solution(int X, int Y, int D) 
{
    int minimalJmp = (Y - X) / D;
    
    if((Y - X) % D != 0)
    {
        ++minimalJmp;
    }
    
    return minimalJmp;
}

