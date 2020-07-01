vector<int> solution(string &S, vector<int> &P, vector<int> &Q) 
{
    vector<size_t> counterA;
    vector<size_t> counterC;
    vector<size_t> counterG;
    
    size_t A = 0;
    size_t C = 0;
    size_t G = 0;
    
    for(auto element : S)
    {
        if(element == 'A')
        {
            ++A;
        }
        if(element == 'C')
        {
            ++C;
        }
        if(element == 'G')
        {
            ++G;
        }      
        
        counterA.push_back(A);
        counterC.push_back(C);
        counterG.push_back(G);        
    }
    
    vector<int> result;
    
    for(size_t i = 0; i < P.size(); ++i)
    {
        size_t indexFirst = P[i];
        size_t indexLast = Q[i];
        int num;
        bool flag = true;
        
        if(S[indexFirst] == 'A' || counterA[indexLast] - counterA[indexFirst] > 0)
        {
            num = 1;
            flag = false;
        }
        else if(S[indexFirst] == 'C' || counterC[indexLast] - counterC[indexFirst] > 0)
        {
            num = 2;
            flag = false;
        }
        else if(S[indexFirst] == 'G' || counterG[indexLast] - counterG[indexFirst] > 0)
        {
            num = 3;
            flag = false;
        }      
        if(flag)
        {
            num = 4;
        }
        result.push_back(num);
    }
    
    return result;
}