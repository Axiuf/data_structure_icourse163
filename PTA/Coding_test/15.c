// 06-图1 列出连通集 (25分)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MaxSize 11
int Set[MaxSize] = {0};
int Count = 0;

struct GNode
{
    int nV;
    int nE;
    int Edge[MaxSize][MaxSize];
    int IsVisited[MaxSize];
};
typedef struct GNode *Graph;

struct ENode
{
    int V1, V2;
};
typedef struct ENode *Edge;

Graph CreateGraph(int Size)
{
    Graph G = (Graph) malloc(sizeof(struct GNode));
    G->nV = Size;
    G->nE = 0;
    int i, j;
    for (i = 0; i < Size; i++)
    {
        G->IsVisited[i] = 0;
        for ( j = 0; j < Size; j++)
        {
            G->Edge[i][j] = 0;
        }
    }

    return G;
}

void InsertEdge(Graph G, Edge Ei)
{
    if (G->Edge[Ei->V1][Ei->V2] == 0)
    {
        G->nE++;
        G->Edge[Ei->V1][Ei->V2] = 1;
        G->Edge[Ei->V2][Ei->V1] = 1;
    }
}

void DFS(Graph G, int i)
{
    int j;

    if (G->IsVisited[i] != 1)
    {
        G->IsVisited[i] = 1;
        Set[Count] = i;
        Count++;

        for (j = 0; j < G->nV; j++)
        {
            if (G->Edge[i][j] == 1)
            {
                DFS(G, j);
            }
        }
    }
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


void BFS(Graph G, int i)
{
    int pop, j;
    Quene Q = CreateQuene();

    if (G->IsVisited[i] == 0)
    {
        G->IsVisited[i] = 1;
        Set[Count] = i;
        Count++;

        InsertQuene(Q, i);

        while (Q->front != Q->rear)
        {
            pop = PopQuene(Q);
            for (j = 0; j < G->nV; j++)
            {
                if (G->Edge[pop][j] == 1 && G->IsVisited[j] == 0)
                {
                    G->IsVisited[j] = 1;
                    Set[Count] = j;
                    Count++;
                    InsertQuene(Q, j);
                }
            }
        }
    }
}


int main()
{
    int N, E, i;
    scanf("%d %d", &N, &E);

    Graph G = CreateGraph(N);
    Edge Ei = (Edge) malloc(sizeof(struct ENode));
    for (i = 0; i < E; i++)
    {
        scanf("%d %d", &Ei->V1, &Ei->V2);
        InsertEdge(G, Ei);
    }

    int j;
    for (i = 0; i < N; i++)
    {
        memset(Set, -1, sizeof(Set));
        Count = 0;
        DFS(G, i);

        if (Count > 0)
        {
            printf("{ ");
            for (j = 0; j < Count; j++)
            {
                printf("%d ", Set[j]);
            }
            printf("}\n");
        }
    }

    memset(G->IsVisited, 0, sizeof(G->IsVisited));

    for (i = 0; i < N; i++)
    {
        memset(Set, -1, sizeof(Set));
        Count = 0;
        BFS(G, i);

        if (Count > 0)
        {
            printf("{ ");
            for (j = 0; j < Count; j++)
            {
                printf("%d ", Set[j]);
            }
            printf("}\n");
        }
    }


    return 0;
}