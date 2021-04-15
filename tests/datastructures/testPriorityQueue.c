/* by return 0 test passes, by returning -1 test fails */
#include "datastructures/compressHoff.h"
#include "testUtils.h"
#include <time.h>
#include <ctype.h>
const int low = 10;
const int high = 100;

int getRand() {
    return rand() % (high - low + 1) + low;
}

void sortArr(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[i]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
} 
/* priorityQueue test */
testPass testinit() {
    mPriorityQueue *pq = initPriQ();
    if (pq == NULL || pq->head != NULL || pq->size != 0) {
        return FAIL;
    } else {
        return PASS;
    }
}

/* generates array with random integers between 
@const high and @const low */
void genRandArr(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        int r = getRand();
        arr[i] = r;
    }
}

/* tests if two integer values are equal */
boolean assertEquals(int expected, int actual) {
    return (expected == actual);
}

/* helper class for testing priQAdd for random 
arrays of different sizes */
boolean testAddSize(int size) {
    int *arr = (int *) malloc(sizeof(int) * size);
    mPriorityQueue *pq = initPriQ();
    genRandArr(arr, size);
    for (int i = 0; i < size; i++) {
        priQAdd(pq, inittNode('a', arr[i]));
    }
    sortArr(arr, size);
    if (assertEquals(pq->size, size) == F) {
        return F;
    }
    mNode *next = pq->head;
    for (int i = 0; i < size; i++) {
        if (assertEquals(arr[i], next->data->freq) == F) {
            free(next);
            free(arr);
            free(pq);
            return F;
        }
        next = next->next;
    }
    free(next);
    free(arr);
    free(pq);
    return T;
}
testPass testAdd() {
    /* add to empty queue */
    mPriorityQueue *pq = initPriQ();
    int arr[5] = {5, 4, 3, 2, 1};
    priQAdd(pq, inittNode('a', 3));

    /* add to end of queue*/
    priQAdd(pq, inittNode('a', 4));
    priQAdd(pq, inittNode('a', 5));

    /* add to front of queue*/
    priQAdd(pq, inittNode('a', 2));
    priQAdd(pq, inittNode('a', 1));

    /* check 1 (base)*/
    mNode *next = pq->head;
    for (int i = 0; i < 5; i++) {
        if (assertEquals(arr[i], next->data->freq) == F) {
            return FAIL;
        }
        next = next->next;
    }
    free(pq);
    free(next);

    /* check 2 (varying sizes) */
    if (testAddSize(50) == F || testAddSize(100) == F ||
    testAddSize(1000) == F) {
        return FAIL;
    }

    return PASS;
}

boolean testPopSize(int size) {
    int *arr = (int *) malloc(sizeof(int) * size);
    mPriorityQueue *pq = initPriQ();
    genRandArr(arr, size);
    for (int i = 0; i < size; i++) {
        priQAdd(pq, inittNode('a', arr[i]));
    }
    sortArr(arr, size);
    for (int i = 0; i < size; i++) {
        if (!assertEquals(arr[i], pop(pq)->freq)) {
            free(arr);
            free(pq);
            return F;
        }
    }
    if (!assertEquals(pq->size, 0) || pq->head != NULL) {
        return F;
    }
    free(arr);
    free(pq);
    return T;
}

testPass testPop() {
    printf("\tpop: ");
    mPriorityQueue *pq = initPriQ();
    if (pop(pq) != NULL) {
        return FAIL;
    }
    tNode *tn = inittNode('a', 10);
    priQAdd(pq, tn);
    if (!assertEquals(tn->freq, pop(pq)->freq) || pq->size != 0 || pq->head != NULL) {
        return FAIL;
    }

    if (!testPopSize(50) || !testPopSize(100) || !testPopSize(1000)) {
        return FAIL;
   }
   return PASS;
}

testPass testContains() {
    mPriorityQueue *pq = initPriQ();
    for (int i = 0; i < 10; i++) {
        tNode *tn = inittNode((char)i, i);
        priQAdd(pq, tn);
        if(contains(pq, tn) == NULL) {
            return FAIL;
        }
    }
    tNode *val = contains(pq, inittNode((char)11, 11));
    tNode *val2 = contains(pq, inittNode((char)12, 11));
    tNode *val3 = contains(pq, inittNode((char)13, 11));

    if (val != NULL || val2 != NULL || val3 != NULL) {
        return PASS;
    }
}

int main() {
    time_t t;
    srand((unsigned)time(&t));
    ASSERT_PASS_TEST(testinit())
    ASSERT_PASS_TEST(testAdd())
    ASSERT_PASS_TEST(testPop())
    ASSERT_PASS_TEST(testContains())
}