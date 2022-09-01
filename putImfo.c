#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hs/otherfunc.h"
#define PUTSIZE 64
#define BUFSIZE 200
#define FNAME "datas/putImfo.csv"

static int putImfo[PUTSIZE];

int clearPutImfo() {
    FILE *fp;
    fp = fopen(FNAME, "w");
    if (fp == NULL) {
        printf("fault in clearPutImfo.\n");
        return -1;
    }
    fprintf(fp, "");
    fclose(fp);
    return 1;
}

int addPutImfo(int c) {
    FILE *fp;
    fp = fopen(FNAME, "a");
    if (fp == NULL) {
        printf("fault in addPutImfo.\n");
        return -1;
    }
    fprintf(fp, "%d,", c);
    fclose(fp);
    return 1;
}

int readPutImfo() {
    FILE *fp = fopen(FNAME, "r");
    char buf[BUFSIZE];
    char buf2[BUFSIZE];
    char *tmpbuf;
    int a;
    // reset -2
    for (int i = 0; i < PUTSIZE; i++) putImfo[i] = -2;
    // case fault
    if (fp == NULL) {
        printf("fault in readPutImfo.\n");
        return -1;
    }
    int j = 0;
    while (fgets(buf2, BUFSIZE, fp) != NULL) {
        strcpy(buf, buf2);
        j++;
    }
    printf("READPUTIMFO readline is %d\n", j);

    if ((tmpbuf = strtok(buf, ",")) != NULL)
        putImfo[0] = atoi(tmpbuf);
    else
        return -2;
    for (int i = 1; i < PUTSIZE; i++) {
        if ((tmpbuf = strtok(NULL, ",")) == NULL || strcmp(tmpbuf, "\n") == 0)
            break;

        putImfo[i] = atoi(tmpbuf);
    }
    fclose(fp);
    return 1;
}

int getPutImfo(int n) {
    /*
        after readPutImfo. return putImfo[n].
    */
    if (n < 0 || n >= PUTSIZE) return -2;
    return putImfo[n];
}

int addNewLinePutImfo() {
    FILE *fp;
    fp = fopen(FNAME, "a");
    if (fp == NULL) {
        printf("fault in addNewLinePutImfoPutImfo.\n");
        return -1;
    }
    fprintf(fp, "\n");
    fclose(fp);
    return 1;
}