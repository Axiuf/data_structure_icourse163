// 07-图4 哈利·波特的考试 (25分)
// 图里面的多源最短路径的问题


#include <stdio.h>
#include <stdlib.h>
#define MaxSize 101
#define INFINITE 101


struct GraphNode
{
    int Edge[MaxSize][MaxSize];
    int MinDist[MaxSize][MaxSize];
    int MinPath[MaxSize][MaxSize];
    int Size;
};
typedef struct GraphNode *Graph;

Graph CreateGraph(int Size)
{
    Graph G = (Graph) malloc(sizeof(struct GraphNode));
    G->Size = Size;
    int i, j;
    for (i = 1; i <= G->Size; i++)
    {
        for (j = 1; j <= G->Size; j++)
        {
            if (i == j)
            {
                G->Edge[i][j] = 0;
            }
            else
            {
                G->Edge[i][j] = INFINITE;
            }         
        }
    }

    return G;
}

void Floyd(Graph G)
{
    int i, j, k;
    for (i = 1; i <= G->Size; i++)
    {
        for (j = 1; j <= G->Size; j++)
        {
            G->MinDist[i][j] = G->Edge[i][j];
            G->MinPath[i][j] = -1;
        }
    }

    for (k = 1; k <= G->Size; k++)
    {
        for (i = 1; i <= G->Size; i++)
        {
            for (j = 1; j <= G->Size; j++)
            {
                if (G->MinDist[i][k] + G->MinDist[k][j] < G->MinDist[i][j])
                {
                    G->MinDist[i][j] = G->MinDist[i][k] + G->MinDist[k][j];
                    G->MinPath[i][j] = k;
                }
            }
        }
    }
}


int main()
{
    int N, M;
    scanf("%d %d", &N, &M);

    Graph G = CreateGraph(N);
    int i, j, dist, k;
    for (k = 1; k <= M; k++)
    {
        scanf("%d %d %d", &i, &j, &dist);
        G->Edge[i][j] = dist;
        G->Edge[j][i] = dist;
    }

    Floyd(G);

    int MaxDist[MaxSize], res = 1;
    for (i = 1; i <= G->Size; i++)
    {
        MaxDist[i] = 0;
        for (j = 1; j <= G->Size; j++)
        {
            if (G->MinDist[i][j] > MaxDist[i])
            {
                MaxDist[i] = G->MinDist[i][j];
            }
        }
    }

    for (i = 1; i <= G->Size; i++)
    {
        if (MaxDist[i] < MaxDist[res])
        {
            res = i;
        }
    }

    if (MaxDist[res] == INFINITE)
    {
        printf("0");
    }
    else
    {
        printf("%d %d", res, MaxDist[res]);
    }

    return 0;
}