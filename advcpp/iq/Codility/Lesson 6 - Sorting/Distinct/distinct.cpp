// https://app.codility.com/demo/results/training4ZV2QC-XUS/

#include <algorithm> // sort
#include <set>
#include <unordered_set>

int solution(vector<int> &A) 
{
    const size_t vectorSize = A.size();
    int result = 0;

    if(0 == vectorSize)
    {
        return result;
    }
    
    if(1 == vectorSize)
    {
        return ++result;
    }
    
    sort(A.begin(), A.end());
    
    for(size_t i = 0; i < vectorSize - 1; ++i)
    {
        if(A[i + 1] != A[i])
        {
            ++result;
        }
    }
    
    return ++result;
}

// https://app.codility.com/demo/results/trainingYEXTDC-829/

int solution2(vector<int> &A) 
{
    set<int> distincts;
    
    for(auto num: A)
    {
        distincts.insert(num);
    }
    
    return distincts.size();
}

// https://app.codility.com/demo/results/trainingC8Y8WA-SEG/

int solution3(vector<int> &A) 
{
    unordered_set<int> distincts;
    
    for(auto num: A)
    {
        distincts.insert(num);
    }
    
    return distincts.size();
}