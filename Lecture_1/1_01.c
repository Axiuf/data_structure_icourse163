// 计算简单多项式的值
// 测试代码块的运行时间

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

clock_t start, stop;
double duration;
#define MaxN 10
#define MaxK 1e7
double f1(int n, double a[], double x);
double f2(int n, double a[], double x);

int main(){
    int i;
    double a[MaxN];
    for(i=0; i<MaxN; i++){
        a[i] = (double)i;
    }


    start = clock();
    for(i=0; i<MaxK; i++){ // 测试范围内的代码块
      f1(MaxN-1, a, 1.1); 
    }  
    stop = clock();
    duration = ((double)(stop - start)) / CLK_TCK / MaxK;
    printf("ticks1 = %f\n", (double)(stop - start));
    printf("duration = %6.2e\n", duration);

    start = clock();
    for(i=0; i<MaxK; i++){ 
      f2(MaxN-1, a, 1.1); 
    } 
    stop = clock();
    duration = ((double)(stop - start)) / CLK_TCK / MaxK;
    printf("ticks1 = %f\n", (double)(stop - start));
    printf("duration = %6.2e\n", duration);

    system("pause");
    return 0;
}

double f1(int n, double a[], double x){
    int i;
    double p = a[0];
    for(i=1; i<=n; i++){
        p += (a[i] * pow(x, i));
    }
    return p;
}

double f2(int n, double a[], double x){
    int i;
    double p = a[n];
    for(i=n; i>0; i--){
        p += a[i-1] + x*p;
    }
    return p;
}