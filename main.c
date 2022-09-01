#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "hs/available.h"
#include "hs/board.h"
#include "hs/otherfunc.h"
#include "hs/putImfo.h"
#include "hs/record.h"
#include "hs/results.h"

#define MAXCMDSIZE 30

void handler_quit(int sig){
    //do nothing
}

int parseCmd(char *command, char cmdVel[][MAXCMDSIZE]) {
    char *p = strtok(command, " ");
    int i = 0;
    while (p != NULL && i < 3) {
        strcpy(cmdVel[i++], p);
        p = strtok(NULL, " ");
    }
    printf("!%d!\n", i);
    return i;
}

void printHelp() { printf("type \"h\" display some imformation.\n"); }

void printCmdImfo() { printf("1st 2nd 3rd ex.\n"); }

void putPlus(board *b, coo c, record *rec) {
    int putResult = justput(b, c, b->nextS);
    switch (putResult) {
        // cannot put
        case 0:
            printf("cannot put. (%c at x:%d y:%d)\n", view(b->nextS), colIndex(c),
                   rowIndex(c));
            break;
        // normal
        case 1:
            printf("put (%c at x:%d y:%d)\n", view(b->nextS), colIndex(c),
                   rowIndex(c));
            addRecord(rec, c);
            printBoardImage(*b);
            break;
        // change player
        case 2:
            printf("change player %c->%c\n", view(b->nextS), view(3 - b->nextS));
            addRecord(rec, c);
            printBoardImage(*b);
            break;
        // cannot change player
        case 3:
            printf("cannot change player. %c can put %d place.\n", view(b->nextS),
                   allAvailable(*b, b->nextS));
            break;
        default:
            assert(0);
            break;
    }
}

int main(int argc, char *argv[]) {
    // if(signal(SIGINT, handler_quit) == SIG_ERR){perror("signal"); exit(1);}
    int cmdN;
    char command[MAXCMDSIZE];
    char cmdVel[3][MAXCMDSIZE];
    int n, m;
    record rec = initRecord();

    board b = initBoard();
    printBoardImage(b);
    readAvailable();

    while (1) {
        printf(">");
        fgets(command, MAXCMDSIZE, stdin);
        pint(*(command+1));
        sleep(10);
        cmdN = parseCmd(command, cmdVel);
        // sleep(1);
        if (strlen(cmdVel[0]) != 1) {
            printf("first command must be 1 one letter.\n");
            printCmdImfo();
            continue;
        }

        switch (cmdVel[0][0]) {
            // "put 27" or "put 3 4"
            case 'p':
                switch (cmdN) {
                    case 1:
                        printf("second command must be number.\n");
                        break;
                    case 2:
                        n = strtol(cmdVel[1], NULL, 0);
                        if (errno != 0) {
                            printf("second command must be number.\n");
                            continue;
                        }
                        putPlus(&b, n, &rec);
                        break;
                    case 3:
                        n = strtol(cmdVel[1], NULL, 0);
                        if (errno != 0) {
                            printf("second command must be number.\n");
                            continue;
                        }
                        m = strtol(cmdVel[2], NULL, 0);
                        if (errno != 0) {
                            printf("third command must be number.\n");
                            continue;
                        }
                        putPlus(&b, newcoo(n, m), &rec);
                        break;
                    default:
                        printf("%d\n", cmdN);
                        assert(0);
                        break;
                }
            case 's':
            default:
                break;
        }
    }
    return 0;
}