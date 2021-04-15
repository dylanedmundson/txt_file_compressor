#include "compressHoff.h"

mPriorityQueue *initPriQ() {
    mPriorityQueue *priq = (mPriorityQueue *) malloc(sizeof(mPriorityQueue));
    priq->head = NULL;
    priq->size = 0;
    return priq;
}

void priQAdd(mPriorityQueue *pq, tNode *tnode) {
    mNode *nnode = initmNode(tnode);
    if (pq->head == NULL) {
        pq->head = nnode;
    } else if (nnode->data->freq < pq->head->data->freq) {
        nnode->next = pq->head;
        pq->head = nnode;
    } else {
        mNode *next = pq->head;
        while (next->next != NULL && nnode->data->freq >= next->next->data->freq) {
            next = next->next;
        }
        nnode->next = next->next;
        next->next = nnode;
        next = NULL;
        free(next);
    }
    pq->size++;
}

tNode *pop(mPriorityQueue *pq) {
    if(pq->size == 0) {
        return NULL;
    }
    mNode *holder = pq->head;
    tNode *data = holder->data;
    pq->head = pq->head->next;
    pq->size--;
    free(holder);
    return data;
}

mNode *initmNode(tNode *tnode) {
    mNode *n = (mNode *) malloc(sizeof(mNode));
    n->next = NULL;
    n->data = tnode;
    return n;
}

void printQueue(mPriorityQueue *pq) {
    mNode *next = pq->head;
    while (next != NULL)
    {
        printf("%c|%d ", next->data->c, next->data->freq);
        next = next->next;
    }
    next = NULL;
    free(next);
    printf("\n");
}

tNode *contains(mPriorityQueue *pq, tNode *tn) {
    mNode *next = pq->head;
    while (next != NULL && next->data->c != tn->c)
    {
        next = next->next;
    }
    if (next == NULL) {
        return NULL;
    } else {
        return next->data;
    }
}
