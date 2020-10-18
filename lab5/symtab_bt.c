#include "symtab.h"

/*
 * symbol table type, binary tree impl
 */
struct symtab {
    entry entry;
    struct symtab *left, *right;
};

// ************************************************************
//    Your implementation goes here
// ************************************************************

symtab *symtab_init(){
    symtab *self = malloc(sizeof(symtab));
    memset(self, '\0', sizeof(symtab));
    self->left = NULL;
    self->right = NULL;
    return self;
}

int symtab_insert(symtab *self, char *key, VAL_T value){
    symtab *p = self;
    // new node
    symtab *node = malloc(sizeof(symtab));
    memset(node, '\0', sizeof(symtab));
    entry_init(&node->entry, key, value);
    node->left = NULL;
    node->right = NULL;

    while(1){
        if(strcmp(key, p->entry.key) > 0){
            if(p->right == NULL){
                p->right = node;
                return 1;
            }
            p = p->right;
        }else if(strcmp(key, p->entry.key) < 0){
            if(p->left == NULL){
                p->left = node;
                return 1;
            }
            p = p->left;
        }else{
            // free(node);
            return 0;
        }
    }
}

VAL_T symtab_lookup(symtab *self, char *key){
    symtab *p = self;
    if(strcmp(key, p->entry.key) == 0){
        return p->entry.value;
    }else if(strcmp(key, p->entry.key) > 0){
        if(p->right == NULL){
            return -1;
        }
        return symtab_lookup(p->right, key);
    }else{
        if(p->left == NULL){
            return -1;
        }
        return symtab_lookup(p->left, key);
    }
    return -1;
}

int flag = 1;

symtab* _symtab_remove(symtab *self, char *key){
    if(self == NULL){
        flag = 0;
        return NULL;
    }
    if(strcmp(key, self->entry.key) == 0){
        if(self->left == NULL){
            return self->right;
        }else if(self->right == NULL){
            return self->left;
        }else{
            symtab* cur = self->right;
            while(cur->left != NULL){
                cur = cur-> left;
            }
            cur->left = self->left;
            self = self->right;
            return self;
        }
    }
    if(strcmp(key, self->entry.key) > 0){
        self->right = _symtab_remove(self->right, key);
    }else if(strcmp(key, self->entry.key) < 0){
        self->left = _symtab_remove(self->left, key);
    }
    return self;
}

int symtab_remove(symtab *self, char *key){
    flag = 1;
    _symtab_remove(self, key);
    return flag;
}