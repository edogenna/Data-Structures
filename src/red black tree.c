#include <stdio.h>
#include <stdlib.h>

typedef struct node_{
    struct node_* p;
    struct node_* left;
    struct node_* right;
    char color; // 'R' = red, 'B' = black
    int key;
}node_t;

typedef struct tree_{
    struct node_* root;
    struct node_* nil;
}tree_t;

void leftRotateRB(tree_t * t, node_t* x){
    node_t* y = x->right;
    x->right = y->left;

    if(y->left != t->nil)
        y->left->p = x;
    y->p = x->p;
    if(x->p == t->nil) //x is leaf
        t->root = y;
    else if(x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;

    y->left = x;
    x->p = y;
}
void rightRotateRB(tree_t * t, node_t* x){
    node_t* y = x->left;
    x->left = y->right;

    if(y->right != t->nil)
        y->right->p = x;
    y->p = x->p;
    if(x->p == t->nil)
        t->root = y;
    else if(x == x->p->right)
        x->p->right = y;
    else
        x->p->left = y;

    y->right = x;
    x->p = y;
}
void insertFixUpRB(tree_t * t, node_t* z){
    node_t *x, *y;
    if(z == t->root)
        t->root->color = 'B';
    else{
        x = z->p;
        if(x->color == 'R'){
            if(x == x->p->left){
                y = x->p->right;
                if(y->color == 'R'){
                    x->color = 'B';
                    y->color = 'B';
                    x->p->color = 'R';
                    insertFixUpRB(t,x->p);
                }else{
                    if(z == x->right){
                        z = x;
                        leftRotateRB(t,z);
                        x = z->p;
                    }
                    x->color = 'B';
                    x->p->color = 'R';
                    rightRotateRB(t,x->p);
                }
            }else{
                y = x->p->left;
                if(y->color == 'R'){
                    x->color = 'B';
                    y->color = 'B';
                    x->p->color = 'R';
                    insertFixUpRB(t,x->p);
                }else {
                    if (z == x->left) {
                        z = x;
                        rightRotateRB(t, z);
                        x = z->p;
                    }
                    x->color = 'B';
                    x->p->color = 'R';
                    leftRotateRB(t, x->p);
                }
            }
        }
    }
}
void insertRB(tree_t * t, int n) {
    node_t *x, *y, *z;
    y = t->nil;
    x = t->root;

    z = (node_t *) malloc(sizeof(node_t));
    if(z == NULL) {
        printf("Malloc Error");
        return;
    }

    z->key = n;
    z->left = t->nil;
    z->right = t->nil;
    z->color = 'R';

    while (x != t->nil) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->p = y;
    if (y == t->nil) {
        t->root = z;
        //printf("albero vuoto");
    } else if (z->key < y->key){
        y->left = z;
    }else{
        y->right = z;
    }

    //printf("inserito");
    insertFixUpRB(t, z);
}
tree_t* initializeRB(){
    tree_t* t;
    t = (tree_t*)malloc(sizeof(tree_t));
    if(t == NULL) {
        printf("Malloc Error");
        return NULL;
    }
    t->nil = (node_t*)malloc(sizeof(node_t));
    if(t->nil == NULL) {
        printf("Malloc Error");
        return NULL;
    }
    t->nil->left = NULL;
    t->nil->right = NULL;
    t->nil->color = 'B';
    t->root = t->nil;

    return t;
}
int leavesInorderRB(tree_t* t, node_t* n,int lev){
    int l, r;
    if (n != t->nil) {
        l = leavesInorderRB(t, n->left, lev+1);
        printf("%c %d lev: %d\n",n->color, n->key, lev);
        r = leavesInorderRB(t, n->right, lev+1);
        return l+r+1;
    }
    return 0;
}
int inorderWalkRB(tree_t* t){
    return leavesInorderRB(t,t->root,0);
}

node_t* leavesSearchRB(tree_t* t, node_t* n, int k){
    if(n == NULL)
        return  n;
    if(k == n->key)
        return n;

    if(k < n->key)
        return leavesSearchRB(t, n->left, k);
    return leavesSearchRB(t, n->right, k);
}
node_t* searchRB(tree_t * t, int k){
    return leavesSearchRB(t, t->root, k);
}
