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
    q->front = q->rear = NULL;
    return q;
}

void enqueueLL(queueLinkedList_t *q, int n){
    queueLLNode_t *newNode = malloc(sizeof(queueLLNode_t));
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