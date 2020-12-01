// 07-图5 Saving James Bond - Hard Version (30分)
// 最短路径问题

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define MaxSize 101
#define Bank 50
#define Disk 15
#define Infinite 1000
#define Start 0

struct CrocodileLocation
{
    int X;
    int Y;
};
typedef struct CrocodileLocation Crocodile;

struct GraphNode
{
    Crocodile Location[MaxSize];
    float Distance[MaxSize][MaxSize];
    float DistToS[MaxSize];
    int PathToS[MaxSize];
    int Size;
};
typedef struct GraphNode *Graph;

Graph CreateGraph(int N)
{
    Graph G = (Graph) malloc(sizeof(struct GraphNode));
    G->Size = N;
}

void CalculateDistance(Graph G, int D)
{
    int i, j;
    float x;
    for (i = 1; i <= G->Size; i++)
    {
        for (j = i; j <= G->Size; j++)
        {
            x = sqrt(pow((G->Location[i].X - G->Location[j].X), 2) + pow((G->Location[i].Y - G->Location[j].Y), 2));
            if (x <= D)
            {
                G->Distance[i][j] = x;
                G->Distance[j][i] = x;
            }
            else
            {
                G->Distance[i][j] = Infinite;
                G->Distance[j][i] = Infinite;
            }
        }
    }

    i = 0;
    for (j = i; j <= G->Size; j++)
    {
        x = sqrt(pow(G->Location[j].X, 2) + pow(G->Location[j].Y, 2));
        if (x <= Disk / 2)
        {
            G->Distance[i][j] = x;
            G->Distance[j][i] = x;
        }
        else
        {
            G->Distance[i][j] = Infinite;
            G->Distance[j][i] = Infinite;
        }
    }
}

int FindMinDistToS(Graph G, int Collected[])
{
    int MinV, V;
    float MinDist = Infinite;

    for (V = 0; V <= G->Size; V++)
    {
        if (Collected[V] == 0 && G->DistToS[V] < MinDist)
        {
            MinDist = G->DistToS[V];
            MinV = V;
        }
    }

    if (MinDist < Infinite)
    {
        return MinV;
    }
    else
    {
        return -1;
    }
}

bool Dijkstra(Graph G, int S)
{
    int Collected[MaxSize];
    int V, W;

    for (V = 0; V <= G->Size; V++)
    {
        G->DistToS[V] = G->Distance[S][V];

        if (G->DistToS[V] < Infinite)
        {
            G->PathToS[V];
        }
        else
        {
            G->PathToS[V] = -1;
        }
        
        Collected[V] = 0;
    }

    G->DistToS[S] = 0;
    Collected[S] = 1;

    while (1)
    {
        V = FindMinDistToS(G, Collected);
        if (V == -1)
        {
            break;
        }

        Collected[V] = 1;
        for (W = 0; W <= G->Size; W++)
        {
            if (Collected[W] == 0 && G->Distance[V][W] < Infinite)
            {
                if (G->Distance < 0)
                {
                    return false;
                }
                if (G->DistToS[V] + G->Distance[V][W] < G->DistToS[W])
                {
                    G->DistToS[W] = G->DistToS[V] + G->Distance[V][W];
                    G->PathToS[W] = V;
                }
            }
        }
    }
    
    return true;
}

int main()
{
    int N, D, i;
    scanf("%d %d", &N, &D);

    Graph G = CreateGraph(N);
    for (i = 1; i <= G->Size; i++)
    {
        scanf("%d %d", &G->Location[i].X, &G->Location[i].Y);
    }
    G->Location[0].X = G->Location[0].Y = 0;

    CalculateDistance(G, D);

    Dijkstra(G, Start);


    return 0;
}