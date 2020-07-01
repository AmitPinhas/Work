#include <stack>
#include <iostream>

using namespace std;

void InitStack(stack<int>& a_stack,int a_num);
int PopStack(stack<int>& a_stack);

int Vip(const int a_matrix[][3])
{
    stack<int> myStack;

    InitStack(myStack, 3);

    if(myStack.size() == 1)
    {
        return PopStack(myStack);
    }

    while(myStack.size() > 1) 
    {
        int a = PopStack(myStack);
        int b = PopStack(myStack);

        if(a_matrix[a][b])
        {
            myStack.push(b); 
        }
        else
        {
            myStack.push(a); 
        }
        
    }
    
    return PopStack(myStack);
}

int main()
{
    int a_matrix[][3]= { {0, 0, 0},
                         {1, 0, 1},
                         {1, 0, 0 } }; // 0 vip
                      

    cout<< "vip is -> " << Vip(a_matrix) << endl;                 
}

void InitStack(stack<int>& a_stack,int a_num)
{
    while (a_num-- > 0)
    {
        a_stack.push(a_num);
    }    
}

int PopStack(stack<int>& a_stack)
{
    int tmp = a_stack.top();
    a_stack.pop();
    return tmp;
}