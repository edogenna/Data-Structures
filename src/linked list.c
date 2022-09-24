#include <stdio.h>
#include <stdlib.h>

typedef struct node_{
    int key;
    struct node_ *next;
}node_t;

node_t* appendList(node_t* list, int num){
    node_t *prec;
    node_t *tmp;
    tmp = malloc(sizeof(node_t));

    tmp->next = NULL;
    tmp->key = num;
    if(list == NULL)
        list = tmp;
    else{
        for(prec = list; prec->next != NULL; prec = prec->next);
        prec->next = tmp;
    }

    return list;
}


node_t* pushList(node_t* list, int num){
    node_t *tmp;
    tmp = malloc(sizeof(node_t));

    tmp->key = num;
    tmp->next = list;
    list = tmp;

    return list;
}

//the list must be sorted before insertion
node_t* insertInOrderedList(node_t* head, int n){
    if (!head || head->key > n)
        return pushList(head,n);
    head->next = insertInOrderedList(head->next, n);
    return head;
}

void printElementsInList(node_t* list){
    printf("list: ");
    while(list != NULL){
        printf("%d ", list->key);
        list = list->next;
    }
    printf("\n");
}


node_t* freeAllNodesInList(node_t* list){
    node_t* tmp;
    while(list!= NULL){
        tmp = list;
        list = list->next;
        free(tmp);
    }

    return NULL;
}

int searchInList(node_t* list, int num){
    for(; list && list->key != num; list = list->next);
    return (list != NULL);
}


node_t* deleteFirstOccurrenceInList(node_t* list, int num){
    node_t *curr, *prec, *canc;
    int found;

    found=0;
    curr = list;
    prec = NULL;
    while(curr && ! found){
        if(curr->key == num){
            found=1;
            canc = curr;
            curr = curr->next;
            if(prec!=NULL)
                prec->next = curr;
            else
                list = curr;
            free(canc);
        }
        else{
            prec=curr;
            curr = curr->next;
        }
    }
    return list;

}


node_t* deleteAllOccurrencesInList(node_t* list, int num){
    node_t *curr, *prec, *canc;

    curr = list;
    prec = NULL;
    while(curr){
        if(curr->key == num){
            canc = curr;
            curr = curr->next;
            if(prec != NULL)
                prec->next = curr;
            else
                list = curr;
            free(canc);
        }
        else{
            prec = curr;
            curr = curr->next;
        }
    }
    return list;
}
;