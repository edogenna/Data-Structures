typedef struct nodo_{
    struct nodo_* p;
    struct nodo_* left;
    struct nodo_* right;
    char color; // 'R' = red, 'B' = black
    int key;
}nodo_t;

typedef struct tree_{
    struct nodo_* root;
    struct nodo_* nil;
}tree_t;

void leftRotate(tree_t * t, nodo_t* x){
    nodo_t* y = x->right;
    x->right = y->left;

    if(y->left != t->nil)
        y->left->p = x;
    y->p = x->p;
    if(x->p == t->nil) //x è foglia
        t->root = y;
    else if(x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;

    y->left = x;
    x->p = y;
}
void rightRotate(tree_t * t, nodo_t* x){
    nodo_t* y = x->left;
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
void RBInsertFixUp(tree_t * t, nodo_t* z){
    nodo_t *x, *y;
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
                    RBInsertFixUp(t,x->p);
                }else{
                    if(z == x->right){
                        z = x;
                        leftRotate(t,z);
                        x = z->p;
                    }
                    x->color = 'B';
                    x->p->color = 'R';
                    rightRotate(t,x->p);
                }
            }else{
                y = x->p->left;
                if(y->color == 'R'){
                    x->color = 'B';
                    y->color = 'B';
                    x->p->color = 'R';
                    RBInsertFixUp(t,x->p);
                }else {
                    if (z == x->left) {
                        z = x;
                        rightRotate(t, z);
                        x = z->p;
                    }
                    x->color = 'B';
                    x->p->color = 'R';
                    leftRotate(t, x->p);
                }
            }
        }
    }
}
void RBInsert(tree_t * t, int n) {
    nodo_t *x, *y, *z;
    y = t->nil;
    x = t->root;

    z = (nodo_t *) malloc(sizeof(nodo_t));
    if (!z) {
        printf("Errore malloc");
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
    RBInsertFixUp(t, z);
}
tree_t* RBInitializer(){
    tree_t* t;
    t = (tree_t*)malloc(sizeof(tree_t));
    t->nil = (nodo_t*)malloc(sizeof(nodo_t));
    t->nil->left = NULL;
    t->nil->right = NULL;
    t->nil->color = 'B';
    t->root = t->nil;

    return t;
}
int inorderRBLeaves(tree_t* t, nodo_t* n,int lev){
    int l, r;
    if (n != t->nil) {
        l = inorderRBLeaves(t, n->left, lev+1);
        printf("%c %d lev: %d\n",n->color, n->key, lev);
        r = inorderRBLeaves(t, n->right, lev+1);
        return l+r+1;
    }
    return 0;
}
int inorderRBWalk(tree_t* t){
    return inorderRBLeaves(t,t->root,0);
}
nodo_t* RBSearchLeaves(tree_t* t, nodo_t* n, int k){
    if(n == NULL)
        return  n;
    if(k == n->key)
        return n;

    if(k < n->key)
        return RBSearchLeaves(t, n->left, k);
    return RBSearchLeaves(t, n->right, k);
}
nodo_t* RBSearch(tree_t * t, int k){
    return RBSearchLeaves(t, t->root, k);
}

int main() {
    tree_t* t = RBInizializer();
    int n, nodi;

    scanf("%d", &n);
    while(n!=0){
        RBInsert(t,n);
        scanf("%d",&n);
    }

    nodi = inorderRBWalk(t);
    printf("nodi: %d", nodi);

    return 0;
}
