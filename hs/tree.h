#ifndef TREE_H
#define TREE_H

#include "board.h"

struct score_{
    int s1;
};
typedef struct score_ score;

struct tnode_{
    board b;
    int n;
    score s;
    struct tnode_ **childlen;
};
typedef struct tnode_ *tnode;

tnode initTnode(board b);
void setTnode(tnode tn);
void makeTree(tnode root, int n);
int cmpScore(score s1, score s2);
score getScore(tnode tn);

#endif