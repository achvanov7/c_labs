#ifndef CLIST_H
#define CLIST_H

typedef struct intrusive_node {
    struct intrusive_node *next;
    struct intrusive_node *prev;
} intrusive_node;

typedef struct intrusive_list {
    struct intrusive_node *head;
} intrusive_list;

void init_list(intrusive_list *list);
void add_node(intrusive_list *list, intrusive_node *node);
void remove_node(intrusive_list *list, intrusive_node *node);

int get_length(intrusive_list *list);

#endif
