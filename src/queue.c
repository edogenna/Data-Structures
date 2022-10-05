#include <stdio.h>
#include <stdlib.h>

//--------------------------------//
// USING A LINKED LIST AS A QUEUE
//--------------------------------//

//each node points to the previous one
typedef struct queueLLNode_{
    struct queueLLNode_ *next;
    int key;
}queueLLNode_t;

typedef struct queueLinkedList_{
    queueLLNode_t *front;
    queueLLNode_t *rear;
}queueLinkedList_t;

int isQueueLLEmpty(queueLinkedList_t *q){
    return q->rear == NULL;
}

queueLinkedList_t* createQueueLL(){
    queueLinkedList_t *q= malloc(sizeof(queueLinkedList_t));
    if(q == NULL) {
        printf("Malloc Error");
        return NULL;
    }
    q->front = q->rear = NULL;
    return q;
}

void enqueueLL(queueLinkedList_t *q, int n){
    queueLLNode_t *newNode = malloc(sizeof(queueLLNode_t));
    if(newNode == NULL) {
        printf("Malloc Error");
        return;
    }

    newNode->key = n;
    newNode->next = NULL;

    if(isQueueLLEmpty(q)){
        q->front = newNode;
        q->rear = newNode;
    }else{
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

void dequeueLL(queueLinkedList_t *q){
    if(isQueueLLEmpty(q)){
        printf("the queue is empty\n");
        return;
    }

    queueLLNode_t *oldFront = q->front;
    q->front = q->front->next;
    free(oldFront);

    //deleted the last node of the queue
    if(q->front == NULL){
        q->rear = NULL;
    }
}

void printElementsInQueueLL(queueLinkedList_t *q){
    queueLLNode_t *tmp = q->front;
    while(tmp){
        printf("%d\n", tmp->key);
        tmp = tmp->next;
    }
}

int countElementsInQueueLL(queueLinkedList_t *q){
    int count = 0;
    queueLLNode_t *tmp = q->front;

    while(tmp){
        count++;
        tmp = tmp->next;
    }

    return count;
}


//--------------------------------//
// USING AN ARRAY AS A QUEUE
//--------------------------------//

typedef struct queueArray_{
    int front, rear, size; //highest position occupied
    int *array;
    int capacity;
}queueArray_t;

queueArray_t *createQueueArray(int capacity){
    queueArray_t *q = malloc(sizeof(queueArray_t));
    if(q == NULL) {
        printf("Malloc Error");
        return NULL;
    }

    q->capacity = capacity;
    q->array = malloc(sizeof(int)*capacity);
    if(q->array == NULL) {
        printf("Malloc Error");
        return NULL;
    }

    q->front = q->size = 0;
    q->rear = capacity - 1;
}

int isQueueArrayFull(queueArray_t *q){
    return q->capacity == q->size;
}

int isQueueArrayEmpty(queueArray_t *q){
    return q->size == 0;
}

void enqueueArray(queueArray_t *q, int n){
    if(isQueueArrayFull(q)){
        printf("Queue is full\n");
        return;
    }

    q->rear = (q->rear + 1) % q->capacity;
    q->array[q->rear] = n;
    (q->size) ++;
}

int dequeueArray(queueArray_t *q){
    if(isQueueArrayEmpty(q)){
        printf("Queue is empty\n");
        return INT_MIN;
    }

    int n = q->array[q->front];
    (q->size) --;
    q->front = (q->front + 1) % q->capacity;
    return n;
}

//get the front of the queue, the oldest number insered
int frontQueueArray(queueArray_t *q){
    if(isQueueArrayEmpty(q)){
        printf("Queue is empty\n");
        return INT_MIN;
    }
    return q->array[q->front];
}

//get the rear of the queue, the latest number insered
int rearQueueArray(queueArray_t *q){
    if(isQueueArrayEmpty(q)){
        printf("Queue is empty\n");
        return INT_MIN;
    }
    return q->array[q->rear];
}