#include <stdio.h>
#include <stdlib.h>

//--------------------------------//
// USING A LINKED LIST AS A STACK
//--------------------------------//

//REMEMBER TO INITIALISE THE TOP AT NULL
typedef struct stackLinkedList_{
    struct stackLinkedList_ *next;
    int key;
}stackLinkedList_t;

//returns the new top
stackLinkedList_t *popStackLL(stackLinkedList_t *top){
    if(top == NULL){
        printf("stack is empty\n");
        return NULL;
    }

    stackLinkedList_t *tmp = top;
    top = top->next;
    free(tmp);
    return top;
}

//returns the new top
stackLinkedList_t *pushStackLL(stackLinkedList_t *top, int n){
    stackLinkedList_t *tmp = malloc(sizeof(stackLinkedList_t));
    if(tmp == NULL) {
        printf("Malloc Error");
        return top;
    }

    tmp->key = n;
    tmp->next = top;

    return tmp;
}

int countElementsInStackLL(stackLinkedList_t *top){
    int count = 0;

    while(top != NULL){
        count++;
        top = top->next;
    }

    return count;
}

void printElementsInStackLL(stackLinkedList_t *top){
    while(top != NULL){
        printf("%d\n", top->key);
        top = top->next;
    }
}

int isStackLLEmpty(stackLinkedList_t *top){
    return top == NULL;
}

//--------------------------------//
// USING AN ARRAY AS A STACK
//--------------------------------//

typedef struct stackArray_{
    int top; //highest position occupied
    int *array;
    unsigned capacity;
}stackArray_t;

stackArray_t *inizializeStackArray(unsigned capacity){
    stackArray_t *s = malloc(sizeof(stackArray_t));
    if(s == NULL) {
        printf("Malloc Error");
        return NULL;
    }

    s->array = malloc(sizeof(int)*capacity);
    if(s == NULL) {
        printf("Malloc Error");
        return NULL;
    }
    s->capacity = capacity;
    s->top = -1;

    return s;
}

int isStackArFull(stackArray_t *stack)
{
    return stack->top == stack->capacity - 1;
}

int isStackArEmpty(stackArray_t *stack)
{
    return stack->top == -1;
}

void pushStackArray(stackArray_t *stack, int n){
    if(isStackArFull(stack)){
        printf("The stack is full\n");
        return;
    }
    stack->top ++;
    stack->array[stack->top] = n;
}

int popStackArray(stackArray_t *stack){
    if(isStackArEmpty(stack)){
        printf("The stack is empty\n");
        return INT_MIN;
    }

    int n = stack->array[stack->top];
    stack->top --;
    return n;
}