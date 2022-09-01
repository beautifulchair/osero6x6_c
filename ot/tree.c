#include <stdlib.h>
#include <stdio.h>
#include "hs/tree.h"
#include "hs/board.h"
#include "hs/otherfunc.h"
#include "hs/available.h"

parentNode initParentNode(board b){
    parentNode new;
    new = (parentNode)calloc(sizeof *new, 1);
    new->b = b;
    new->cn = NULL;
    return new;
}

childNode initChildNode(board b){
    childNode new;
    new = (childNode)calloc(sizeof *new, 1);
    new->next = NULL;
    new->pn = initParentNode(b);
    return new;
}

void setParentNode(parentNode pn){
    int n, i;
    board b;
    childNode tmpcn;

    b = pn->b;
    n = allAvailable(b, b.nextS);
    if(n==0)
        return;
    
    pn->cn = initChildNode(putResult(b, numberPutCoo(b, b.nextS, 1), b.nextS));
    tmpcn = pn->cn;

    for(i=1; i<n; i++){
        tmpcn->next = initChildNode(putResult(b, numberPutCoo(b, b.nextS, i+1), b.nextS));
        tmpcn = tmpcn->next;
    }
}

void makeTree(parentNode pn, int n){
    childNode tmpcn;
    if(n==1){
        setParentNode(pn);
    }
    if(n>1){
        setParentNode(pn);
        if(pn->cn == NULL)
            return;
        else{
            makeTree(pn->cn->pn, n-1);
            tmpcn = pn->cn;
            while(tmpcn->next != NULL){
                tmpcn = tmpcn->next;
                makeTree(tmpcn->pn, n-1);
            }
        }
    }
}

queNode initQueNode(parentNode pn){
    queNode new;
    new = (queNode)calloc(sizeof *new, 1);
    new->pn = pn;
    new->next = NULL;
    return new;
}

queNode rootQueNode(){
    queNode new;
    new = (queNode)calloc(sizeof *new, 1);
    new->pn = NULL;
    new->next = NULL;
    return new;
}

queNode enque(queNode root, parentNode pn){
    queNode new;
    new = initQueNode(pn);
    new->next = root->next;
    root->next = new;
    return new;
}

parentNode deque(queNode root){
    queNode tmp;
    parentNode pn;

    tmp = root;
    if(tmp->next == NULL){
        return NULL;
    }
    while((tmp->next)->next != NULL)
        tmp = tmp->next;
    pn = tmp->next->pn;
    free(tmp->next);
    tmp->next = NULL;
    return pn;
}

void printParentNode(parentNode pn){
    printBoardImage(pn->b);
}

void printTree(parentNode pn){
    queNode root, qn;
    parentNode tmppn;
    childNode cn;
    root = rootQueNode();
    enque(root, pn);
    while((tmppn=deque(root))!=NULL){
        printBoardImage(tmppn->b);
        if(tmppn->cn!=NULL){
            cn = tmppn->cn;
            while(cn!=NULL){
                if(cn->pn->cn!=NULL)
                    enque(root, cn->pn);
                cn = cn->next;
            }
        }
    }
}