#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "hs/available.h"
#include "hs/otherfunc.h"
#define LINESIZE 5994
#define BUFSIZE 15
#define FNAME "datas/available.csv"

static int available[LINESIZE*2];

int convertIndexAvailable(int n, int b, int c,int i){
    b=convert4to3(b);
    switch(n){
        case(6):
            return b*n*2+2*i+c-1;
        case(5):
            return 8748+b*n*2+2*i+c-1;
        case(4):
            return 11178+b*n*2+2*i+c-1;
        case(3):
            return 11826+b*n*2+2*i+c-1;
        default:
            // printf("error convertIndexAvailable\n");
            return -1;
    }

}

int getAvailable(int n){
    if(n==-1)return 0;
    return available[n];
}

void readAvailable(){
    FILE* fp=fopen(FNAME, "r");
    char buf[BUFSIZ];
    if(fp==NULL){
        printf("cannot open file %s.\n", FNAME);
        return;
    }
    for(int i=0; i<LINESIZE; i++){
        fgets(buf, BUFSIZE, fp);
        available[i*2]=atoi(strtok(buf, ","));
        available[i*2+1]=atoi(strtok(NULL, ","));
    }
    fclose(fp);
}