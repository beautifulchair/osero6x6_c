#ifndef RECORD_H
#define RECORD_H

typedef struct record{
    // int id;
    int n;
    int r[36];
    // struct record *next;
    // struct record *prev;
}record;

record initRecord();
void printRecord(record rec);
void addRecord(record *rec, int coo);
void undoRecord(record *rec);
record cloneRecord(record rec);

#endif