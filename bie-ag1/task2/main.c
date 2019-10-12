#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    unsigned int key;
    struct node *left, *right, *parent;
}NODE;

NODE *BSTFind (NODE *root, unsigned int x) {

    while (root != NULL && x != root->key) {
        if (x < root->key)
            root = root->left;
        else
            root = root->right;
    }
    return root;
}

NODE *newNode(unsigned int key) {
    
    NODE *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = key;
    temp->left = temp->right = temp->parent = NULL;
    return temp;
}

NODE *BSTInsert(NODE *root, unsigned int key) {

    if (root == NULL) {
        return newNode(key);
    }
    
    if (key < root->key) {
        root->left = BSTInsert(root->left, key);
        root->left->parent = root;
    }
    else if (key > root->key) {
        root->right = BSTInsert(root->right, key);
        root->right->parent = root;
    }
    return root;
}



NODE *BSTMin(NODE *root) {

    while (root->left != NULL)
        root = root->left;

    return root;
    
}

NODE *BSTDelete(NODE *root, unsigned int key) {

    if (root == NULL) return NULL;
    

    if (key < root->key) {
        root->left = BSTDelete(root->left, key);
        if (root->left != NULL)
            root->left->parent = root;
        return root;
    }
    else if (key > root->key) {
        root->right = BSTDelete(root->right, key);
        if (root->right != NULL)
            root->right->parent = root;
        return root;
    }
    
    else  {
        if (root->left == NULL && root->right == NULL) {
            root->parent = NULL;
            free(root);
            return NULL;
        }
        else if (root->left == NULL) {
            root->right->parent = root->parent;
            return root->right;
        }
        else if (root->right == NULL) {
            root->left->parent = root->parent;
            return root->left;
        }
        NODE *s = BSTMin(root->right);
        root->key = s->key;
        root->right = BSTDelete(root->right, s->key);
        return root;
    }
}

NODE* BSTSuc (NODE *root, unsigned int key ) {
    
    NODE *x = BSTFind(root,key);

    if (x->right != NULL)
        return BSTMin(x->right);

    NODE *y = x->parent;

    while (y != NULL && x == y->right) {
        x = y;
        y = y->parent;
    }

    return y;
}

int BSTParent (struct node *root, unsigned int x) {

    NODE *tmp = BSTFind(root,x);

    if (tmp->parent == NULL)
        return 0;

    else
        return tmp->parent->key;

    
}

struct node* BSTRotateRight(struct node *root, unsigned int key) {

    NODE *y = BSTFind(root,key);
    NODE *x = NULL;

    if (y->left == NULL)
        return NULL;

    x = y->left;
    y->left = x->right;

    if (x->right != NULL)
        x->right->parent = y;
    x->parent = y->parent;

    if (y->parent == NULL)
        root = x;
    else if (y == y->parent->right)
        x->parent->right = x;
    else 
        y->parent->left = x;
    x->right = y;
    y->parent = x;

    return root;

}

struct node*  BSTRotateLeft(struct node *root, unsigned int key) {
    NODE *x = BSTFind(root,key);
    NODE *y = NULL;

    if (x->right == NULL)
        return NULL;

    y = x->right;
    x->right = y->left;

    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;

    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else 
        x->parent->right = y;
    y->left = x;
    x->parent = y;

    return root;
}

struct node* BSTRotate(struct node *root, unsigned int key, unsigned l_or_r) {
    if (l_or_r == 1)
        return BSTRotateLeft(root,key);
    else
        return BSTRotateRight(root,key);
}

void freeInorder(struct node *root) {
    if (root == NULL)
        return;
    freeInorder(root->left);
    freeInorder(root->right);
    free(root);
}


int main() {

    NODE *root = NULL;
    unsigned int command, key, l_or_r;
    
    while (scanf("%ud",&command)) {


        if (command == 6) {
            freeInorder(root);
            break;
        }
                
        else if (command == 1) {

            scanf("%ud",&key);

            root = BSTInsert(root, key);


        }

        else if (command == 2) {
            
            scanf("%ud",&key);

            root = BSTDelete(root, key);


        }

        else if (command == 3) {

            scanf("%ud",&key);

            if (BSTFind(root,key) == NULL) {
                puts("notfound");
                continue;
            }

            else {
                int par = BSTParent(root,key);

                if (par == 0) {
                    puts("noparent");
                    continue;
                }
                else
                    printf("%d\n",par);
            }
        }

        else if (command == 4) {

            scanf("%ud",&key);

            if (BSTFind(root,key) == NULL) {
                puts("notfound");
                continue;
            }

            else {
                NODE *suc = BSTSuc(root,key);

                if (suc == NULL){
                    puts("nosuccessor");
                    continue;
                }
                else
                    printf("%d\n",suc->key);
            }
        }

         else if (command == 5) {

            scanf("%ud",&key);
            scanf("%ud", &l_or_r);

            if (BSTFind(root,key) == NULL) {
                puts("notfound");
                continue;
            }

            else {
                NODE *tmp = BSTRotate(root, key, l_or_r);

                if (tmp == NULL) {
                    puts("norotate");
                    continue;
                }
                else
                    root = tmp;
            }
        }       
    }
}
