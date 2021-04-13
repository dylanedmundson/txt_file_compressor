#include "priorityQueue.h"
#include <stdlib.h>
#include <stdio.h>

typedef unsigned long ulong;
typedef unsigned int uint;

tNode *inittNode(char, int);

/* takes the string value for the name of a .txt file
and compresses that file into a new .comp file*/
void compress(char *);

/* takes a .comp file and extracts its contents into a
.txt file */
void extract(char *);

/* helper methods */
char *changeExt(char *, char *);
mPriorityQueue *buildFreqList(FILE *);
tNode *buildTree(mPriorityQueue *);
void writeCompression(FILE *, FILE *, char *, uint *);
void decompress(FILE *);
// void printTree(tNode *);
// int printTreeSpaces(tNode *);