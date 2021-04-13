#include "datastructures/compressHoff.h"
#include <time.h>
#include <ctype.h>
enum boolean {false, true};
typedef enum boolean boolean;
const int low = 10;
const int high = 100;

int getRand() {
    return rand() % (high - low + 1) + low;
}

void sortArr(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[j] > arr[i]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
} 
/* priorityQueue test */
void testinit() {
    mPriorityQueue *pq = initPriQ();
    printf("\tinitPriQ: ");
    if (pq == NULL || pq->head != NULL || pq->size != 0) {
        printf("Fail");
    } else {
        printf("Pass");
    }
    printf("\n");
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
    if (assertEquals(pq->size, size) == false) {
        printf("actual size: %d, expected size: %d | ", pq->size, size);
        return false;
    }
    mNode *next = pq->head;
    for (int i = 0; i < size; i++) {
        if (assertEquals(arr[i], next->data->freq) == false) {
            printf("size %d at index %d | ", size, i);
            free(next);
            free(arr);
            free(pq);
            return false;
        }
        next = next->next;
    }
    free(next);
    free(arr);
    free(pq);
    return true;
}
void testAdd() {
    /* add to empty queue */
    printf("\tpriQAdd: ");
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
        if (assertEquals(arr[i], next->data->freq) == false) {
            printf("Fail at check 1\n");
            return;
        }
        next = next->next;
    }
    free(pq);
    free(next);

    /* check 2 (varying sizes) */
    if (testAddSize(50) == false || testAddSize(100) == false ||
    testAddSize(1000) == false) {
        printf("Fail at check 2\n");
        return;
    }

    printf("Pass\n");
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
            printf("size %d at index %d | ", size, i);
            free(arr);
            free(pq);
            return false;
        }
    }
    if (!assertEquals(pq->size, 0) || pq->head != NULL) {
        printf("fail at size %d, size not zero or head not null", size);
        return false;
    }
    free(arr);
    free(pq);
    return true;
}
void testPop() {
    printf("\tpop: ");
    mPriorityQueue *pq = initPriQ();
    if (pop(pq) != NULL) {
        printf("Fail empty pq\n");
        return;
    }
    tNode *tn = inittNode('a', 10);
    priQAdd(pq, tn);
    if (!assertEquals(tn->freq, pop(pq)->freq) || pq->size != 0 || pq->head != NULL) {
        printf("Fail pq size 1\n");
        return;
    }

    if (!testPopSize(50) || !testPopSize(100) || !testPopSize(1000)) {
        printf("Fail at check 2\n");
        return;
    }

    printf("Pass\n");
}

void testContains() {
    printf("\tcontains: ");
    mPriorityQueue *pq = initPriQ();
    for (int i = 0; i < 10; i++) {
        tNode *tn = inittNode((char)i, i);
        priQAdd(pq, tn);
        if(contains(pq, tn) == NULL) {
            printf("Fail at does contain\n");
            return;
        }
    }
    tNode *val = contains(pq, inittNode((char)11, 11));
    tNode *val2 = contains(pq, inittNode((char)12, 11));
    tNode *val3 = contains(pq, inittNode((char)13, 11));

    if (val != NULL || val2 != NULL || val3 != NULL) {
        printf("Fail at doesn't contain\n");
        return;
    }
    printf("Pass\n");
}

void pb(unsigned int val) {
    if (val != 0) {
        pb(val / 2);
        printf("%d",(val % 2));
    }
}

void printBinary(unsigned int val) {
    if (val == 0) {
        printf("%d", 0);
    } else {
        pb(val);
    }
    printf("\n");
}

int main() {
    time_t t;
    srand((unsigned)time(&t));
    printf("Start PriorityQueue Tests:\n");
    testinit();
    testAdd();
    testPop();
    testContains();

    printf("\nStart CompressHoff Tests:\n");
    // unsigned int bit_buff = 0x0000000000000001;
    // printBinary(bit_buff);
    // bit_buff = bit_buff << 1;
    // printBinary(bit_buff);
    // bit_buff++;
    // printBinary(bit_buff);
    // bit_buff = bit_buff << 1;
    // printBinary(bit_buff);
    compress("small.txt");

    return 0;
}