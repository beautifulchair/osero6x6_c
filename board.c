#include "hs/board.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "hs/available.h"
#include "hs/otherfunc.h"
#include "hs/putImfo.h"
#include "hs/record.h"

static int N = 0;
static int availables[36];

coo newcoo(int x, int y) { return x + y * 6; }

status getStatus(board b, coo c) {
    return (b.row[rowIndex(c)] >> colIndex(c) * 2) & 3;
}

char view(status x) {
    switch (x) {
        case 0:
            return '_';
            break;
        case 1:
            return 'x';
            break;
        case 2:
            return 'o';
            break;
        case 3:
            return '*';
            break;
        default:
            assert(x<4);
            break;
    }
    return '?';
}

void printBoardImage(board b) {
    printf("  _ _ _ _ _ _\n");
    for (int r = 0; r < 6; r++) {
        printf("%d|", r);
        for (int c = 0; c < 6; c++) {
            printf("%c|", view(getStatus(b, newcoo(c, r))));
        }
        printf("\n");
    }
    printf("  0 1 2 3 4 5\n");
}

void printBoardData(board b) {
    printf("row: ");
    for (int i = 0; i < 6; i++) printf("%d, ", b.row[i]);
    printf("\n");
    printf("col: ");
    for (int i = 0; i < 6; i++) printf("%d, ", b.col[i]);
    printf("\n");
    printf("rid: ");
    for (int i = 0; i < 7; i++) printf("%d, ", b.rid[i]);
    printf("\n");
    printf("led: ");
    for (int i = 0; i < 7; i++) printf("%d, ", b.led[i]);
    printf("\n");
    printf("next: %d", b.nextS);
    printf("\n");
}

void printBoard(board b) {
    printBoardImage(b);
    printBoardData(b);
}

board initBoard() {
    board new;
    for (int i = 0; i < 6; i++) {
        new.row[i] = 0;
        new.col[i] = 0;
        new.rid[i] = 0;
        new.led[i] = 0;
    }
    new.rid[6] = 0;
    new.led[6] = 0;
    changeBoard(&new, newcoo(2, 2), 2);
    changeBoard(&new, newcoo(3, 2), 1);
    changeBoard(&new, newcoo(2, 3), 1);
    changeBoard(&new, newcoo(3, 3), 2);
    new.nextS = 1;
    return new;
}

void changeBoard(board* b, coo c, status s) {
    int tmp, v = getStatus(*b, c), x = colIndex(c), y = rowIndex(c),
             a = (x + y <= 5) ? y : (5 - x), d = (x - y <= 0) ? x : y;
    status saveS = s;
    tmp = b->row[y];
    b->row[y] = (tmp & ~(3 << x * 2)) | (s << x * 2);
    tmp = b->col[x];
    b->col[x] = (tmp & ~(3 << y * 2)) | (s << y * 2);
    if(0<=x+y-2 && x+y-2<7){
        tmp = b->rid[x + y - 2];
        b->rid[x + y - 2] = (tmp & ~(3 << a * 2)) | (s << a * 2);
    }
    if(0<=3+x-y && 3+x-y<7){
        tmp = b->led[3 + x - y];
        b->led[3 + x - y] = (tmp & ~(3 << d * 2)) | (s << d * 2);
    }
    b->nextS = saveS;  // nazo koreganaito okasikunaru
}

int put(board* b, coo c, status s) {
    // 0: cannot put, 1: normal, 2: change player, 3: cannot change player
    if (c == -1) {
        if (allAvailable(*b, b->nextS) != 0)
            return 3;
        printf("CHANGE\n");
        b->nextS = 3 - b->nextS;
        return 2;
    }
    int x = colIndex(c), y = rowIndex(c), z = ridIndex(c), w = ledIndex(c);
    int i, tmp;
    int a = (x + y <= 5) ? y : (5 - x), d = (x - y <= 0) ? x : y;
    int row = b->row[y];
    int col = b->col[x];
    int rid = b->rid[x + y - 2];
    int led = b->led[3 + x - y];
    int rowchange = getAvailable(convertIndexAvailable(6, row, s, x));
    int colchange = getAvailable(convertIndexAvailable(6, col, s, y));
    int ridchange =
        getAvailable(convertIndexAvailable(6 - abs(5 - x - y), rid, s, a));
    int ledchange =
        getAvailable(convertIndexAvailable(6 - abs(x - y), led, s, d));
    if (rowchange == 0 && colchange == 0 && ridchange == 0 && ledchange == 0) {
        printf("PUT coo: (%d, %d), status: %d -> cannot put.\n", x, y, s);
        return 0;
    }
    if (rowchange != 0)
        for (i = rowchange % 6; i <= rowchange / 6; i++)
            changeBoard(b, newcoo(i, y), s);
    if (colchange != 0)
        for (i = colchange % 6; i <= colchange / 6; i++)
            changeBoard(b, newcoo(x, i), s);
    if (ridchange != 0)
        for (i = ridchange % 6; i <= ridchange / 6; i++)
            changeBoard(b, newcoo(x + a - i, y - a + i), s);
    if (ledchange != 0)
        for (i = ledchange % 6; i <= ledchange / 6; i++)
            changeBoard(b, newcoo(x - d + i, y - d + i), s);
    printf(
        "PUT coo: (%d, %d), status: %d -> row: %d, col: %d, rid: %d, led: %d\n",
        x, y, s, rowchange, colchange, ridchange, ledchange);
    b->nextS = 3 - b->nextS;
    return 1;
}

