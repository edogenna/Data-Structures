#include <stdio.h>
#include <stdlib.h>

typedef struct node_{
    struct node_* p;
    struct node_* left;
    struct node_* right;
    int key;
}node_t;

int inorderWalkBST(node_t* t) {
    int l, r;
    if (t != NULL) {
        l = inorderWalkBST(t->left);
        printf("%d\n", t->key);
        r = inorderWalkBST(t->right);
        return l+r+1;
    }
    return 0;
}
node_t* insertBST(node_t* t, int n){
    node_t* y = NULL;
    node_t* x = t;
    node_t* z;

    z = (node_t*)malloc(sizeof(node_t));
    if(z == NULL) {
        printf("Malloc Error");
        return NULL;
    }
    z->key = n;
    z->left = NULL;
    z->right = NULL;


    while(x != NULL){
        y = x;
        if(z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->p = y;
    if(y == NULL)
        return z;
    else if(z->key < y->key)
        y->left = z;
    else
        y->right = z;

    return t;
}
node_t* searchBST(node_t* t, int k){
    if(t == NULL || k == t->key)
        return  t;
    if(k < t->key)
        return searchBST(t->left, k);
    return searchBST(t->right, k);
}
node_t* minimumBST(node_t* x){
    while(x->left != NULL)
        x = x->left;
    return x;
}

node_t* maximumBST(node_t* x){
    while(x->right != NULL)
        x = x->right;
    return x;
}

node_t* successorBST(node_t* x){
    node_t* y;
    if(x->right == NULL)
        return minimumBST(x->right);
    y = x->p;
    while (y != NULL && x == y->right){
        x = y;
        y = y->p;
    }
    return y;
}
void deleteNodeBST(node_t* t, node_t* z){
    //y è il nodo da eliminare
    //x è quello con cui lo sostituiamo
    node_t *x, *y;
    if(z->left == NULL || z->right == NULL)
        y = z;
    else
        y = successorBST(z);

    if(y->left != NULL)
        x = y->left;
    else
        x = y->right;

    if(x != NULL)
        x->p = y->p;

    if(y->p == NULL)
        t = x;
    else if(y == y->p->left)
        y->p->left = x;
    else
        y->p->right = x;

    if(y != z)
        z->key = y->key;

    free(y);
}
