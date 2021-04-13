
/* node that will hold elements of list */
typedef struct tNode
{
    char c;
    int freq;
    struct tNode *left;
    struct tNode *right;
}tNode;

typedef struct Node
{
    struct Node *next;
    tNode *data;
}mNode;

/* structure of the priority queue */
typedef struct
{
    mNode *head;
    int size;
} mPriorityQueue;

/* initializes priority queue setting head = null
and size to be zero */
mPriorityQueue *initPriQ(void);

/* adds data to the list and organizes it into
based off the proper priority */
void priQAdd(mPriorityQueue *, tNode *);

/* initializes new node to have with data and 
pointers to children initiated to NULL and
frequency to zero */
mNode *initmNode(tNode *);

/* prints out the values of the tree nodes
in the priority queue */
void printQueue(mPriorityQueue *);

/* removes node from front of queue and returns it */
tNode *pop(mPriorityQueue *);

/* checks to see if priority queue has tNode with character c*/
tNode *contains(mPriorityQueue *pq, tNode *);