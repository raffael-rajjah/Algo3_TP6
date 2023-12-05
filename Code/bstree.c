#include "bstree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

void bstree_remove_node(ptrBinarySearchTree *t, ptrBinarySearchTree current);

/*------------------------  BSTreeType  -----------------------------*/

struct _bstree {
    BinarySearchTree *parent;
    BinarySearchTree *left;
    BinarySearchTree *right;
    NodeColor nodeColor;
    int root;
};

/*------------------------  BaseBSTree  -----------------------------*/

BinarySearchTree *bstree_create() {
    return NULL;
}

/* This constructor is private so that we can maintain the oredring invariant on
 * nodes. The only way to add nodes to the tree is with the bstree_add function
 * that ensures the invariant.
 */
BinarySearchTree *bstree_cons(BinarySearchTree *left, BinarySearchTree *right, int root) {
    BinarySearchTree *t = malloc(sizeof(struct _bstree));
    t->parent = NULL;
    t->left = left;
    t->right = right;
    if (t->left != NULL)
        t->left->parent = t;
    if (t->right != NULL)
        t->right->parent = t;
    
    t->root = root;
    t->nodeColor = red;
    return t;
}

void bstree_delete(ptrBinarySearchTree *t) {
    (void) t;
    
}

bool bstree_empty(const BinarySearchTree *t) {
    return t == NULL;
}

int bstree_root(const BinarySearchTree *t) {
    assert(!bstree_empty(t));
    return t->root;
}

BinarySearchTree *bstree_left(const BinarySearchTree *t) {
    assert(!bstree_empty(t));
    return t->left;
}

BinarySearchTree *bstree_right(const BinarySearchTree *t) {
    assert(!bstree_empty(t));
    return t->right;
}

BinarySearchTree *bstree_parent(const BinarySearchTree *t) {
    assert(!bstree_empty(t));
    return t->parent;
}

/*------------------------  BSTreeDictionary  -----------------------------*/

/* Obligation de passer l'arbre par référence pour pouvoir le modifier */
void bstree_add(ptrBinarySearchTree *t, int v) {
    
    ptrBinarySearchTree *cur = t;
    BinarySearchTree *par = NULL;
    BinarySearchTree *tmp = NULL;


    while (!bstree_empty(*cur)){   
        par = *cur;

        if(v < bstree_root(*cur)){
            tmp = bstree_left(*cur);
        }
        else {
            tmp = bstree_right(*cur);
        }

        *cur = tmp;
    }

    BinarySearchTree *newLeaf = bstree_cons(bstree_create(), bstree_create(), v);
    newLeaf->parent = par;
    *cur = newLeaf;

    if(!bstree_empty(par) && v < bstree_root(par)){
        par->left = newLeaf;
    }
    else if(!bstree_empty(par) && v > bstree_root(par)){
        par->right = newLeaf;
    }

    while(!bstree_empty(bstree_parent(*cur))){
        *cur = bstree_parent(*cur);
    }

}

bool bstree_search(const BinarySearchTree *t, int v) {
    const BinarySearchTree* currentNode = t;
    while (!bstree_empty(currentNode)){
        if (v < bstree_root(currentNode)){

            currentNode = bstree_left(currentNode);
        }
        else if (v > bstree_root(currentNode)){
            currentNode = bstree_right(currentNode);
        }
        else
            break;
        
    }

    return !bstree_empty(currentNode);
    
}

BinarySearchTree *bstree_successor(const BinarySearchTree *x) {
    assert(!bstree_empty(x));
    
    BinarySearchTree* currentNode = bstree_right(x);

    if (!bstree_empty(bstree_right(x)))
    {
        while (!bstree_empty(currentNode) && !bstree_empty(currentNode->left)){
            
            currentNode = bstree_left(currentNode);

        }
        

        /* code */
    }

    else{
        BinarySearchTree* parent = bstree_parent(x);
        if(!bstree_empty(bstree_parent(x))){
            if(parent->left == x) currentNode = parent->left;
            else currentNode = parent->right;
        }
        else{
            return NULL;
        }
        // currentNode = x;
        while (parent != NULL && currentNode == parent->right)
        {
            currentNode = parent;
            parent = currentNode->parent;
            // return parent;
        }
        
        
        currentNode = parent;
    }
    
    return currentNode;
}

BinarySearchTree *bstree_predecessor(const BinarySearchTree *x) {
    assert(!bstree_empty(x));
    
    // BinarySearchTree* currentNode = bstree_left(x);

    // while (!bstree_empty(currentNode) && !bstree_empty(currentNode->right)){
        
    //     currentNode = bstree_right(currentNode);

    // }
    

    // return currentNode;

    BinarySearchTree* currentNode = bstree_left(x);

    if (!bstree_empty(bstree_left(x)))
    {
        while (!bstree_empty(currentNode) && !bstree_empty(currentNode->right)){
            
            currentNode = bstree_right(currentNode);

        }
        

        /* code */
    }

    else{
        BinarySearchTree* parent = bstree_parent(x);
        if(!bstree_empty(bstree_parent(x))){ //bypass const
            if(parent->right == x) currentNode = parent->right;
            else currentNode = parent->left;
        }
        else{
            return NULL;
        }
        // currentNode = x;
        while (parent != NULL && currentNode == parent->left)
        {
            currentNode = parent;
            parent = currentNode->parent;
            // return parent;
        }
        
        
        currentNode = parent;
        
    }

    return currentNode;
}

