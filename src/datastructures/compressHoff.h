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

/* changes the extention of file of first argument to second argument
example changeExt("test.txt", ".comp") will change file test.txt to test.comp */
char *changeExt(char *, char *);
/* builds a frequency list in a priority queue given a text file */
mPriorityQueue *buildFreqList(FILE *);
/* builds a huffman binary tree given the frequency list */
tNode *buildTree(mPriorityQueue *);
void writeCompression(FILE *, FILE *, char *, uint *);
void decompress(FILE *);