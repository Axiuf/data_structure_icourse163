// 05-树8 File Transfer (25分)
// 这道题考察的是集合的构建和运算


#include <stdio.h>
#include <string.h>

typedef int ElementType;
typedef int SetName; /* 默认用根结点的下标作为集合名称 */

SetName FindSet(ElementType S[], int x)
{
    SetName Set;
    Set = x;
    while (S[Set] > 0)
    {
        Set = S[Set];
    }

    return Set;
}

void AddConnection(ElementType S[], int x, int y)
{
    SetName SetX = FindSet(S, x), SetY = FindSet(S, y);
    
    if (SetX != SetY)
    {
        if (S[SetX] < S[SetY])
        {
            S[SetX] = S[SetX] + S[SetY];
            S[SetY] = SetX;
        }
        else
        {
            S[SetY] = S[SetX] + S[SetY];
            S[SetX] = SetY;
        }
        
    }
}

void CheckConnection(ElementType S[], int x, int y)
{
    SetName SetX = FindSet(S, x), SetY = FindSet(S, y);

    if (SetX == SetY)
    {
        printf("yes\n");
    }
    else
    {
        printf("no\n");
    }
}

int CheckComponents(ElementType S[], int Size)
{
    int i, components = 0;
    for (i = 1; i <= Size; i++)
    {
        if (S[i] < 0)
        {
            components++;
        }
    }

    return components;
}


int main()
{
    int N;
    scanf("%d", &N);

    ElementType S[N+1]; /* 用一个数组表示所有的计算机，数组表示下标表示编号，数组值表示集合根节点 */
    memset(S, -1, sizeof(S));

    char operator;
    int x, y;
    scanf("\n%c", &operator);
    
    while (operator != 'S')
    {
        if (operator == 'I')
        {
            scanf(" %d %d", &x, &y);
            AddConnection(S, x, y);
        }
        else if (operator == 'C')
        {
            scanf(" %d %d", &x, &y);
            CheckConnection(S, x, y);
        }

        scanf("\n%c", &operator);
    }
    
    int i = CheckComponents(S, N+1);
    if (i == 1)
    {
        printf("The network is connected.\n");
    }
    else
    {
        printf("There are %d components.", i);
    }
    
    return 0;
}