void bstree_swap_nodes(ptrBinarySearchTree *tree, ptrBinarySearchTree from, ptrBinarySearchTree to) {
    assert(!bstree_empty(*tree) && !bstree_empty(from) && !bstree_empty(to));
    
    int tmp = from->root;

    from->root = to->root;
    to->root = tmp;

    (void) tree;

}

// t -> the tree to remove from, current -> the node to remove
void bstree_remove_node(ptrBinarySearchTree *t, ptrBinarySearchTree current) {
    assert(!bstree_empty(*t) && !bstree_empty(current));
    (void)t; 

    if(!bstree_empty(bstree_right(current))){
        
        bstree_swap_nodes(t, current, bstree_successor(current));
        free(current->right);
        current->right = NULL;

    }

    else if (!bstree_empty(bstree_left(current))){
        
        bstree_swap_nodes(t, current, bstree_predecessor(current));
        free(current->left);
        current->left = NULL;
    }

    else{

        if (current->parent->left == current){
            current->parent->left = NULL;
        }

        else if (current->parent->right == current){
            current->parent->right = NULL;
        }
        
        free(current);
        current = NULL;

    }
    

} 

void bstree_remove(ptrBinarySearchTree *t, int v) {
    (void)t; (void)v;

    if (!bstree_search(*t, v)){
        return;
    }
    

    BinarySearchTree* currentNode = *t;
    while (!bstree_empty(currentNode)){
        if (v < bstree_root(currentNode)){

            currentNode = bstree_left(currentNode);
        }
        else if (v > bstree_root(currentNode)){
            currentNode = bstree_right(currentNode);
        }
        else
            break;
        
    }

    bstree_remove_node(t, currentNode);
}

/*------------------------  BSTreeVisitors  -----------------------------*/

void bstree_depth_prefix(const BinarySearchTree *t, OperateFunctor f, void *userData) {
    if (bstree_empty(t)) {
        return;
    }

    f(t, userData);
    bstree_depth_prefix(t->left,f, userData);
    bstree_depth_prefix(t->right, f, userData);
    
    
}

void bstree_depth_infix(const BinarySearchTree *t, OperateFunctor f, void *userData) {
    if (bstree_empty(t)) {
        return;
    }

    bstree_depth_infix(t->left,f, userData);
    f(t, userData);
    bstree_depth_infix(t->right, f, userData);
}

void bstree_depth_postfix(const BinarySearchTree *t, OperateFunctor f, void *userData) {
        if (bstree_empty(t)) {
        return;
    }

    bstree_depth_postfix(t->left,f, userData);
    bstree_depth_postfix(t->right, f, userData);
    f(t, userData);
}

void bstree_iterative_depth_infix(const BinarySearchTree *t, OperateFunctor f, void *userData) {
    (void)t; (void) f; (void)userData;

    const BinarySearchTree *current = t;
    const BinarySearchTree *next = bstree_parent( t );
    const BinarySearchTree *prev = bstree_parent( t );

    while ( !bstree_empty( current ) ) {
        if (prev == bstree_parent( current ) ) {
            prev = current; 
            next = bstree_left( current );
        }
        if ( bstree_empty( next ) || prev == bstree_left( current ) ) {
            f(current, userData); 
            prev = current; 
            next = bstree_right( current );
        }
        if ( bstree_empty(next) || prev == bstree_right( current ) ) {
            prev = current; 
            next = bstree_parent( current );
        }

        current = next;
    }
 }

void bstree_iterative_breadth_prefix(const BinarySearchTree *t, OperateFunctor f, void *userData) {
    

    Queue* visited = createQueue();
    
    f(t, userData);
    const BinarySearchTree* currentNode = t;



    do{

        if (!bstree_empty(bstree_left(currentNode))){
            queuePush(visited, bstree_left(currentNode));
        }

        if (!bstree_empty(bstree_right(currentNode))){
            queuePush(visited, bstree_right(currentNode));
        }

        
        currentNode = queueTop(visited);
        f(currentNode, userData);
        queuePop(visited);
        

    }while (queueSize(visited) > 0);
    
    

}

/*------------------------  BSTreeIterator  -----------------------------*/

struct _BSTreeIterator {
    /* the collection the iterator is attached to */
    const BinarySearchTree *collection;
    /* the first element according to the iterator direction */
    const BinarySearchTree *(*begin)(const BinarySearchTree *);
    /* the current element pointed by the iterator */
    const BinarySearchTree *current;
    /* function that goes to the next element according to the iterator direction */
    BinarySearchTree *(*next)(const BinarySearchTree *);
};

