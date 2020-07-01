// https://app.codility.com/demo/results/trainingQXXNUH-C5S/

int solution(vector<int> &A) 
{
    const size_t vectorSize = A.size();
    int maxProfit = 0;
    
    if(vectorSize < 2)
    {
        return maxProfit;
    }
    
    int minCurrElement = A[0];
    
    for(auto num: A)
    {
        minCurrElement = min(num, minCurrElement);
        
        maxProfit = max(maxProfit, num - minCurrElement);
    }
    
    return maxProfit;
}