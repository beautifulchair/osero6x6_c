#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "hs/record.h"

record initRecord(){
    record new;
    new.n = 0;
    for(int i=0; i<36; i++)
        new.r[i] = -2;
    return new;
}

void printRecord(record rec){
    for(int i=0; i<rec.n; i++){
        printf("%d ", rec.r[i]);
    }
    printf("\n");
}

void addRecord(record *rec, int coo){
    if(rec->n < 36-1)
        rec->r[rec->n++] = coo;
    else
        perror(__func__);
}

void undoRecord(record *rec){
    if(rec->n < 1)
        perror(__func__);
    else
        rec->r[--rec->n] = -2;
}

record cloneRecord(record rec){
    record *new;
    new->n = rec.n;
    for(int i=0; i<36; i++)
        new->r[i] = rec.r[i];
        return *new;
}