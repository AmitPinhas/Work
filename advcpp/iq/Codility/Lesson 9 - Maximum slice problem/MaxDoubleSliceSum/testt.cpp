// https://app.codility.com/demo/results/training93P44P-R2P/

#include <vector>
#include <iostream> // cout
#include<bits/stdc++.h> // INT_MIN

using namespace std;

int solution(vector<int> &A) 
{
    const size_t vectorSize = A.size();
    int maximalSum = 0;
    
    if(3 == vectorSize)
    {
        return maximalSum;
    }
    
    size_t tmpIndexStart = 0;
    size_t indexStart = 0;
    size_t indexEnd = vectorSize - 1;

    int maxSlice = INT_MIN;
    
    int sum = 0;
    
    for(size_t i = 1; i < vectorSize - 1; ++i)
    {
        sum += A[i];
        
        if(A[i] > sum)
        {
           tmpIndexStart = i - 1;
           sum = A[i];
        }
        
        if(sum > maxSlice)
        {
            indexStart = tmpIndexStart;
            indexEnd = i + 1;
            maxSlice = sum;
        }
    }    
    
    if(maxSlice <= 0)
    {
        return maximalSum;
    }
    
    int minMaxSlice = INT_MAX;
    
    for(size_t i = indexStart + 1; i < indexEnd; ++i)
    {
        if(A[i] < minMaxSlice)
        {
          minMaxSlice = A[i];  
        }
    }
    
    const int secondMaximalSum = maxSlice - minMaxSlice; 
    
    if((0 == indexStart) && (indexEnd == vectorSize - 1))
    {
        return secondMaximalSum;
    }
    
    maximalSum += maxSlice;
    
    int leftSum = 0;
    int rightSum = 0;
    int leftMax = 0;
    int rightMax = 0;
    
    for(int i = indexStart - 1; i > 0; --i)
    {
        leftSum += A[i];
        if(leftSum > leftMax)
        {
            leftMax = leftSum;
        }
    }
    
    for(size_t i = indexEnd + 1; i < vectorSize - 1; ++i)
    {
        rightSum += A[i];
        if(rightSum > rightMax)
        {
            rightMax = rightSum;
        }
    }    
    
    return max(maximalSum + max(leftMax, rightMax), secondMaximalSum);
}

// https://app.codility.com/demo/results/trainingZH3X5E-9E7/

int solution2(vector<int> &A) 
{
    const size_t vectorSize = A.size();
    int result = 0;
    
    if(3 == vectorSize)
    {
        return result;
    }
    
    vector<int> leftSum(vectorSize);
    vector<int> rightSum(vectorSize);
    
    for(size_t i = 1; i < vectorSize - 1; ++i)
    {
        const size_t indexRight = vectorSize - i - 1;
        
        leftSum[i] = max(leftSum[i - 1] + A[i], 0);
        rightSum[indexRight] = max(rightSum[indexRight + 1] + A[indexRight], 0);
    }
    
    for(size_t i = 1; i < vectorSize - 1; ++i)
    {
        result = max(result, leftSum[i - 1] + rightSum[i + 1]);
    }
    
    return result;
}

int main()
{
    vector<int> vec = {6, 1, 5, 6, 4, 2, 9, 4};

    cout << solution(vec) << endl;
}