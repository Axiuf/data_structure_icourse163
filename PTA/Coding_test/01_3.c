// 01-复杂度1 最大子列和问题 (20分)
// 解法3：在线处理
// 实时判断前部分子列是否为0
// 若为0，则该部分子列对于最大子列没有贡献，直接去除
// 时间复杂度为n

#include <stdio.h>

int main(){
    int K;
    scanf("%d", &K);

    int a[K], i;
    for(i=0; i<K; i++){
        scanf("%d", &a[i]);
    }

    int sum = 0, Max = 0, j;
    for(i=0; i<K; i++){
        sum += a[i];
        if(sum < 0){
            sum = 0;
        }else if(sum > Max){
            Max = sum;
        }
    }

    printf("%d", Max);

    return 0;
}