// 04-树4 是否同一棵二叉搜索树 (25分)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// 定义二叉搜索树的结构，基本的操作函数
// 定义二叉搜索树的结构
typedef struct TreeNode *Tree;
struct TreeNode
{
    int V;
    Tree Left, Right;
    int Flag; // 设一个标记表示单个结点是否被访问和比较过
};

Tree NewNode(int V)
{
    Tree T;
    T = (Tree) malloc(sizeof(struct TreeNode));
    T->V = V;
    T->Left = NULL;
    T->Right = NULL;
    T->Flag = 0;

    return T;
}

Tree InsetTree(Tree T, int V)
{
    if (T == NULL)
    {
        T = NewNode(V);
    }
    else if (T->V > V)
    {
        T->Left = InsetTree(T->Left, V);
    }
    else if (T->V < V)
    {
        T->Right = InsetTree(T->Right, V);
    }

    return T;
}

Tree BuildTree(int N)
{
    int V, i;
    scanf("%d", &V);

    Tree T;
    T = NewNode(V);

    for (i = 1; i < N; i++)
    {
        scanf("%d", &V);
        T = InsetTree(T, V);
    }

    return T;
}


// 给定一个数， 判断这个数在树中是否按原顺序存放
bool Check(Tree T, int V)
{
    if (T == NULL)
    {
        return false;
    }

    if (T->Flag == 1)
    {
        if (T->V > V)
        {
            return Check(T->Left, V);
        }
        else if (T->V < V)
        {
            return Check(T->Right, V);
        }
        else if (T->V == V)
        {
            return false;
        }
    }
    else if (T->Flag == 0)
    {
        if (T->V == V)
        {
            T->Flag = 1;
            return true;
        }
        else
        {
            return false;
        }
    }
    
}

// 判别序列是否与已构建的树一致
int IsSame(Tree T, int N)
{
    int V, i, flag = 1;

    for (i = 0; i < N; i++)
    {
        scanf("%d", &V);

        if (flag == 0)
        {
            continue;
        }
        else if (!Check(T, V))
        {
            flag = 0;
        }
    }
    
    return flag;
}

void ResetFlag(Tree T)
{
    if (T->Left)
    {
        ResetFlag(T->Left);
    }
    if (T->Right)
    {
        ResetFlag(T->Right);
    }
    
    T->Flag = 0;
}

void FreeTree(Tree T)
{
    if (T->Left)
    {
        FreeTree(T->Left);
    }
    if (T->Right)
    {
        FreeTree(T->Right);
    }
    
    free(T);
}

// 主函数结构
int main()
{
    int N, L, i;
    scanf("%d", &N); // 无论如何都会存在第一个N，首先读入

    Tree T;
    while (N)
    {
        scanf("%d", &L); // N不为0，才读入L
        T = BuildTree(N); // 读入第一行并构建一颗二叉树
        for (i = 0; i < L; i++)
        {
            if (IsSame(T, N)) // 读入第二行并判断与第一行是否相同
            {
                printf("Yes\n");
            }
            else
            {
                printf("No\n");
            } 

            ResetFlag(T); // 清除树中的标记Flag
        }

        FreeTree(T);
        scanf("%d", &N); // 当前序列处理完之后，再重新读入N处理下一组
    }

    return 0;
}