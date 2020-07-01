#include <stdio.h>
#include <stdlib.h> /* free */

typedef struct Node
{
    int m_value;
    struct Node *m_next;

}Node;

void Print(Node* head, Node* stop)
{
    int flag = head == stop ? 1: 0;

    while(head && flag < 2)
    {
        printf("%d ", head->m_value);
        head = head->m_next;

        if(head == stop)
        {
            ++flag;
        }
    }

    putchar('\n');

}

void Removing(Node *a_node)
{
    if(!a_node)
    {
        return;
    }

    a_node->m_value = a_node->m_next->m_value;

    a_node->m_next = a_node->m_next->m_next;

    return;
}

int main()
{
    Node first;
    Node second;
    Node third;

    first.m_value = 1;
    second.m_value = 2;    
    third.m_value = 3;

    first.m_next = &second;
    second.m_next = &third;
    third.m_next = &first;

    Print(&first, &first);
    Removing(&second);
    Print(&first, &first);    

    return 0;
}