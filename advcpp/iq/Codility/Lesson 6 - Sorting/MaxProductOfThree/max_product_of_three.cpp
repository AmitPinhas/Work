// https://app.codility.com/demo/results/trainingDGAG79-RCS/

#include <algorithm> // sort
#include<bits/stdc++.h> // INT_MAX

int solution(vector<int> &A) 
{
    sort(A.begin(), A.end());
    
    const size_t vectorSize = A.size();
    
    int firstCandidate = A[vectorSize - 1] * A[vectorSize - 2] * A[vectorSize - 3];
    
    if(A[0] > 0 || A[vectorSize - 1] < 0 || (A[0] < 0 && A[1] > 0))
    {
        return firstCandidate;
    }

    int secondCandidate = A[vectorSize - 1] * A[0] * A[1] ;
    
    return max(firstCandidate, secondCandidate);
}

// https://app.codility.com/demo/results/trainingE5HTW6-W5H/

int solution2(vector<int> &A) 
{
    int min1 = 0;
    int min2 = 0;
    int max1 = INT_MIN;
    int max2 = INT_MIN;
    int max3 = INT_MIN;
    
    for(auto num: A)
    {
        if(num < 0)
        {
            if(num < min1)
            {
                min2 = min1;
                min1 = num;
            }
            else if(num < min2)
            {
                min2 = num;
            }
        }
        if(num > max1)
        {
            max3 = max2;
            max2 = max1;
            max1 = num;
        }
        else if(num > max2)
        {
            max3 = max2;
            max2 = num;
        }
        else if(num > max3)
        {
            max3 = num;
        }
    }
    
    return max(max1 * max2 * max3, max1 * min1 * min2);
}



