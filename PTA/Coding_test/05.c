// 02-线性结构4 Pop Sequence (25分)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERROR 0 


// 定义数组堆栈结构
struct SNode {
    int *Data;    /* 存储元素的数组的指针 */
    int Top;      /* 栈顶指针 */
    int MaxSize;  /* 堆栈最大容量 */
};
typedef struct SNode *Stack;


// 创建堆栈
Stack CreateStack(int MaxSize)
{
    Stack S = (Stack) malloc(sizeof(struct SNode));
    S->Data = (int *) malloc(MaxSize * sizeof(int));
    S->Top = -1;
    S->MaxSize = MaxSize;

    return S;
}


bool IsFull(Stack S)
{
    return (S->Top == S->MaxSize-1);
}


bool Push(Stack S, int X)
{
    if (IsFull(S)) 
    {
        return false;
    }
    else {
        S->Data[S->Top + 1] = X;
        S->Top++;

        return true;
    }
}


bool IsEmpty(Stack S)
{
    return (S->Top == -1);
}


int Pop(Stack S)
{
    int X;

    if (IsEmpty(S))
    {
        return ERROR; /* ERROR是ElementType的特殊值，标志错误 */
    }
    else
    {
        X = S->Data[S->Top];
        S->Top--;

        return (X);
    }
}


int isOK(int Seq[], int N, int M)
{
    int ok = 1;
    Stack S = CreateStack(M);
    int i = 0;
    int n = 1;
    while (i < N && ok == 1)
    {
        if (IsEmpty(S))
        {
            Push(S, n);
            n++;
        }

        if (Seq[i] == S->Data[S->Top])
        {
            Pop(S);
            i++;
        }
        else if (Seq[i] > S->Data[S->Top])
        {
            if (!Push(S, n))
            {
                ok = 0;
            }
            n++;
        }
        else if (Seq[i] < S->Data[S->Top])
        {
            ok = 0;
        }
    }

    return ok;
}


int main()
{
    int M, N, K;
    scanf("%d %d %d", &M, &N, &K);

    int i, *Seq, *Res;
    Seq = (int *) malloc(N * sizeof(int));
    Res = (int *) malloc(K * sizeof(int));

    int k = 0;
    while (k < K)
    {
        i = 0;
        while (i < N)
        {
            scanf("%d", &Seq[i]);
            i++;
        }

        Res[k] = isOK(Seq, N, M);

        k++;
    }

    for (i=0; i<K; i++)
    {
        if (Res[i] == 1)
        {
            printf("YES\n");
        }
        else if (Res[i] == 0)
        {
            printf("NO\n");
        }
    }

    return 0;
}