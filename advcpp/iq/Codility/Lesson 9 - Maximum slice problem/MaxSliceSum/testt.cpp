// https://app.codility.com/demo/results/trainingK47MG4-SHJ/

#include<bits/stdc++.h> // INT_MIN

int solution(vector<int> &A) 
{
    const size_t vectorSize = A.size();
    
    if(1 == vectorSize)
    {
        return A[0];
    }
    
    int maxSlice = INT_MIN;
    
    int sum = 0;
    
    for(auto num: A)
    {
        sum += num;
        
        sum = max(num, sum);
        
        maxSlice = max(sum, maxSlice);
    }
    
    return maxSlice;
}