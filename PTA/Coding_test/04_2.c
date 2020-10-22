// 02-线性结构3 Reversing Linked List (25分)
// 用结构数组实现
// 直接用给定的5位数“地址”作为结构数组的下标
// 按照最直接的链表逆转的算法实现

#include <stdio.h>

#define MaxSize 100001
typedef int ElementType;
typedef int Position;


struct Node
{
    ElementType Data;
    Position Next;
};
typedef struct Node Link;


int main()
{
    Position root;
    int N, K;
    scanf("%d %d %d", &root, &N, &K);

    Link L[MaxSize];
    Position Address, Next;
    ElementType Data;
    int i;
    for (i = 0; i < N; i++)
    {
        scanf("%d %d %d", &Address, &Data, &Next);
        L[Address].Data = Data;
        L[Address].Next = Next;
    }
    Address = root;
    N = 0;
    while (Address != -1)
    {
        Address = L[Address].Next;
        N++;
    }

    Position Head = 100000, New, Old, temp;
    L[Head].Next = root;
    int k;
    for (i = 0; i < N / K; i++)
    {
        New = L[Head].Next;
        Old = L[New].Next;
        k = 1;

        while (k < K)
        {
            temp = L[Old].Next;
            L[Old].Next = New;
            New = Old;
            Old = temp;
            k++;
        }

        temp = L[Head].Next;
        L[temp].Next = Old;
        L[Head].Next = New;
        Head = temp;

        if (i == 0)
        {
            root = New;
        }
    }

    Address = root;
    while (L[Address].Next != -1)
    {
        printf("%05d %d %05d\n", Address, L[Address].Data, L[Address].Next);
        Address = L[Address].Next;
    }
    printf("%05d %d %d\n", Address, L[Address].Data, L[Address].Next);

    return 0;
}