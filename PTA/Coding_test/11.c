// 04-树6 Complete Binary Search Tree (30分)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int compare(const void*a, const void*b)
{
    return *(int*)a -*(int*)b;
}

int GetLeftLength(int N)
{
    int L, H, X;
    H = (int) (log(N + 1) / log (2));
    X = N - pow(2, H) + 1;
    if (X > pow(2, (H - 1)))
    {
        X = pow(2, (H - 1));
    }

    L = pow(2, (H - 1)) - 1 + X;

    return L;
}

void Solve(int Tree[], int List[], int L_left, int L_right, int T_root)
{
    int N = L_right - L_left + 1;
    if (N == 0)
    {
        return;
    }

    int L;
    L = GetLeftLength(N);
    Tree[T_root] = List[L_left + L];
    int left_root = T_root * 2 + 1;
    int right_root = left_root + 1;

    Solve(Tree, List, L_left, L_left + L - 1, left_root);
    Solve(Tree, List, L_left + L + 1, L_right, right_root);
}


int main()
{
    int N;
    scanf("%d", &N);

    int List[N], Tree[N], i;
    for (i = 0; i < N; i++)
    {
        scanf("%d", &List[i]);
    }

    qsort(List, N, sizeof(int), compare);

    Solve(Tree, List, 0, N - 1, 0);

    for (i = 0; i < N - 1; i++)
    {
        printf("%d ", Tree[i]);
    }
    printf("%d", Tree[i]);

    return 0;
}