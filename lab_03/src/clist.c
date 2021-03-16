#include "clist.h"
#include "stdlib.h"

void init_list(intrusive_list *list) {
      list->head->next = NULL;
      list->head->prev = NULL;
}

void add_node(intrusive_list *list, intrusive_node *node) {
    node->next = list->head;
    list->head->prev = node;
    node->prev = NULL;
    list->head = node;
}

void remove_node(intrusive_list *list, intrusive_node *node) {
    if (node->prev != NULL) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    } else {
        node->next->prev = NULL;
        list->head = node->next;
    }
}

int get_length(intrusive_list *list) {
    intrusive_node *cur = list->head;
    int length = 0;
    while (cur != NULL) {
        length++;
        cur = cur->next;
    }
    return length - 1;
}


