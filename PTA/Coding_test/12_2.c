// 05-树7 堆中的路径 (25分)
// 构建堆的时候采用全部读入后再调整的方法
// 这个方法的问题在于，会构建出一个同构的堆，与按照输入顺序构建的堆不完全一样

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

void PercUp(MinHeap H, int p)
{ /* 给定根节点的下标，调整这个子树的结构满足最小堆的有序性 */
  /* 实际上是为给定的根节点找到合适的位置 */
    int Parent, Child;
    ElementType X;

    X = H->Data[p];
    for (Parent = p; Parent * 2 <= H->Size; Parent = Child)
    {
        Child = Parent * 2;
        if ((Child < H->Size) && (H->Data[Child] > H->Data[Child + 1]))
        {
            Child++;
        }
        if (X <= H->Data[Child])
        {
            break;
        }
        else
        {
            H->Data[Parent] = H->Data[Child];
        }
    }
    H->Data[Parent] = X;
}

void Build(MinHeap H)
{ /* 调整中的元素，使其满足最小堆的有序性 */
    int i;

    for(i = H->Size / 2; i >= 1; i--)
    {
        PercUp(H, i);
    }
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
    for (i = 1; i <= N; i++)
    { /* 依次读入数据并插入到最小堆中 */
        scanf("%d", &X);
        H->Data[i] = X;
        H->Size++;
    }
    Build(H);

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