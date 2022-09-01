#include <stdio.h>
#include "hs/board.h"
#include "hs/putImfo.h"
#include "hs/otherfunc.h"
#include "hs/available.h"

int main(int argc, char* argv[]){
    int tmp, counter, pren = 0;
    int bN, wN, winner;
    board b = initBoard();
    int* randoms = randInts(72);
    readAvailable();

    addNewLinePutImfo();
    justput(&b, 27, b.nextS);
    addPutImfo(27);
    for(counter=2; counter<argc; counter++){
        if(sscanf(argv[counter], "%d", &tmp)==0 || tmp>35){
            printf("failed.\n");
            return 0;
        }
        justput(&b, tmp, b.nextS);
        addPutImfo(tmp);
    }

    counter = 0;
    while(1){
        tmp = allAvailable(b, b.nextS);
        if(getN(b) == 36){
            printf("board is full.\n");
            break;
        }
        if(tmp == 0){
            if(pren == 1){
                printf("both cannot put.\n");
                break;
            }
            pren = 1;
            addPutImfo(-1);
            justput(&b, -1, b.nextS);
        }else{
            pren = 0;
            tmp = numberPutCoo(b, b.nextS, randoms[counter]%tmp+1);
            addPutImfo(tmp);
            justput(&b, tmp, b.nextS);
            counter++;
        }
    }

    printBoardImage(b);
    printf("###############################\n");
    bN = getBlackN(b);
    wN = getWhiteN(b);
    winner = (bN<wN) + 1;
    if(bN==wN) winner = 0;
    printf("black: %d, white: %d\n", getBlackN(b), getWhiteN(b));
    printf("###############################\n");

    FILE *fp;
    fp=fopen("datas/results.csv", "a");
    if(fp==NULL){
        printf("fault in open result.csv.\n");
        return -1;
    }
    fprintf(fp, "%d,", winner);
    readPutImfo();
    for(counter=0; counter<100; counter++){
        tmp = getPutImfo(counter);
        if(tmp != -2)
            fprintf(fp, "%d,", getPutImfo(counter));
        else
            break;
    }
    fprintf(fp, "\n");
    fclose(fp);
    printf("witing in result.csv sucsess.\n");

    return 0;
}