#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include "hs/board.h"
#include "hs/available.h"
#include "hs/putImfo.h"
#include "hs/tree.h"
#include "hs/otherfunc.h"

int main(int argc, char** argv){
    board b;
    tnode tn;
    time_t st, et;

    readAvailable();
    readPutImfo();

    b = initBoard();
    justput(&b, 27, b.nextS);
    tn = initTnode(b);

    st = time(NULL);
    makeTree(tn, atoi(argv[1]));
    et = time(NULL);
    printf("time: %ld\n", et-st);
    // printf("made\n");
    // printTree(pn);
    return 0;
}