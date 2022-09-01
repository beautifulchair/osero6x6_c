#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include "hs/otherfunc.h"

#define max(x, y) ((x>=y) ? x : y)
#define min(x, y) ((x<=y) ? x : y)

int log_quiet = 0;

int threePow(int n){
    int ans=1;
    for(int i=0; i<n; i++)
        ans*=3;
    return ans;
}

int convert4to3(int n){
    int ans=0;
    for(int i=0; i<6; i++){
        ans += (threePow(i) * ((n >> (2*i)) % 4));
    }
    return ans;
}

void printArrayInt(int a[], int n){
    for(int i=0; i<n; i++)
        printf("%d: %d, ", i, a[i]);
    printf("\n");
}

int randInt(int n){
    if(n<=0)
        return -1;
    int r = myrand();
    return (r%n);
}

int* randInts(int num){
    int* ip;
    if(num <= 0)
        return NULL;
    ip = calloc(num, sizeof(int));
    for(int i=0; i<num; i++){
        ip[i] = myrand();
    }
    return ip;
}

int myrand(){
    //use datas/oneInt.csv
    char buf[20];
    int n, r;
    FILE *fp;
    fp = fopen("datas/oneInt.csv", "r");
    if(fp == NULL){
        printf("fail in myrand.\n");
        return 1;
    }
    fgets(buf, 20, fp);
    fclose(fp);
    n = atoi(buf);
    srand((unsigned int)n);
    r = rand();
    fp = fopen("datas/oneInt.csv", "w");
    if(fp == NULL){
        printf("fail in myrand.\n");
        return r;
    }
    fprintf(fp, "%d,", r);
    fclose(fp);
    // pint(r);
    return r;
}

void log_q(const char *fmt, ...){
    // use log_quiet
    if(log_quiet == 0) return;
    printf("%d: ", __LINE__);
    va_list va;
    va_start(va, fmt);
    vprintf (fmt, va);
    va_end(va);
}

void setLogQuiet(int bool){
    log_quiet = bool;
}