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
            free(node);
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
        symtab_lookup(p->right, key);
    }else{
        if(p->left == NULL){
            return -1;
        }
        symtab_lookup(p->left, key);
    }
}

int symtab_remove(symtab *self, char *key){
    symtab *p = self;
    symtab *pre = NULL;

    // 查找目标节点的位置
    while(1){
        if(strcmp(key, p->entry.key) > 0 && p->right != NULL){
            pre = p;
            p = p->right;
        }else if(strcmp(key, p->entry.key) < 0 && p->left != NULL){
            pre = p;
            p = p->left;
        }else if(strcmp(key, p->entry.key) !=0 && p->right == NULL && p->left == NULL){
            return 0;   
        }else{
            break;
        }
    }
    // 目标节点没有子节点
    if(p->right == NULL && p->left == NULL){
        if(p == pre->right){
            pre->right = NULL;
        }else if(p == pre->left){
            pre->left = NULL;
        }
        free(p);
    }
    // 目标节点有左右子节点，按照中序删除
    if(p->right != NULL && p->left != NULL){
        symtab *del_p = p;
        p = p->right;
        if(p->right == NULL){
            del_p->entry = p->entry;
            if(p->right == NULL){
                del_p->right = NULL;
            }else{
                del_p->right = p->right;
            }
            free(p);
        }
        while(p->left != NULL){
            pre = p;
            p = p->left;
        }
        if(p->right == NULL){
            pre->left = NULL;
        }else{
            pre->left = p->right;
        }
        del_p->entry = p->entry;
        free(p);
    }
    // 目标节点只有右节点
    if(p->right != NULL){
        if(pre != NULL){
            if(p == pre->left){
                pre->left = p->right;
            }else if(p == pre->right){
                pre->right = p->right;
            }
            free(p);
        }else{
            self = p->right;
            free(p);
        }
    }
    // 目标节点只有左子节点
    if(p->left != NULL){
        if(pre != NULL){
            if(p == pre->left){
                pre->left = p->left;
            }else if(p == pre->right){
                pre->right = p->left;
            }
            free(p);
        }else{
            self = p->left;
            free(p);
        }
    }
    return 1;
}
