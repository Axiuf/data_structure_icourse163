// 01-复杂度1 最大子列和问题 (20分)
// 解法1：穷举法
// 把所有的子列和全部算出来，并和最大值一一比较
// 最后得到最大子列和

#include <stdio.h>

int main(){
    int K;
    scanf("%d", &K);

    int a[K], i;
    for(i=0; i<K; i++){
        scanf("%d", &a[i]);
    }

    int sum, Max = 0, j, k;
    for(i=0; i<K; i++){
        for(j=i; j<K; j++){
            sum = 0;
            for(k=i; k<=j; k++){
                sum += a[k];
            }
            if(sum > Max){
                Max = sum;
            }
        }
    }

    printf("%d", Max);

    return 0;
}