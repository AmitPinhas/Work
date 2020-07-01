#include <bits/stdc++.h> 

using namespace std;

int solution(int N) {
   
   int longestBinaryGap = 0;
   
   if(N < 0)
   {
       return -1;
   }
   
   if(N == 0)
   {
       return longestBinaryGap;
   }
   
   if(ceil(log2(N)) == floor(log2(N)))
   {
       return longestBinaryGap;
   }
   
   size_t numBits = CHAR_BIT * sizeof(int);
   
   for(size_t i = 0; N && i < numBits; ++i)
   {
       int tmpLength = 0;
       const int mask = 1;
       
       if(N & mask)
       {
           if(++i < numBits)
           {
               N >>=1;
           }
           else
           {
               break;
           }

           while(N && i < numBits && !(N & mask))
           {
               ++tmpLength;
               ++i;
               N >>=1;
           }
           if(N && i < numBits && N & mask)
           {
               if(tmpLength > longestBinaryGap)
               {
                   longestBinaryGap = tmpLength;
               }
           }
       }
       else
       {
           N >>=1;
       }
   }
   
   return longestBinaryGap;
}


int solution2(int N) {
   
   int longestBinaryGap = 0;
   
   if(N < 0)
   {
       return -1;
   }
   
   if(N == 0)
   {
       return longestBinaryGap;
   }
   
   if(ceil(log2(N)) == floor(log2(N)))
   {
       return longestBinaryGap;
   }
   
   size_t numBits = CHAR_BIT * sizeof(int);
   
   size_t i = 0;
   const int mask = 1;
   
   while(!(N & mask))
   {
       ++i;
       N >>=1;
   }
   
   while(N && i < numBits)
   {
       while(i < numBits && N & mask)
       {
           N >>=1;
           ++i;
       }
       
       int tmpLength = 0;
       
       while(N && i < numBits && !(N & mask))
       {
           ++i;
           ++tmpLength;
           N >>=1;
       }

        if(tmpLength > longestBinaryGap)
        {
            longestBinaryGap = tmpLength;
        }
        
        N >>=1;
       
   }
   
   return longestBinaryGap;
}

int solution3(int N)
{
    int longestBinaryGap = 0;

    while(!(N & 1))
    {
        N >>=1;
    }

    while(N)
    {
        while(N & 1)
        {
            N >>=1;
        }

        if(!N)
        {
            return longestBinaryGap;
        }

        int tmpLength = 0;

        while(!(N & 1))
        {
            ++tmpLength;
            N >>=1;
        }

        if(tmpLength > longestBinaryGap)
        {
            longestBinaryGap = tmpLength;
        }
    }

    return longestBinaryGap;
}

int main()
{
    cout << solution3(1041) << endl;
    int max = INT_MAX;
    cout << (max >>31) << endl; 
    return 1;
}