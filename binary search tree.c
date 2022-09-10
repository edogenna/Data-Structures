//
// Created by edoge on 04/07/2022.
//

typedef struct nodo_{
    struct nodo_* p;
    struct nodo_* left;
    struct nodo_* right;
    int key;
}nodo_t;

int inorderBSTWalk(nodo_t* t) {
    int l, r;
    if (t != NULL) {
        l = inorderBSTWalk(t->left);
        printf("%d\n", t->key);
        r = inorderBSTWalk(t->right);
        return l+r+1;
    }
    return 0;
}
nodo_t* BSTInsert(nodo_t* t, int n){
    nodo_t* y = NULL;
    nodo_t* x = t;
    nodo_t* z;

    z = (nodo_t*)malloc(sizeof(nodo_t));
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
nodo_t* BSTSearch(nodo_t* t, int k){
    if(t == NULL || k == t->key)
        return  t;
    if(k < t->key)
        return BSTSearch(t->left, k);
    return BSTSearch(t->right, k);
}
nodo_t* BSTMinimum(nodo_t* x){
    while(x->left != NULL)
        x = x->left;
    return x;
}
nodo_t* BSTMaximum(nodo_t* x){
    while(x->right != NULL)
        x = x->right;
    return x;
}
nodo_t* BSTSuccessor(nodo_t* x){
    nodo_t* y;
    if(x->right == NULL)
        return BSTMinimum(x->right);
    y = x->p;
    while (y != NULL && x == y->right){
        x = y;
        y = y->p;
    }
    return y;
}
void BSTDelete(nodo_t* t, nodo_t* z){
    //y è il nodo da eliminare
    //x è quello con cui lo sostituiamo
    nodo_t *x, *y;
    if(z->left == NULL || z->right == NULL)
        y = z;
    else
        y = BSTSuccessor(z);

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


int main() {
    int n, nodi;
    nodo_t* t;

    scanf("%d", &n);
    while(n!=0){
        BSTInsert(t,n);
        scanf("%d",&n);
    }

    nodi = inorderBSTWalk(t);
    printf("nodi: %d", nodi);

    return 0;
}
