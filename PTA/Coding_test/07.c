// 03-树2 List Leaves (25分)

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MaxSize 10
#define Null -1


struct TreeNode
{
    int Left;
    int Right;
    int Position;
};
typedef struct TreeNode Tree;


int BuildTree(Tree T[])
{
    int N;
    scanf("%d", &N);

    int root = Null;

    if (N)
    {
        char L, R;
        int i, check[MaxSize];

        for (i=0; i<N; i++)
        {
            check[i] = 0;
        }
        for (i=0; i<N; i++)
        {
            scanf("\n%c %c", &L, &R);
            if (L != '-')
            {
                T[i].Left = L - '0';
                check[T[i].Left] = 1;
            }
            else
            {
                T[i].Left = Null;
            }

            if (R != '-')
            {
                T[i].Right = R - '0';
                check[T[i].Right] = 1;
            }
            else
            {
                T[i].Right = Null;
            }

            T[i].Position = i;
        }

        for (i=0; i<N; i++)
        {
            if (check[i] == 0)
            {
                root = i;
                break;
            }
        }
    }
    
    return root;
}


struct QueueNode {
    Tree *Data;     /* 存储元素的数组 */
    int Front, Rear;  /* 队列的头、尾指针 */
    int Max;
};
typedef struct QueueNode *Queue;


Queue CreateQueue()
{
    Queue Q = (struct QueueNode *) malloc(sizeof(struct QueueNode));
    Q->Data = (Tree *)malloc(MaxSize * sizeof(Tree));
    Q->Front = Q->Rear = 0;
    Q->Max = MaxSize;
    return Q;
}

bool IsFull(Queue Q)
{
    return ((Q->Rear + 1) % Q->Max == Q->Front);
}
 
bool AddQ(Queue Q, Tree X)
{
    if (IsFull(Q)) {
        return false;
    }
    else {
        Q->Rear = (Q->Rear + 1) % Q->Max;
        Q->Data[Q->Rear] = X;
        return true;
    }
}
 
bool IsEmptyQ(Queue Q)
{
    return (Q->Front == Q->Rear);
}
 
Tree DeleteQ(Queue Q)
{
    Tree error = {Null, Null, Null};
    if (IsEmptyQ(Q)) { 
        return error;
    }
    else  {
        Q->Front = (Q->Front + 1) % Q->Max;
        return  Q->Data[Q->Front];
    }
}


int LevelOrderTraversal(Tree T[], int root, int leaf[])
{
    if (root == Null)
    {
        return;
    }

    Queue Q = CreateQueue();
    AddQ(Q, T[root]);
    Tree X;

    int numleaf = 0;
    while (IsEmptyQ(Q) != 1)
    {
        X = DeleteQ(Q);
        if (X.Left != Null)
        {
            AddQ(Q, T[X.Left]);
        }
        if (X.Right != Null)
        {
            AddQ(Q, T[X.Right]);
        }
        if ((X.Left == Null) && (X.Right == Null))
        {
            leaf[numleaf] = X.Position;
            numleaf++;
        }
    }

    return numleaf;
}

int main()
{
    int root;
    Tree T[MaxSize];

    root = BuildTree(T);
    int leaf[MaxSize] = {Null}, numleaf, i;
    numleaf = LevelOrderTraversal(T, root, leaf);

    if (leaf[0] != Null)
    {
        printf("%d", leaf[0]);
    }
    for(i=1; i<numleaf; i++)
    {
        printf(" %d", leaf[i]);
    }

    return 0;
}