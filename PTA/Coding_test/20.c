// 07-图6 旅游规划 (25分)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxSize 500
#define INFINITY 400
#define ERROR -1

struct GraphNode
{
    int Size;
    int Distance[MaxSize][MaxSize];
    int Charge[MaxSize][MaxSize];
};
typedef struct GraphNode *Graph;

Graph CreateGraph(int N)
{
    Graph G = (Graph) malloc(sizeof(struct GraphNode));
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (i == j)
            {
                G->Distance[i][j] = 0;
                G->Charge[i][j] = 0;
            }
            else
            {
                G->Distance[i][j] = INFINITY;
                G->Charge[i][j] = INFINITY;
            }
        }
    }
    G->Size = N;

    return G;
}

int FindMinDist(Graph G, int dist[], int collected[])
{ /* 返回未被收录顶点中dist最小者 */
    int MinV, V;
    int MinDist = INFINITY;

    for (V = 0; V < G->Size; V++) {
        if (collected[V] == false && dist[V] < MinDist) {
            /* 若V未被收录，且dist[V]更小 */
            MinDist = dist[V]; /* 更新最小距离 */
            MinV = V; /* 更新对应顶点 */
        }
    }
    if (MinDist < INFINITY) /* 若找到最小dist */
        {
            return MinV; /* 返回对应的顶点下标 */
        }
    else
    {
        return ERROR;  /* 若这样的顶点不存在，返回错误标记 */
    }
}

bool Dijkstra(Graph G, int dist[], int fee[], int path[], int S)
{
    int collected[G->Size];
    int V, W;

    /* 初始化：此处默认邻接矩阵中不存在的边用INFINITY表示 */
    for (V = 0; V < G->Size; V++) {
        dist[V] = G->Distance[S][V];
        fee[V] = G->Charge[S][V];
        if (dist[V] < INFINITY)
        {
            path[V] = S;
        }
        else
        {
            path[V] = -1;
        }
        collected[V] = false;
    }
    /* 先将起点收入集合 */
    dist[S] = 0;
    fee[S] = 0;
    collected[S] = true;

    while (1) {
        /* V = 未被收录顶点中dist最小者 */
        V = FindMinDist(G, dist, collected);
        if (V == ERROR)
        {/* 若这样的V不存在 */
            break;      /* 算法结束 */
        } 
        collected[V] = true;  /* 收录V */
        for(W = 0; W < G->Size; W++) /* 对图中的每个顶点W */
            /* 若W是V的邻接点并且未被收录 */
            if (collected[W] == false && G->Distance[V][W] < INFINITY) {
                if (G->Distance[V][W] < 0) /* 若有负边 */
                {
                    return false; /* 不能正确解决，返回错误标记 */
                }
                /* 若收录V使得dist[W]变小 */
                if (dist[V] + G->Distance[V][W] < dist[W])
                {
                    dist[W] = dist[V] + G->Distance[V][W]; /* 更新dist[W] */
                    fee[W] = fee[V] + G->Charge[V][W];
                    path[W] = V; /* 更新S到W的路径 */
                }
                else if (dist[V] + G->Distance[V][W] == dist[W])
                {
                    if (fee[V] + G->Charge[V][W] < fee[W])
                    {
                        dist[W] = dist[V] + G->Distance[V][W]; /* 更新dist[W] */
                        fee[W] = fee[V] + G->Charge[V][W];
                        path[W] = V; /* 更新S到W的路径 */
                    }
                }
            }
    } /* while结束*/
    return true; /* 算法执行完毕，返回正确标记 */
}

int main()
{
    int N, M, S, D, i;
    scanf("%d %d %d %d", &N, &M, &S, &D);

    int c1, c2, distance, charge;
    Graph G = CreateGraph(N);
    for (i = 0; i < M; i++)
    {
        scanf("%d %d %d %d", &c1, &c2, &distance, &charge);
        G->Distance[c1][c2] = distance;
        G->Distance[c2][c1] = distance;
        G->Charge[c1][c2] = charge;
        G->Charge[c2][c1] = charge;
    }

    int dist[MaxSize], fee[MaxSize], path[MaxSize];
    Dijkstra(G, dist, fee, path, S);

    printf("%d %d", dist[D], fee[D]);
    return 0;
}