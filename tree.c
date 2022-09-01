#include <stdio.h>
#include <stdlib.h>
#include "hs/tree.h"
#include "hs/board.h"
#include "hs/otherfunc.h"
#include "hs/available.h"

tnode initTnode(board b){
    tnode new;
    new = (tnode)calloc((sizeof *new), 1);
    new->b = b;
    new->n = -1;
    new->s = getScore(new);
    return new;
}

void setTnode(tnode tn){
    board b;
    int n;

    b = tn->b;
    n = allAvailable(b, b.nextS);
    tn->n = n;

    if(n == 0)
        tn->childlen = NULL;
    else{
        tn->childlen = (tnode*)calloc(sizeof tn, n);
        for(int i=0; i<n; i++)
            tn->childlen[i] = initTnode(putResult(b, numberPutCoo(b, b.nextS, i+1), b.nextS));
    }
}

void makeTree(tnode tn, int n){
    setTnode(tn);
    if(n==1)
        return;
    else{
        for(int i=0; i<tn->n; i++)
            makeTree(tn->childlen[i], n-1);
    }
}

int cmpScore(score s1, score s2){
    if(s1.s1>s2.s1)
        return 1;
    else if(s1.s1<s2.s1)
        return -1;
    else
        return 0;
}

score getScore(tnode tn){
    score new;
    new.s1 = getBlackN(tn->b);
    return new;
}