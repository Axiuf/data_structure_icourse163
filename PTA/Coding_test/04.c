// 02-线性结构3 Reversing Linked List (25分)

#include <stdio.h>
#include <stdlib.h>

#define END -1


// 定义单链节点
typedef struct Node *PtrToNode;
struct Node
{
    int Address;
    int Data;
    int Next;
    PtrToNode Link;
};
typedef PtrToNode List;


// 初始化节点
List NewNode()
{
    List L;
    L = (List) malloc(sizeof(struct Node));

    L->Address = END;
    L->Data = 0;
    L->Next = END;
    L->Link = NULL;

    return L;
}


// 读入一个节点
List ReadNode()
{
    List L = NewNode();
    int address, data, next;

    scanf("%d %d %d", &address, &data, &next);
    L->Address = address;
    L->Data = data;
    L->Next = next;

    return L;
}


// 释放中间产物
void FreeNode(List L)
{
    List temp;
    while (L)
    {
        temp = L;
        L = L->Link;
        free(temp);
    }
}


int main()
{
    int Start, N, K;
    scanf("%d %d %d", &Start, &N, &K);  // 读入设置

    List front, rear;
    front = NewNode();
    rear = front;

    int i = N;
    while (i)
    {
        rear->Link = ReadNode();  // 按输入顺序写入一个链表
        rear = rear->Link;
        i--;
    }

    List front2;
    front2 = NewNode();
    rear = front2;

    List temp;
    temp = front;
    int next = Start;

    int n = 0;
    while (next != END)
    {
        while (1)
            {
                if (temp->Link->Address == next)
                {
                    rear->Link = temp->Link;
                    rear = rear->Link;
                    temp->Link = temp->Link->Link;  // 按照给定的头尾重构链表顺序

                    next = rear->Next;   
                    temp = front;
                    n++;
                    break;
                }

                temp = temp->Link;
            }
    }
    
    rear->Link = NULL;

    FreeNode(front->Link);
    front->Link = NULL;
    rear = front; // front为逆序后链表的头, rear为逆序后链表的尾

    List Stack, rStack; 
    Stack = NewNode(); 
    rStack = Stack;

    i = n / K;
    int k = K;

    // 逆序时对指针操作的同时对节点的Next也同样操作
    int temp_Next;
    front2->Next = front2->Link->Address;

    while (i)
    {
        // 将前K个元素暂存到一个堆栈中
        while (k)
        {
            temp = Stack->Link;
            temp_Next = Stack->Next;

            Stack->Link = front2->Link;
            Stack->Next = front2->Next;

            if (front2->Link->Link != NULL)
            {
                front2->Link = front2->Link->Link;  
                front2->Next = front2->Link->Address;
            }
            else
            {
                front2->Link = NULL;
                front2->Next = END;
            }

            Stack->Link->Link = temp;
            Stack->Link->Next = temp_Next;

            if (k == K)
            {
                rStack = Stack->Link;
            }

            k--;
        }
        
        rear->Link = Stack->Link;  // 将堆栈嫁接到最终链表的尾部
        rear->Next = Stack->Next;

        Stack->Link = NULL;
        Stack->Next = END;

        rear = rStack;
        k = K;
        i--;
    }
    
    rear->Link = front2->Link;  // 将剩余元素嫁接到最终链表的尾部
    rear->Next = front2->Next;

    free(Stack);
    free(front2);
    temp = front;
    front = front->Link;
    free(temp);

    while (front)
    {
        printf("%05d %d ", front->Address, front->Data);
        if (front->Next != -1)
        {
            printf("%05d\n", front->Next);
        }
        else
        {
            printf("-1\n");
        }
        
        front = front->Link;
    }

    return 0;
}