// 01-复杂度2 Maximum Subsequence Sum (25分)
// 解法：在线处理
// 设一个指示器k代表计算子列时的头，每当目前的子列和小于0的时候这个头会往后移动
// 仅当目前的子列和大于已记录的最大子列和的时候，才会更改最大子列和头尾的下标
// 只记录第一次出现的最大子列的下标，由于在线处理从左遍历到右，所以第一个最大子列即为下标最小

#include <stdio.h>

int main(){
    int K;
    scanf("%d", &K);

    int a[K], i;
    for(i=0; i<K; i++){
        scanf("%d", &a[i]);
    }

    int sum = 0, Max = -1, k = 0, start = 0, stop = K-1;
    for(i=0; i<K; i++){
        sum += a[i];
        if(sum < 0){
            sum = 0;
            k = i + 1;
        }else if(sum > Max){
            Max = sum;
            stop = i;
            start = k;
        }
    }

    if(Max == -1){
        Max = 0;
    }

    printf("%d %d %d", Max, a[start], a[stop]);

    return 0;
}