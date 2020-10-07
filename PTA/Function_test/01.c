// 01-复杂度3 二分查找 (20分)

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define NotFound 0
typedef int ElementType;

typedef int Position;
typedef struct LNode *List;
struct LNode {
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

List ReadInput(); /* 裁判实现，细节不表。元素从下标1开始存储 */
Position BinarySearch( List L, ElementType X );

int main()
{
    List L;
    ElementType X;
    Position P;

    L = ReadInput();
    scanf("%d", &X);
    P = BinarySearch( L, X );
    printf("%d\n", P);

    return 0;
}

List ReadInput()
{
    List L;
    L = (List) malloc(sizeof(struct LNode));

    int N, i = 1;
    scanf("%d", &N);
    while (i <= N)
    {
        scanf("%d", &(L->Data[i]));
        i++;
    }
    L->Last = N;

    return L;
}


// 这个算法一开始没想到，参考别人的。真的很简单，精妙。
// 提示我边界问题和特殊值的处理方法问题。在暴力判断特殊值并一一处理之前，要多考虑原本算法的通用性。
// 写算法的时候一开始就要考虑边界值，而不是先写完之后再根据测试结果去调整。
Position BinarySearch(List L, ElementType X)
{
    int res = NotFound;
    int a = 1, b = L->Last, c;
    c = (a + b) / 2;

    while (a <= b)
    {
        c = (a + b) / 2;
        if (X > L->Data[c])
        {
            a = c + 1;
        }
        else if (X < L->Data[c])
        {
            b = c - 1;
        }
        else if (X == L->Data[c])
        {
            res = c;
            break;
        }
    }

    return res;
}