/* minimum element of the collection */
const BinarySearchTree *goto_min(const BinarySearchTree *e) {
	(void)e;
    const BinarySearchTree* currentNode = e;

    while (!bstree_empty (bstree_predecessor(currentNode))){
        
        currentNode = bstree_predecessor(currentNode);

    }
    

	return currentNode;
}

/* maximum element of the collection */
const BinarySearchTree *goto_max(const BinarySearchTree *e) {
	(void)e;
	const BinarySearchTree* currentNode = e;

    while (!bstree_empty (bstree_successor(currentNode))){
        
        currentNode = bstree_successor(currentNode);

    }
    

	return currentNode;
}

/* constructor */
BSTreeIterator *bstree_iterator_create(const BinarySearchTree *collection, IteratorDirection direction) {
	(void)collection; (void)direction;

    BSTreeIterator* bst_iterator = malloc(sizeof(BSTreeIterator));

    bst_iterator->collection = collection;

    if (direction == forward){
        bst_iterator->begin = goto_min;
        bst_iterator->current = goto_min(bst_iterator->collection);
        bst_iterator->next = bstree_successor;
    }

    else{
        bst_iterator->begin = goto_max;
        bst_iterator->current = goto_max(bst_iterator->collection);
        bst_iterator->next = bstree_predecessor;
    }
    

	return bst_iterator;
}

/* destructor */
void bstree_iterator_delete(ptrBSTreeIterator *i) {
    free(*i);
    *i = NULL;
}

BSTreeIterator *bstree_iterator_begin(BSTreeIterator *i) {
    i->current = i->begin(i->collection);
    return i;
}

bool bstree_iterator_end(const BSTreeIterator *i) {
    return i->current == NULL;
}

BSTreeIterator *bstree_iterator_next(BSTreeIterator *i) {
    i->current = i->next(i->current);
    return i;
}

const BinarySearchTree *bstree_iterator_value(const BSTreeIterator *i) {
    return i->current;
}


void printNode(const BinarySearchTree *n, void *out){
    FILE *file = (FILE *) out;

    printf("%d ", bstree_root(n));
    fprintf(file, "\tn%d [style=filled, fillcolor=red, label=\"{{<parent>}|%d|{<left>|<right>}}\"];\n",
            bstree_root(n), bstree_root(n));

    if (bstree_left(n)) {
        fprintf(file, "\tn%d:left:c -> n%d:parent:c [headclip=false, tailclip=false]\n",
                bstree_root(n), bstree_root(bstree_left(n)));
    } else {
        fprintf(file, "\tlnil%d [style=filled, fillcolor=grey, label=\"NIL\"];\n", bstree_root(n));
        fprintf(file, "\tn%d:left:c -> lnil%d:n [headclip=false, tailclip=false]\n",
                bstree_root(n), bstree_root(n));
    }
    if (bstree_right(n)) {
        fprintf(file, "\tn%d:right:c -> n%d:parent:c [headclip=false, tailclip=false]\n",
                bstree_root(n), bstree_root(bstree_right(n)));
    } else {
        fprintf(file, "\trnil%d [style=filled, fillcolor=grey, label=\"NIL\"];\n", bstree_root(n));
        fprintf(file, "\tn%d:right:c -> rnil%d:n [headclip=false, tailclip=false]\n",
                bstree_root(n), bstree_root(n));
    }
}

void rbtree_export_dot ( const BinarySearchTree *t , FILE * file ) {
    fprintf (file , "digraph RedBlackTree {\n\tgraph [ ranksep =0.5];\n\tnode [ shape = record ];\n\n");
    bstree_iterative_depth_infix (t , printNode , file ) ;
    fprintf ( file , "\n}\n" ) ;
}


void leftrotate(BinarySearchTree *x){
    BinarySearchTree* y = x->right;
    x->right = y->left;
    if(!bstree_empty(y->left)){
        y->left->parent = x;
    }

    y->parent = x->parent;
    

    if(!(bstree_empty(x->parent)) && x == x->parent->left){
        x->parent->left = y;
    }

    else if(!bstree_empty(x->parent)){
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;

}

void rightrotate(BinarySearchTree *y){
    BinarySearchTree* x = y->left;
    y->left = x->right;
    if(!bstree_empty(x->right)){
        x->right->parent = y;
    }

    x->parent = y->parent;
    

    if(!bstree_empty(y->parent) && y == y->parent->right){
        y->parent->right = x;
    }

    else if (!bstree_empty(y->parent)){
        y->parent->left = x;
    }

    x->right = y;
    y->parent = x;
}

void testrotateleft(BinarySearchTree *t){
    leftrotate(t);
}

void testrotateright(BinarySearchTree *t){
    rightrotate(t);
}