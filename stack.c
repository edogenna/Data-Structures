#include <stdio.h>
#include <stdlib.h>


//REMEMBER TO INITIALISE THE TOP AT NULL
typedef struct stackLinkedList_{
    struct stackLinkedList_ *next;
    int n;
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

    tmp->n = n;
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
        printf("%d\n", top->n);
        top = top->next;
    }
}

int isStackLLVoid(stackLinkedList_t *top){
    return top == NULL ? 1 : 0;
}

typedef struct stackArray_{
    int top;
    int *array;
    unsigned capacity;
}stackArray_t;

