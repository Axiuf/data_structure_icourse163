// 03-树3 Tree Traversals Again (25分)

#include <stdio.h>
#include <stdlib.h>

struct SNode
{
    int *data;
    int front, rear;
    int size;
};
typedef struct SNode *Stack;

Stack CreateStack(int size)
{
    Stack S = (Stack) malloc(sizeof(struct SNode));
    S->data = (int *) malloc((size + 1) * sizeof(int));
    S->front = S->rear = 0;
    S->size = size;

    return S;
}

void Push(Stack S, int X)
{
    if (S->rear < S->size)
    {
        S->rear++;
        S->data[S->rear] = X;
    }
}

int Pop(Stack S)
{
    int X;
    if (S->rear > S->front)
    {
        X = S->data[S->rear];
        S->rear--;
    }

    return X;
}

void Solve(int PRE[], int pre_i, int IN[], int in_i, int POST[], int post_i, int n)
{
    if (n == 0)
    {
        return;
    }
    if (n == 1)
    {
        POST[post_i] = PRE[pre_i];
        return;
    }

    int root, i;
    root = PRE[pre_i];
    POST[post_i + n - 1] = root;
    for (i = 0; i < n; i++)
    {
        if (IN[in_i + i] == root)
        {
            break;
        }
    }
    
    Solve(PRE, pre_i + 1, IN, in_i, POST, post_i, i);
    Solve(PRE, pre_i + i + 1, IN, in_i + i + 1, POST, post_i + i, n - i - 1);
}

int main()
{
    int N;
    scanf("%d", &N);

    Stack S = CreateStack(N);

    int IN[N], PRE[N], POST[N], i, X;
    int in_i = 0, pre_i = 0;
    char operator[4];
    for (i = 0; i < 2 * N; i++)
    {
        scanf("\n%s", operator);
        if (operator[1] == 'u')
        {
            scanf(" %d", &X);
            PRE[pre_i] = X;
            pre_i++;
            Push(S, X);
        }
        else if (operator[1] == 'o')
        {
            X = Pop(S);
            IN[in_i] = X;
            in_i++;
        }
    }

    int post_i = 0;
    pre_i = in_i = 0;
    Solve(PRE, pre_i, IN, in_i, POST, post_i, N);

    for (i = 0; i < N - 1; i++)
    {
        printf("%d ", POST[i]);
    }
    printf("%d", POST[i]);

    return 0;
}