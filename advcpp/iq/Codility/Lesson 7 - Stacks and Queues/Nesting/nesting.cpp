// https://app.codility.com/demo/results/trainingY35J9M-CHF/

int solution(string &S) 
{
    int result = 1;
    size_t leftBracket = 0;
    
    for(auto element: S)
    {
        if(element == '(')
        {
            ++leftBracket;
        }
        else
        {
            if(0 == leftBracket)
            {
                result = 0;
                break;
            }
            --leftBracket;
        }
    }
    
    if(leftBracket != 0)
    {
        result = 0;
    }
    
    return result;
}

