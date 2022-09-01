#ifndef BOARD_H
#define BOARD_H

#include "record.h"

typedef struct board_{
    int row[6];
    int col[6];
    int rid[7];
    int led[7];
    int nextS;
}board;

typedef int coo;

typedef int status;

coo newcoo(int, int);
char view(status);
status getStatus(board, coo);
void printBoard(board);
void printBoardImage(board);
void printBoardData(board);
board initBoard();
void changeBoard(board*, coo, status);
int available(board, coo, status);
int put(board*, coo, status);
int justput(board*, coo, status);
board putResult(board, coo, status);
void createAvailables(board b, status s);
void readyAvailables();
int allAvailable(board b, status s);
coo numberPutCoo(board b, status, int number);
coo randumPutCoo(board b, status s);
int getWhiteN(board b);
int getBlackN(board b);
int getN(board b);
board effectRecord(record rec);
#define rowIndex(c) (c/6) 
#define colIndex(c) (c%6)
#define ridIndex(c) (c/6+c%6-2)
#define ledIndex(c) (c%6-c/6+3)

#endif