#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hs/available.h"
#include "hs/board.h"
#include "hs/otherfunc.h"
#include "hs/putImfo.h"

#define MAXTURN 100

void printExplanation() {
    printf(
        "n)new, d)display, a)add, s)printN, h)hint\n"
        "p)put, r)randamPut, u)undo, y)clone, v)store\n");
}

// use "putImfo.csv"
int main(int argc, char *argv[]) {
    char inChar;
    int inNum;
    int counter;
    int tmp;
    board b = initBoard();
    if (argc == 1) {
        printExplanation();
    }
    if (argc == 3) {
        sscanf(argv[2], "%d", &inNum);
    }
    if (argc >= 2 && sscanf(argv[1], "%c", &inChar) != 0) {
        switch (inChar) {
            case 'n':
                // add new game
                printf("new line putImfo.csv? y/n\n");
                scanf("%c", &inChar);
                if (inChar == 'y') {
                    addNewLinePutImfo();
                    addPutImfo(27);
                    readAvailable();
                    readPutImfo();
                    put(&b, 27, 1);
                    printBoardImage(b);
                    break;
                } else {
                    printf("canceled\n");
                    break;
                }
            case 'd':
                // deiplay last geme
                readAvailable();
                readPutImfo();
                b = initBoard();
                for (counter = 0; counter < MAXTURN; counter++) {
                    tmp = getPutImfo(counter);
                    if (tmp == -2) break;
                    put(&b, tmp, b.nextS);
                    printBoardImage(b);
                }
                break;
            case 'a':
                // put stone in current game
                if (argc < 3) {
                    printf("argc error\n");
                    break;
                }
                for (counter = 2; counter < argc; counter++) {
                    sscanf(argv[counter], "%d", &inNum);
                    if (-2 < inNum && inNum < 36) addPutImfo(inNum);
                }
                break;
            case 'p':
                // put stone in current game and display
                if (argc < 3) {
                    printf("argc error\n");
                    break;
                }
                sscanf(argv[2], "%d", &inNum);
                readAvailable();
                readPutImfo();
                b = initBoard();
                for (counter = 0; counter < MAXTURN; counter++) {
                    tmp = getPutImfo(counter);
                    if (tmp == -2) break;
                    justput(&b, tmp, b.nextS);
                }
                addPutImfo(inNum);
                put(&b, inNum, b.nextS);
                printBoardImage(b);
                break;
            case 'u':
                // undo
                readAvailable();
                readPutImfo();
                addNewLinePutImfo();
                b = initBoard();
                for (counter = 0; counter < MAXTURN; counter++) {
                    tmp = getPutImfo(counter);
                    if (getPutImfo(counter + 1) != -2) {
                        addPutImfo(getPutImfo(counter));
                        justput(&b, tmp, b.nextS);
                    } else
                        break;
                }
                printBoardImage(b);
                break;
            case 'y':
                // clone last game
                readPutImfo();
                addNewLinePutImfo();
                for (counter = 0; counter < MAXTURN; counter++) {
                    if (getPutImfo(counter) != -2)
                        addPutImfo(getPutImfo(counter));
                    else
                        break;
                }
                break;
            case 'r':
                // randumput
                readAvailable();
                readPutImfo();
                b = initBoard();
                for (counter = 0; counter < MAXTURN; counter++) {
                    tmp = getPutImfo(counter);
                    if (tmp == -2) break;
                    justput(&b, tmp, b.nextS);
                }
                tmp = randumPutCoo(b, b.nextS);
                int check = put(&b, tmp, b.nextS);
                if (check) addPutImfo(tmp);
                printBoardImage(b);
                break;
            case 's':
                // print score
                readAvailable();
                readPutImfo();
                b = initBoard();
                for (counter = 0; counter < MAXTURN; counter++) {
                    tmp = getPutImfo(counter);
                    if (tmp == -2) break;
                    justput(&b, tmp, b.nextS);
                }
                printf("black: %d, white: %d\n", getBlackN(b), getWhiteN(b));
                break;
            case 'v':
                // add last result to results.csv
                if (argc < 3) {
                    printf("argc error\n");
                    break;
                }
                sscanf(argv[2], "%d", &inNum);
                FILE *fp;
                fp = fopen("datas/results.csv", "a");
                if (fp == NULL) {
                    printf("fault in open result.csv.\n");
                    return -1;
                }
                fprintf(fp, "%d,", inNum);
                readPutImfo();
                for (counter = 0; counter < MAXTURN; counter++) {
                    tmp = getPutImfo(counter);
                    if (tmp != -2)
                        fprintf(fp, "%d,", getPutImfo(counter));
                    else
                        break;
                }
                fprintf(fp, "\n");
                fclose(fp);
                break;
            case 'h':
                // show available coo
                readAvailable();
                readPutImfo();
                b = initBoard();
                for (counter = 0; counter < MAXTURN; counter++) {
                    tmp = getPutImfo(counter);
                    if (tmp == -2) break;
                    justput(&b, tmp, b.nextS);
                }
                int availableCooN = allAvailable(b, b.nextS);
                if (availableCooN == 0) {
                    printf("cannot put anywhere. please type \"./m p -1\" \n");
                    break;
                }
                for (int i = 0; i < availableCooN; i++) {
                    printf("%d)%d, ", i + 1, numberPutCoo(b, b.nextS, i));
                }
                printf("\n");
                break;
            default:
                printf(
                    "c)clear, n)new, d)printList, l)display, a)add, s)printN\n"
                    "p)put, r)randamPut, j)now, b)deleteOne, y)copy, "
                    "m)comment\n");
                break;
        }
    }

    return 0;
}