#ifndef TREE_H
#define TREE_H

#include "board.h"

struct queNode_{
    struct parentNode_ *pn;
    struct queNode_ *next;
};
typedef struct queNode_ *queNode;

struct childNode_{
    struct childNode_  *next;
    struct parentNode_ *pn;
};
typedef struct childNode_  *childNode;

struct parentNode_{
    board b;
    struct childNode_ *cn;
};
typedef struct parentNode_* parentNode;

parentNode initParentNode(board b);
childNode initChildNode(board b);
void setParentNode(parentNode pn);
void makeTree(parentNode pn, int n);
void printParentNode(parentNode pn);
queNode initQueNode(parentNode pn);
queNode rootQueNode();
queNode enque(queNode root, parentNode pn);
parentNode deue(queNode root);
void printTree(parentNode pn);
#endif