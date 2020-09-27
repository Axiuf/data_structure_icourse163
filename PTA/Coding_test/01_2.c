// 01-复杂度1 最大子列和问题 (20分)
// 解法2：穷举法的改进
// 去掉最底层的循环

#include <stdio.h>

int main(){
    int K;
    scanf("%d", &K);

    int a[K], i;
    for(i=0; i<K; i++){
        scanf("%d", &a[i]);
    }

    int sum, Max = 0, j;
    for(i=0; i<K; i++){
        sum = 0;
        for(j=i; j<K; j++){
            sum += a[j];
            if(sum > Max){
                Max = sum;
            }
        }
    }

    printf("%d", Max);

    return 0;
}