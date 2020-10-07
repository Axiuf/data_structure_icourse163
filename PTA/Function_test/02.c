// 02-线性结构1 两个有序链表序列的合并 (15分)

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print( List L ); /* 细节在此不表；空链表将输出NULL */

List Merge( List L1, List L2 );

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

List Merge(List L1, List L2)
{
    List L, rear, temp;
    L = (List) malloc(sizeof(struct Node));
    rear = L;
    
    temp = L1;
    L1 = L1->Next;
    temp->Next = NULL;

    temp = L2;
    L2 = L2->Next;
    temp->Next = NULL;

    while (L1 && L2)
    {
        if (L1->Data < L2->Data)
        {
            rear->Next = L1;
            rear = L1;
            L1 = L1->Next;
        }
        else if (L1->Data > L2->Data)
        {
            rear->Next = L2;
            rear = L2;
            L2 = L2->Next;
        }
        else if (L1->Data == L2->Data)
        {
            rear->Next = L1;
            rear = L1;
            L1 = L1->Next;
            rear->Next = L2;
            rear = L2;
            L2 = L2->Next;
        }
    }
    
    while (L1)
    {
        rear->Next = L1;
        rear = L1;
        L1 = L1->Next;
    }
    while (L2)
    {
        rear->Next = L2;
        rear = L2;
        L2 = L2->Next;
    }

    return L;
}