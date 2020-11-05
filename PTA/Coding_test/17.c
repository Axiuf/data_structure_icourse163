// 06-图3 六度空间 (30分)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef int Vertex;
#define MaxSize 1001

typedef struct ENode *PtrToENode;
struct ENode
{
    Vertex V1, V2;
};
typedef PtrToENode Edge;

typedef struct AdjNode *PtrToAdjNode;
struct AdjNode
{
    Vertex AdjV;
    PtrToAdjNode Next;
};

struct VNode
{
    PtrToAdjNode FirstEdge;
};

typedef struct VNode AdjList;

typedef struct GNode *PtrToGNode;
struct GNode
{
    int nV;
    int nE;
    int IsVisited[MaxSize];
    AdjList G[MaxSize];
};
typedef PtrToGNode LGraph;

LGraph CreatLGraph(int Size)
{
    LGraph Graph;
    Graph = (LGraph) malloc(sizeof(struct GNode));

    Graph->nV = Size;
    Graph->nE = 0;
    memset(Graph->IsVisited, 0, sizeof(Graph->IsVisited));
    
    int i;
    for (i = 1; i <= Graph->nV; i++)
    {
        Graph->G[i].FirstEdge = NULL;
    }
    
    return Graph;
}

void AddEdge(LGraph Graph, Edge E)
{
    PtrToAdjNode NewAdjNode;
    
    NewAdjNode = (PtrToAdjNode) malloc(sizeof(struct AdjNode));
    NewAdjNode->AdjV = E->V2;
    NewAdjNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewAdjNode;

    NewAdjNode = (PtrToAdjNode) malloc(sizeof(struct AdjNode));
    NewAdjNode->AdjV = E->V1;
    NewAdjNode->Next = Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge = NewAdjNode;
}

struct QNode
{
    int List[MaxSize];
    int front;
    int rear;
};
typedef struct QNode *Quene;

Quene CreateQuene()
{
    Quene Q = (Quene) malloc(sizeof(struct QNode));
    memset(Q->List, -1, sizeof(Q->List));
    Q->front = Q->rear = 0;

    return Q;
}

void InsertQuene(Quene Q, int i)
{
    if (((Q->rear + 1) % MaxSize) != Q->front)
    {
        Q->rear = (Q->rear + 1) % MaxSize;
        Q->List[Q->rear] = i;
    }
}

int PopQuene(Quene Q)
{
    int pop = -1;
    if (Q->front != Q->rear)
    {
        pop = Q->List[Q->front + 1];
        Q->List[Q->front + 1] = -1;
        Q->front = (Q->front + 1) % MaxSize;
    }

    return pop;
}

bool IsQueneEmpty(Quene Q)
{
    if (Q->front == Q->rear)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

int BFS(LGraph Graph, Vertex i)
{
    int count = 0, level;
    int pop, last, tail;
    PtrToAdjNode next;
    Quene Q = CreateQuene();
    if (Graph->IsVisited[i] == 0)
    {
        Graph->IsVisited[i] = 1;
        count++;
        level = 0;
        last = i;
        InsertQuene(Q, i);

        while (!IsQueneEmpty(Q))
        {
            pop = PopQuene(Q);
            next = Graph->G[pop].FirstEdge;
            while (next != NULL)
            {
                if (Graph->IsVisited[next->AdjV] == 0)
                {
                    Graph->IsVisited[next->AdjV] = 1;
                    count++;
                    InsertQuene(Q, next->AdjV);
                    tail = next->AdjV;
                }
                next = next->Next;
            }

            if (pop == last)
            {
                level++;
                last = tail;
            }

            if (level == 6)
            {
                break;
            }
        }
    }

    return count;
}

int main()
{
    int N, M, i;
    scanf("%d %d", &N, &M);

    LGraph Graph = CreatLGraph(N);
    Edge E = (Edge) malloc(sizeof(struct ENode));
    for (i = 0; i < M; i++)
    {
        scanf("%d %d", &E->V1, &E->V2);
        AddEdge(Graph, E);
        Graph->nE++;
    }

    int count;
    for (i = 1; i <= N; i++)
    {
        count = BFS(Graph, i);
        printf("%d: %.2f%%\n", i, (count * 1.0 / N * 100));
        memset(Graph->IsVisited, 0, sizeof(Graph->IsVisited));
    }

    return 0;
}