// 03-树1 树的同构 (25分)

#include <stdio.h>

#define MaxTree 10
#define Null -1
typedef int Tree;
typedef char ElementType;


struct TreeNode{ /* 树结点定义 */
    ElementType Element; /* 结点数据 */
    Tree Left;     /* 指向左子树 */
    Tree Right;    /* 指向右子树 */
}T1[MaxTree], T2[MaxTree];


Tree BuildTree(struct TreeNode T[])
{
    int N;
    scanf("%d", &N);

    int Root = Null, check[MaxTree];
    if (N)
    {
        int i;
        char cl, cr;

        for (i=0; i<N; i++) check[i] = 0;
        for (i=0; i<N; i++)
        {
            scanf("\n%c %c %c", &T[i].Element, &cl, &cr);
            
            if (cl != '-')
            {
                T[i].Left = cl - '0';
                check[T[i].Left] = 1;
            }
            else
            {
                T[i].Left = Null;
            }

            if (cr != '-')
            {
                T[i].Right = cr - '0';
                check[T[i].Right] = 1;
            }
            else
            {
                T[i].Right = Null;
            }
            
        }

        for (i=0; i<N; i++)
        {
            if (check[i] == 0)
            {
                Root = i;
                break;
            }
        } 
    }

    return Root;
}


int Isomorphic(Tree R1, Tree R2)
{
    if ((R1 == Null) && (R2 == Null))
    {
        return  1;
    }
    if (((R1 == Null) && (R2 != Null)) || ((R1 != Null) && (R2 == Null)))
    {
        return  0;
    }
    if (T1[R1].Element != T2[R2].Element)
    {
        return  0;
    }
    if ((T1[R1].Left == Null) && (T2[R2].Left == Null))
    {
        return  Isomorphic(T1[R1].Right, T2[R2].Right);
    }
    if (((T1[R1].Left != Null) && (T2[R2].Left != Null)) && (T1[T1[R1].Left].Element == T2[T2[R2].Left].Element))
    {
        return  Isomorphic(T1[R1].Left, T2[R2].Left) && Isomorphic(T1[R1].Right, T2[R2].Right);
    }
    else
    {
        return  Isomorphic(T1[R1].Left, T2[R2].Right) && Isomorphic(T1[R1].Right, T2[R2].Left);
    }
}

int main()
{
    Tree R1, R2; // 定义头结点
    R1 = BuildTree(T1);
    R2 = BuildTree(T2);

    if (Isomorphic(R1, R2)) printf("Yes\n");
    else printf("No\n");

    return 0;
}