// https://app.codility.com/demo/results/trainingHXJWQ6-Z6Y/

#include <cmath> // sqrt

void FillIndexPeaks(vector<size_t> &a_indexPeaks, const vector<int> &A);
bool IsMaxFlags(int a_numFlags, const vector<size_t> &a_indexPeaks);

int solution(vector<int> &A) 
{
    const size_t vectorSize = A.size();
    int flags = 0;
    
    if(vectorSize < 3)
    {
        return flags;
    }
    
    vector<size_t> indexPeaks;
    
    FillIndexPeaks(indexPeaks, A);
    
    const size_t peaksSize = indexPeaks.size();
    
    if(0 == peaksSize)
    {
        return flags;
    }
    
    if(1 == peaksSize)
    {
        ++flags;
        return flags;
    }
    
    flags = ceil(sqrt(vectorSize)) + 1;
    bool foundMaxFlags = false;
    
    while(!foundMaxFlags)
    {
        --flags;
        foundMaxFlags = IsMaxFlags(flags, indexPeaks);
    }
    
    return flags;
    
}

void FillIndexPeaks(vector<size_t> &a_indexPeaks, const vector<int> &A)
{
    const size_t vectorSize = A.size();
    
    for(size_t i = 1; i < vectorSize - 1; ++i)
    {
        if(A[i - 1] < A[i] && A[i + 1] < A[i])
        {
            a_indexPeaks.push_back(i);
        }
    }
    
    return;
}

bool IsMaxFlags(int a_numFlags, const vector<size_t> &a_indexPeaks)
{
    const size_t vectorSize = a_indexPeaks.size();
    size_t lastIndex = a_indexPeaks[0];
    const size_t minDis = a_numFlags; 
    --a_numFlags;
    
    for(size_t i = 0; i < vectorSize && a_numFlags > 0; ++i)
    {
        if(a_indexPeaks[i] - lastIndex >= minDis)
        {
            --a_numFlags;
            lastIndex = a_indexPeaks[i];
        }
    }
    
    if(a_numFlags == 0)
    {
        return true;
    }
    
    return false;
}