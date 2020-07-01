// https://app.codility.com/demo/results/trainingQQRUQK-CHC/

int gcd(int a_a, int a_b);

int solution(int N, int M) 
{
    return N / gcd(N, M);
}

int gcd(int a_a, int a_b)
{
    if(a_a % a_b == 0)
    {
        return a_b;
    }
    
    return gcd(a_b, a_a % a_b);
}

// https://app.codility.com/demo/results/trainingR6UFT8-BQT/

int gcd(int a_a, int a_b);

int solution(int N, int M) 
{
    return N / gcd(N, M);
}

int gcd(int a_a, int a_b)
{
    while(a_a % a_b)
    {
        int tmp = a_b;
        a_b = a_a % a_b;
        a_a = tmp;
    }
    
    return a_b;
}

