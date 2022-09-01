#ifndef OTHERFUNC_H
#define OTHERFUNC_H
#include <stdio.h>

int threePow(int);
#define pint(n) printf("%d\n", n);
int convert4to3(int);
void printArrayInt(int* array, int n);
int randInt(int n);
int* randInts(int num);
int myrand();
void log_q(const char *fmt, ...);
void setLogQuiet(int bool);

#endif