// not print
int justput(board* b, coo c, status s) {
    if (c == -1) {
        if (allAvailable(*b, b->nextS) != 0)
            return 3;
        b->nextS = 3 - b->nextS;
        return 2;
    }
    int x = colIndex(c), y = rowIndex(c), z = ridIndex(c), w = ledIndex(c);
    int i, tmp;
    int a = (x + y <= 5) ? y : (5 - x), d = (x - y <= 0) ? x : y;
    int row = b->row[y];
    int col = b->col[x];
    int rid = b->rid[x + y - 2];
    int led = b->led[3 + x - y];
    int rowchange = getAvailable(convertIndexAvailable(6, row, s, x));
    int colchange = getAvailable(convertIndexAvailable(6, col, s, y));
    int ridchange =
        getAvailable(convertIndexAvailable(6 - abs(5 - x - y), rid, s, a));
    int ledchange =
        getAvailable(convertIndexAvailable(6 - abs(x - y), led, s, d));
    if (rowchange == 0 && colchange == 0 && ridchange == 0 && ledchange == 0) {
        return 0;
    }
    if (rowchange != 0)
        for (i = rowchange % 6; i <= rowchange / 6; i++)
            changeBoard(b, newcoo(i, y), s);
    if (colchange != 0)
        for (i = colchange % 6; i <= colchange / 6; i++)
            changeBoard(b, newcoo(x, i), s);
    if (ridchange != 0)
        for (i = ridchange % 6; i <= ridchange / 6; i++)
            changeBoard(b, newcoo(x + a - i, y - a + i), s);
    if (ledchange != 0)
        for (i = ledchange % 6; i <= ledchange / 6; i++)
            changeBoard(b, newcoo(x - d + i, y - d + i), s);
    b->nextS = 3 - b->nextS;
    return 1;
}

board putResult(board b, coo c, status s) {
    board tmp;
    tmp = b;
    justput(&tmp, c, s);
    return tmp;
}

int available(board b, coo c, status s) {
    int x = colIndex(c), y = rowIndex(c), a = (x + y <= 5) ? y : (5 - x),
        d = (x - y <= 0) ? x : y;
    int row = b.row[y];
    int col = b.col[x];
    int rid = b.rid[x + y - 2];
    int led = b.led[3 + x - y];
    if (getStatus(b, c)) return 0;
    if (getAvailable(convertIndexAvailable(6, row, s, x)) != 0) return 1;
    if (getAvailable(convertIndexAvailable(6, col, s, y)) != 0) return 1;
    if (abs(6 - x - y) < 4 &&
        getAvailable(convertIndexAvailable(6 - abs(5 - x - y), rid, s, a)) != 0)
        return 1;
    if (abs(x - y) < 4 &&
        getAvailable(convertIndexAvailable(6 - abs(x - y), led, s, d)) != 0)
        return 1;
    return 0;
}

void readyAvailables(board b, status s){
    int counter = 0;
    for (int i = 0; i < 36; i++) {
        if (available(b, i, s)) {
            availables[counter] = i;
            counter++;
        }
    }
}

int countAvailables(){
    int i;
    for(i=0; i<36; i++){
        if(availables[i] == -1)
            break;
    }
    return i;
}

int allAvailable(board b, status s) {
    int counter = 0;
    for (int i = 0; i < 36; i++) {
        if (available(b, i, s)) {
            availables[counter] = i;
            counter++;
        }
    }
    availables[counter] = -1;
    return counter;
}

coo numberPutCoo(board b, status s, int number) {
    int n = allAvailable(b, b.nextS);
    if (number > n) printf("!!erro in numberPutCoo!!\n");
    return availables[number - 1];
}

coo randumPutCoo(board b, status s) {
    return numberPutCoo(b, s, randInt(allAvailable(b, s))+1);
}

int getWhiteN(board b) {
    int counter = 0;
    for (int i = 0; i < 36; i++) {
        if (getStatus(b, i) == 2) counter++;
    }
    return counter;
}

int getBlackN(board b) {
    int counter = 0;
    for (int i = 0; i < 36; i++) {
        if (getStatus(b, i) == 1) counter++;
    }
    return counter;
}

int getN(board b) {
    int counter = 0;
    for (int i = 0; i < 36; i++) {
        if (getStatus(b, i) != 0) counter++;
    }
    return counter;
}

board effectRecord(record rec){
    board b = initBoard();
    for(int i=0; i<rec.n; i++)
        justput(&b, rec.r[i], b.nextS);
    return b;
}