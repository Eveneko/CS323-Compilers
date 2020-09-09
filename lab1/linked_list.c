#include "linked_list.h"

node *linked_list_init(){
    node *head = (node*)malloc(sizeof(node));
    head->count = 0;
    head->next = NULL;
    return head;
}

void linked_list_free(node *head){
    node *cur = head;
    node *last;
    while(cur != NULL){
        last = cur;
        cur = cur->next;
        free(last);
    }
}

char linked_list_string[0x10000];

char *linked_list_tostring(node *head){
    node *cur = head->next;
    char *position;
    int length = 0;
    while(cur != NULL){
        position = linked_list_string + length;
        length += sprintf(position, "%d", cur->value);
        cur = cur->next;
        if(cur != NULL){
            position = linked_list_string + length;
            length += sprintf(position, "->");
        }
    }
    position = linked_list_string + length;
    length += sprintf(position, "%c", '\0');
    return linked_list_string;
}

int linked_list_size(node *head){
    return head->count;
}

void linked_list_append(node *head, int val){
    node *cur = head;
    node *new_node;
    while(cur->next != NULL){
        cur = cur->next;
    }
    new_node = (node*)malloc(sizeof(node));
    new_node->value = val;
    new_node->next = NULL;
    cur->next = new_node;
    head->count++;
}

/* your implementation goes here */

/* insert val at position index */
void linked_list_insert(node *head, int val, int index){
    node *cur = head;
    node *new_node;
    if(head->count < index){
        return;
    }
    while(index--){
        cur = cur->next;
    }
    new_node = (node*)malloc(sizeof(node));
    new_node->value = val;
    new_node->next = cur->next;
    cur->next = new_node;
    head->count++;
}

/* delete node at position index */
void linked_list_delete(node *head, int index){
    node *cur = head;
    if(index < 0 || index >= head->count){
        return;
    }
    while(index--){
        cur = cur->next;
    }
    node * del = cur->next;
    free(del);
    cur->next = del->next;
    head->count--;
}

/* remove the first occurence node of val */
void linked_list_remove(node *head, int val){
    node *cur = head;
    node *del;
    int cnt = 0;
    while(cur->next != NULL){
        del = cur->next;
        if(del->value == val){
            linked_list_delete(head, cnt);
            break;
        }
        cnt++;
        cur = cur->next;
    }
}

/* remove all occurences of val */
void linked_list_remove_all(node *head, int val){
    node *cur = head;
    node *del;
    int cnt = 0;
    while(cur->next != NULL){
        del = cur->next;
        if(del->value == val){
            linked_list_delete(head, cnt);
        }else{
            cnt++;
            cur = cur->next;
        }
    }
}

/* get value at position index */
int linked_list_get(node *head, int index){
    node *cur = head->next;
    if(index < 0 || index >= head->count){
        return -0x80000000;
    }
    while(index--){
        cur = cur->next;
    }
    return cur->value;
}

/* search the first index of val */
int linked_list_search(node *head, int val){
    node *cur = head;
    int cnt = 0;
    while(cur->next != NULL){
        cur = cur->next;
        if(cur->value == val){
            return cnt;
        }else{
            cnt++;
        }
    }
    return -1;
}

/* search all indexes of val */
node *linked_list_search_all(node *head, int val){
    node *cur = head;
    node *new_head = linked_list_init();
    int cnt = 0;
    while(cur->next != NULL){
        cur = cur->next;
        if(cur->value == val){
            linked_list_append(new_head, cnt);
        }
        cnt++;
    }
    return new_head;
}
