// 03-树3 Tree Traversals Again (25分)
// 很奇怪，VScode中文件名为 "08.c" 会被识别为 C++ 文件。

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define MaxSize 30
#define Null -1

struct Node
{
    int Position;
    int Left;
    int Right;
};
typedef struct Node Tree;

struct StackNode
{
    struct Node *Data;
    int Rear;
};
typedef struct StackNode *Stack;

Stack CreatStack()
{
    Stack S = (Stack) malloc(sizeof(struct StackNode));
    S->Data = (Tree *) malloc(MaxSize * sizeof(Tree));
    S->Rear = -1;

    return S;
}

bool IsFullStack(Stack S)
{
    if (S->Rear == MaxSize - 1)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

bool PushStack(Stack S, struct Node X)
{
    if (IsFullStack(S))
    {
        return false;
    }
    else
    {
        S->Rear = S->Rear + 1;
        S->Data[S->Rear] = X;
        return true;
    }
}

bool IsEmptyStack(Stack S)
{
    if (S->Rear == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

struct Node PopStack(Stack S)
{
    struct Node res = {Null, Null, Null};
    if (IsEmptyStack(S))
    {
        return res;
    }
    else
    {
        res = S->Data[S->Rear];
        S->Rear = S->Rear - 1;
        return res;
    }
}

int BuildTree(Tree T[])
{
    int N;
    scanf("%d", &N);

    Stack S = CreatStack();
    Tree t = {0, Null, Null};
    T[0] = t;
    int root;
    int pointer = 0, i, operand; // pointer是上一个被操作的结点下标， operand是当前读入的结点下标
    char operator[4];

    scanf("\n%s %d", operator, &operand);
    t.Position = operand;
    PushStack(S, t);
    T[operand] = t;
    pointer = operand;
    root = operand;

    for(i=1; i<2*N; i++)
    {
        scanf("\n%s", operator);
        if (strcmp(operator, "Push") == 0)
        {
            scanf(" %d", &operand);
            t.Position = operand;
            PushStack(S, t);

            if (T[pointer].Left == Null)
            {
                T[pointer].Left = operand;
            }
            else
            {
                T[pointer].Right = operand;
            }

            T[operand] = t;
            pointer = operand;
        }
        else
        {
            t = PopStack(S);
            pointer = t.Position;
        }
    }

    return root;
}

void PostOrderTraversal(Tree T[], int root, int ROOT)
{
    if (root != Null)
    {
        PostOrderTraversal(T, T[root].Left, ROOT);
        PostOrderTraversal(T, T[root].Right, ROOT);
        if (T[root].Position != ROOT)
        {
            printf("%d ", T[root].Position);
        }
        else
        {
            printf("%d", T[root].Position);
        }
        
        
    }
    
}

int main()
{
    Tree T[31];
    int root;
    root = BuildTree(T);
    PostOrderTraversal(T, root, root);

    return 0;
}