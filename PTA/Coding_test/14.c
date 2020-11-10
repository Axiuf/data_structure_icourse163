// 05-树9 Huffman Codes (30分)
// 最小堆的建立过程，适合用数组
// 哈夫曼树的建立过程，适合用链表
// 最后用数组存储链表结点的指针，用数组下标表示最小堆中结点之间的关系，用链表结点内部的指针表示哈夫曼树结点之间的关系

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct DataNode
{
    char Character;
    int Frequency;
};
typedef struct DataNode Data;

typedef struct TreeNode *HuffmanTree;
struct TreeNode
{
    char Character;
    int Frequency;
    HuffmanTree Left, Right;
};

struct HeapStruct
{
    HuffmanTree *Elements; // 用数组存储结构体指针
    int Size;
    int Capacity;
};
typedef struct HeapStruct *MinHeap;

MinHeap CreateHeap(int MaxSize)
{
    MinHeap H = (MinHeap) malloc(sizeof(struct HeapStruct));
    H->Elements = (HuffmanTree *) malloc((MaxSize + 1) * sizeof(struct TreeNode));
    H->Size = 0;
    H->Capacity = MaxSize;
    // H->Elements = (HuffmanTree *) malloc((MaxSize + 1) * sizeof(struct TreeNode));
    int i;
    for (i = 0; i <= H->Capacity; i++)
    {
        H->Elements[i] = (HuffmanTree) malloc(sizeof(struct TreeNode));
        H->Elements[i]->Left = H->Elements[i]->Right = NULL;
    }
    H->Elements[0]->Character = '&';
    H->Elements[0]->Frequency = -1; // 第一个元素，即头节点表示哨兵，不实际存储数据

    return H;
}

void ReadData(MinHeap H, Data D[])
{
    int i;
    for (i = 1; i < H->Capacity; i++)
    {
        scanf("%c %d ", &H->Elements[i]->Character, &H->Elements[i]->Frequency);
        H->Size++;
        D[i].Character = H->Elements[i]->Character;
        D[i].Frequency = H->Elements[i]->Frequency;
    }
    scanf("%c %d", &H->Elements[i]->Character, &H->Elements[i]->Frequency);
    H->Size++;
    D[i].Character = H->Elements[i]->Character;
    D[i].Frequency = H->Elements[i]->Frequency;
}

void PercDown(MinHeap H, int p)
{ 
    int Parent, Child;
    HuffmanTree X;

    X = H->Elements[p];
    for (Parent = p; Parent * 2 <= H->Size; Parent = Child)
    {
        Child = Parent * 2;
        if ((Child < H->Size) && (H->Elements[Child]->Frequency > H->Elements[Child + 1]->Frequency))
        {
            Child++;
        }
        if (X->Frequency <= H->Elements[Child]->Frequency)
        {
            break;
        }
        else
        {
            H->Elements[Parent] = H->Elements[Child];
        }
    }
    H->Elements[Parent] = X;
}

void BuildMinHeap(MinHeap H)
{
    int i;
    for (i = H->Size / 2; i >= 1; i--)
    {
        PercDown(H, i);
    }
}

HuffmanTree DeleteMin(MinHeap H)
{
    int Parent, Child;
    HuffmanTree MinItem, temp;

    MinItem = H->Elements[1];
    temp = H->Elements[H->Size];
    H->Size--;
    for (Parent = 1; Parent * 2 <= H->Size; Parent = Child)
    {
        Child = Parent * 2;
        if ((Parent * 2 != H->Size) && (H->Elements[Child]->Frequency > H->Elements[Child + 1]->Frequency))
        {
            Child++;
        }
        if (temp->Frequency <= H->Elements[Child]->Frequency)
        {
            break;
        }
        else
        {
            H->Elements[Parent] = H->Elements[Child];
        }
    }

    H->Elements[Parent] = temp;

    return MinItem;
}

void Insert(MinHeap H, HuffmanTree T)
{
    int i;

    H->Size++;
    i = H->Size;
    for ( ; H->Elements[i / 2]->Frequency > T->Frequency; i = i / 2)
    {
        H->Elements[i] = H->Elements[i / 2];
    }
    H->Elements[i] = T;
}


