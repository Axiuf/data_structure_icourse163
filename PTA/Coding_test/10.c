// 04-树5 Root of AVL Tree (25分)
// 平衡二叉树的构建，插入，和自平衡

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct AVLNode *Position;
typedef Position AVLTree;
struct AVLNode
{
    ElementType Data;
    AVLTree Left;
    AVLTree Right;
    int Height; // 子树的高度
};

int Max(int a, int b)
{
    return a > b ? a : b;
}

int GetHeight(AVLTree A)
{
    if (!A)
    {
        return -1;
    }

    if (!A->Left && !A->Right)
    {
        A->Height = 0;
    }
    else
    {
        A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
    }

    return A->Height;
}

AVLTree SingleLeftRotation(AVLTree A)
{
    AVLTree B = A->Left;
    A->Left = B->Right;
    B->Right = A;

    A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
    B->Height = Max(GetHeight(B->Left), A->Height) + 1;

    return B;
}

AVLTree SingleRightRotation(AVLTree A)
{
    AVLTree B = A->Right;
    A->Right = B->Left;
    B->Left = A;

    A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
    B->Height = Max(GetHeight(B->Right), A->Height) + 1;

    return B;
}

AVLTree LeftRightRotation(AVLTree A)
{
    A->Left = SingleRightRotation(A->Left);
    
    return SingleLeftRotation(A);
}

AVLTree RightLeftRotation(AVLTree A)
{
    A->Right = SingleLeftRotation(A->Right);
    
    return SingleRightRotation(A);
}

AVLTree Insert(AVLTree A, ElementType X)
{
    if (A == NULL)
    {
        A = (AVLTree) malloc(sizeof(struct AVLNode));
        A->Data = X;
        A->Height = 0;
        A->Left = NULL;
        A->Right = NULL;
    }
    else if (A->Data < X)
    {
        A->Right = Insert(A->Right, X);

        if ((GetHeight(A->Left) - GetHeight(A->Right)) == -2)
        {
            if (A->Right->Data < X)
            {
                A = SingleRightRotation(A);
            }
            else
            {
                A = RightLeftRotation(A);
            }
        }
    }
    else if (A->Data > X)
    {
        A->Left = Insert(A->Left, X);

        if ((GetHeight(A->Left) - GetHeight(A->Right)) == 2)
        {
            if (A->Left->Data > X)
            {
                A = SingleLeftRotation(A);
            }
            else
            {
                A = LeftRightRotation(A);
            }
        }
    }

    A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;

    return A;
}

int main()
{
    int N, X;
    scanf("%d", &N);

    AVLTree A = NULL;
    while (N)
    {
        scanf("%d", &X);
        A = Insert(A, X);
        N--;
    }

    printf("%d", A->Data);

    return 0;
}