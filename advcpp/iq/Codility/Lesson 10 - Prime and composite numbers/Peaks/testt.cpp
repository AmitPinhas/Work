// https://app.codility.com/demo/results/training3676FB-KFY/

void FillIndexPeaks(vector<size_t> &a_indexPeaks, const vector<int> &A);
bool IsMaxBlocks(int a_numBlocks, const vector<size_t> &a_indexPeaks, size_t a_vectorSize);

int solution(vector<int> &A) 
{
    const size_t vectorSize = A.size();
    int blocks = 0;
    
    if(vectorSize < 3)
    {
        return blocks;
    }
    
    vector<size_t> indexPeaks;
    
    FillIndexPeaks(indexPeaks, A);
    
    const size_t peaksSize = indexPeaks.size();
    
    if(0 == peaksSize)
    {
        return blocks;
    }   
    
    if(1 == peaksSize)
    {
        ++blocks;
        return blocks;
    }
    
    bool foundMaxBlock = false;
    blocks = peaksSize + 1;
    
    while(!foundMaxBlock)
    {
        --blocks;
        
        while(vectorSize % blocks != 0)
        {
            --blocks;
        }
        
        foundMaxBlock = IsMaxBlocks(blocks, indexPeaks, vectorSize);
    }
    
    return blocks;
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

bool IsMaxBlocks(int a_numBlocks, const vector<size_t> &a_indexPeaks, size_t a_vectorSize)
{
    const size_t vectorSize = a_indexPeaks.size();
    size_t minIndex = 0;
    const size_t blockSize = a_vectorSize / a_numBlocks;
    size_t maxIndex = blockSize - 1;

    for(size_t i = 0; i < vectorSize; ++i)
    {
        if(a_indexPeaks[i] >= minIndex && a_indexPeaks[i] <= maxIndex)
        {
            --a_numBlocks;
            minIndex = maxIndex + 1;
            maxIndex += blockSize; 
        }
    }
    
    if(a_numBlocks == 0)
    {
        return true;
    }
    
    return false;
}

