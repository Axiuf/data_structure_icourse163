// 06-图2 Saving James Bond - Easy Version (25分)

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define DIAMETER 15
#define EDGE 50

struct GraphNode
{
    int X;
    int Y;
    bool IsVisited;
};
typedef struct GraphNode *Graph;

bool FirstJump(Graph G, int i, int D)
{
    if ((pow(G[i].X, 2) + pow(G[i].Y, 2)) <= pow((D + DIAMETER / 2), 2))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Jump(Graph G, int i, int j, int D)
{
    if ((pow((G[i].X - G[j].X), 2) + pow((G[i].Y - G[j].Y), 2)) <= pow(D, 2))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool IsSafe(Graph G, int i, int D)
{
    if ((EDGE - G[i].X) <= D || (EDGE - G[i].Y) <= D)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool DFS(Graph G, int i, int D, int N)
{
    G[i].IsVisited = true;

    bool survive;
    int j;
    if (IsSafe(G, i, D))
    {
        survive = true;
    }
    else
    {
        for (j = 0; j < N; j++)
        {
            if (G[j].IsVisited == false && Jump(G, i, j, D))
            {
                survive = DFS(G, j, D, N);
                if (survive == true)
                {
                    break;
                }
            }
        }
    }
    
    return survive;
}

int main()
{
    int N, D, i;
    scanf("%d %d", &N, &D);

    Graph G = (Graph) malloc(N * sizeof(struct GraphNode));
    for (i = 0; i < N; i++)
    {
        scanf("%d %d", &G[i].X, &G[i].Y);
        G[i].IsVisited = false;
    }

    bool survive;
    for (i = 0; i < N; i++)
    {
        if (G[i].IsVisited == 0 && FirstJump(G, i, D))
        {
            survive = DFS(G, i, D, N);
            if (survive)
            {
                break;
            }
        }
    }

    if (survive)
    {
        printf("Yes\n");
    }
    else
    {
        printf("No\n");
    }

    return 0;
}