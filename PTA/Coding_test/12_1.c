// 05-树7 堆中的路径 (25分)
// 构建堆的时候采用插入法
// 每读入一个节点即插入到合适位置

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int ElementType;

struct HeapNode
{ /* 构建堆的基本结构 */
    ElementType *Data;
    int Size;
    int Capacity;
};
typedef struct HeapNode *Heap;
typedef Heap MinHeap;

#define MinData -10001

MinHeap CreatHeap(int MaxSize)
{ /* 初始化一个最小堆，其中数组下标为0的节点设一个最小值 */
    MinHeap H;
    H = (MinHeap) malloc(sizeof(struct HeapNode));
    H->Data = (ElementType *) malloc((MaxSize + 1) * sizeof(ElementType));
    H->Size = 0;
    H->Capacity = MaxSize;
    H->Data[0] = MinData;

    return H;
}

bool IsFull(MinHeap H)
{ /* 判断是否为满 */
    if (H->Size == H->Capacity)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool IsEmpty(MinHeap H)
{ /* 判断是否为空 */
    if (H->Size == 0)
    {
        return true;
    }
    else
    {
        return false;
    }  
}

bool Insert(MinHeap H, ElementType X)
{
    if (IsFull(H))
    {
        return false;
    }

    H->Size++;

    int i;
    for (i = H->Size; H->Data[i / 2] > X; i = i / 2)
    {
        H->Data[i] = H->Data[i / 2];
    }
    H->Data[i] = X;

    return true;
}

bool PrintRoot(MinHeap H, int n)
{
    if (n > H->Size || n <= 0)
    {
        return false;
    }

    while (n > 1)
    {
        printf("%d ", H->Data[n]);
        n = n / 2;
    }
    if (n == 1)
    {
        printf("%d\n", H->Data[n]);
    }

    return true;
}

int main()
{
    int N, M;
    scanf("%d %d/n", &N, &M);

    int i;
    ElementType X;
    MinHeap H = CreatHeap(N);
    for (i = 0; i < N; i++)
    { /* 依次读入数据并插入到最小堆中 */
        scanf("%d", &X);
        if (!Insert(H, X))
        {
            printf("Heap is full!\n");
            break;
        }
    }

    int n;
    for (i = 0; i < M; i++)
    { /* 依次读入下标并打印路径 */
        scanf("%d", &n);
        if (!PrintRoot(H, n))
        {
            printf("%d is a invalid index!\n", n);
            break;
        }
    }

    return 0;
}