HuffmanTree Huffman(MinHeap H)
{
    BuildMinHeap(H);

    int i;
    HuffmanTree T;
    for (i = 1; i < H->Capacity; i++)
    {
        T = (HuffmanTree) malloc(sizeof(struct TreeNode));
        T->Left = DeleteMin(H);
        T->Right = DeleteMin(H);
        T->Frequency = T->Left->Frequency + T->Right->Frequency;
        T->Character = '&';
        Insert(H, T);
    }

    T = DeleteMin(H);

    return T;
}

int WPL(HuffmanTree T, int Depth)
{
    if (!T->Left && !T->Right)
    {
        return (Depth * T->Frequency);
    }
    else
    {
        return (WPL(T->Left, Depth + 1) + WPL(T->Right, Depth + 1));
    }
}

int Fq(Data *D, char Key)
{
    if (D->Character == Key)
    {
        return D->Frequency;
    }
    else
    {
        return Fq(D + 1, Key);
    }
}

void FreeTree(HuffmanTree T)
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

HuffmanTree CreateHuffmanTree()
{
    HuffmanTree T;
    T = (HuffmanTree) malloc(sizeof(struct TreeNode));
    T->Character = '&';
    T->Frequency = -1;
    T->Left = T->Right = NULL;

    return T;
}

int BuildTree(HuffmanTree T, char K, char V[])
{
    HuffmanTree N;
    if (V[0] == '0')
    {
        if (T->Left != NULL)
        {
            if (V[1] != '\0')
            {
                if (T->Left->Character == '&')
                {
                    return BuildTree(T->Left, K, V + 1);
                }
                else if (T->Left->Character != '&')
                {
                    return 0;
                }
            }
            else if (V[1] == '\0')
            {
                if (T->Left->Character == K)
                {
                    return 1;
                }
                else if (T->Left->Character != K)
                {
                    return 0;
                }
            }
        }
        else if (T->Left == NULL)
        {
            if (V[1] != '\0')
            {
                N = CreateHuffmanTree();
                T->Left = N;
                T->Left->Character = '&';
                return BuildTree(T->Left, K, V + 1);
            }
            else if (V[1] == '\0')
            {
                N = CreateHuffmanTree();
                T->Left = N;
                T->Left->Character = K;
                return 1;
            }
        }
    }
    else if (V[0] == '1')
    {
        if (T->Right != NULL)
        {
            if (V[1] != '\0')
            {
                if (T->Right->Character == '&')
                {
                    return BuildTree(T->Right, K, V + 1);
                }
                else if (T->Right->Character != '&')
                {
                    return 0;
                }
            }
            else if (V[1] == '\0')
            {
                if (T->Right->Character == K)
                {
                    return 1;
                }
                else if (T->Right->Character != K)
                {
                    return 0;
                }
            }
        }
        else if (T->Right == NULL)
        {
            if (V[1] != '\0')
            {
                N = CreateHuffmanTree();
                T->Right = N;
                T->Right->Character = '&';
                return BuildTree(T->Right, K, V + 1);
            }
            else if (V[1] == '\0')
            {
                N = CreateHuffmanTree();
                T->Right = N;
                T->Right->Character = K;
                return 1;
            }
        }
    }
}

int main()
{
    int N;
    scanf("%d\n", &N);

    MinHeap H = CreateHeap(N);
    Data D[N + 1];
    ReadData(H, D);

    HuffmanTree T = Huffman(H);
    int CodeLen = WPL(T, 0);

    int M, i, j, TestLen, IsPrefix;
    scanf("%d", &M);
    char Key, Value[1000];
    HuffmanTree TestTree;
    for (i = 0; i < M; i++)
    {
        TestTree = CreateHuffmanTree();
        TestLen = 0;
        IsPrefix = 1;
        for (j = 0; j < N; j++)
        {
            scanf("\n%c %s", &Key, Value);
            TestLen += strlen(Value) * Fq(D, Key);
            if (strlen(Value) > (N - 1))
            {
                IsPrefix == 0;
            }
            if (IsPrefix == 1)
            {
                IsPrefix = BuildTree(TestTree, Key, Value);
            }
        }

        if (TestLen == CodeLen && IsPrefix == 1)
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
        FreeTree(TestTree);
    }

    return 0;
}