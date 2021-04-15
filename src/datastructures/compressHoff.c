/* structure and methods for reading a textfile, compressing it and writing
the compressed file */

/* 
    1 create priority queue (prioritize by Frquency)
    2 remove 2 with highest priority (lowest frequency)
    3 create a tree node with these two nodes as children and a frequency equal to the sum of both nodes
    4 add new node to priority queue
    5 when tree is build the it is used to store characters as bits sequences
        start at top node if 0 go L, if 1 go R, continue untill a node with no
        children is reached and print character
        return to header node and repeat untill the file ends*/

#include "compressHoff.h"

tNode *inittNode(char c, int freq) {
    tNode *tn = (tNode *) malloc(sizeof(tNode));
    tn->c = c;
    tn->freq = freq;
    tn->left = NULL;
    tn->right = NULL;
    return tn; 
}

void compress(char *fileName) {
    FILE *read = fopen(fileName, "r");
    char *newExt = changeExt(fileName, ".comp");

    mPriorityQueue *pq = buildFreqList(read);
    char *arr = (char *) malloc(sizeof(char) * pq->size);
    uint size = pq->size;
    for (int i = 0; i < size; i++) {
        arr[i] = pop(pq)->c;
        printf("%c", arr[i]);
    }
    fclose(read);

    read = fopen(fileName, "r");
    FILE *write = fopen(newExt, "wb");
    writeCompression(read, write, arr, &size);
    fclose(write);
    write = fopen(newExt, "rb");
    decompress(write);

    fclose(read);
    fclose(write);
}

void decompress(FILE *read) {
    //get metaData
    uint *refsize = (uint *) malloc(sizeof(uint));
    *refsize = 0;
    fread(refsize, sizeof(int), 1, read);
    char *ref = (char *) malloc(sizeof(char) * *refsize);
    fread(ref, sizeof(char), *refsize, read);

    //write data
        //TODO Implement
    //free pointers
    free(ref);
    free(refsize);

}
char *changeExt(char *fileName, char *ext) {
    int size = 0;
    int i = 0;
    int stop = 0;
    while(fileName[i] != '.') {
        i++;
    }
    stop = i;
    while (ext[i - stop] != '\0')
    {
        i++;
    }
    size = i++;
    char *newName = (char *) malloc(sizeof(char) * size);
    for (i = 0; i < size; i++) {
        if (i > stop) {
            newName[i] = ext[i - stop];
        } else {
            newName[i] = fileName[i];
        }
    }
    return newName;
}

void writeCompression(FILE *read, FILE *write, char *ref, uint *refSize) {
    //firt binary is integer with size of array
    fwrite(refSize, sizeof(int), 1, write);
    //first line is ref
    fwrite(ref, sizeof(char), *refSize, write);
    
    //get characters and load binary to buffer
    ulong *buffer = (ulong *) malloc(sizeof(ulong));
    *buffer = 0x00000000000000000000000000000000;
    int c;
    int count = 0;
    while ((c = fgetc(read)) != EOF)
    {
        for (int i = 0; i < *refSize; i++) {
            if (count == 32) {
                fwrite(buffer, sizeof(uint), 1, write);
                count = -1;
                *buffer = 0x00000000000000000000000000000000;

                //TODO figure out binary shift, I can use incrementing before and after with
                //shifting to figure out if the binary actually works, still need to figure out
                //binary tree(my implementation will not work)
            }
            if (c != ref[i]) {
                if (count == 0) {
                    //do nothing
                } else if (count % 2) {
                    (*buffer)++;
                } else {
                   (*buffer) = (*buffer) << 1;
                }
            }
            count++;
        }
    }
    (*buffer) = (*buffer) << (32 - count);
    fwrite(buffer, sizeof(uint), 1, write);
}

mPriorityQueue *buildFreqList(FILE *read) {
    mPriorityQueue *pq = initPriQ();
    mPriorityQueue *pq2 = initPriQ();
    int c;
    while ((c = fgetc(read)) != EOF) {
        tNode *next = inittNode((char)c, 1);
        tNode *curr = contains(pq, next);
        if (curr != NULL) {
            curr->freq++;
        } else {
            priQAdd(pq, next);
        }
        
        next = NULL;
        curr = NULL;
        free(next);
        free(curr);
    }
    tNode *next = pop(pq);
    while (next != NULL)
    {
        priQAdd(pq2, next);
        next = pop(pq);
    }
    free(pq);
    return pq2;
}


tNode *buildTree(mPriorityQueue *pq) {
    tNode **heads = (tNode **) malloc(sizeof(tNode) * pq->size), *next;
    int i = 0;
    heads[i] = inittNode('\0', -1);
    while ((next = pop(pq)) != NULL)
    {
        if (heads[i]->freq == -1) {
            if (heads[i]->left == NULL) {
                heads[i]->left = next;
            } else if (heads[i]->right == NULL) {
                heads[i]->right = next;
                heads[i]->freq = heads[i]->left->freq + heads[i]->right->freq;
            }
        } else if (next->freq < heads[i]->freq) {
            i++;
            heads[i] = inittNode('\0', -1);
        } else {
            tNode *temp = heads[i];
            heads[i] = inittNode('\0', next->freq + heads[i]->freq);
            heads[i]->left = next;
            heads[i]->right = temp;
        }
    }
    for (int j = i; j > i; j++) {
        tNode *temp = heads[j -1];
        heads[j - 1] = inittNode('\0', heads[j - 1]->freq + heads[j]->freq);
        heads[j - 1]->left = temp;
        heads[j - 1]->right = heads[j];
    }
    next = NULL;
    free(next);
    tNode *head = heads[0];
    heads = NULL;
    free(heads);
    return head;
}