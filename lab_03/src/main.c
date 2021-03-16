#include "stdio.h"
#include "stdlib.h"
#include "clist.h"
#include "stddef.h"
#include "string.h"

#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

typedef struct point {
    int x, y;
    struct intrusive_node node;
} point;

void add_point(intrusive_list *list, int x, int y) {
    point *data = (point*) malloc(sizeof(point));
    data->x = x;
    data->y = y;
    add_node(list, &data->node);
}

void remove_point(intrusive_list *list, int x, int y) {       
    intrusive_node *cur = list->head;
    while (cur->next != NULL) {
        point *data = container_of(cur, struct point, node);
        if (data->x == x && data->y == y) {
            intrusive_node *to_remove = cur;
            cur = cur->next;
            remove_node(list, to_remove);
            free(container_of(to_remove, struct point, node));
        } else {
            cur = cur->next;
        }
    }
}

void show_all_points(intrusive_list *list) {
    intrusive_node *cur = list->head;
    while (cur->next != NULL) {
        point *data = container_of(cur, struct point, node);
        printf("(%d %d) ", data->x, data->y);
        cur = cur->next;
    }
    printf("\n");
}

void remove_all_points(intrusive_list *list) {
    intrusive_node *cur = list->head;
    while (cur->next != NULL) {
        intrusive_node *to_remove = cur;
        cur = cur->next;
        remove_node(list, to_remove);
        free(container_of(to_remove, struct point, node));
    }
}

int main() {
    intrusive_list list;
    list.head = (intrusive_node*) malloc(sizeof(intrusive_node));
    init_list(&list);
    char com[10];
    while (1) {
        scanf("%s", com);
        if (strcmp(com,"add") == 0) {
            int x, y;
            scanf("%d%d", &x, &y);
            add_point(&list, x, y);
        } 
        if (strcmp(com, "rm") == 0) {
            int x, y;
            scanf("%d%d", &x, &y);
            remove_point(&list, x, y);
        }
        if (strcmp(com, "print") == 0) {
            show_all_points(&list);
        }
        if (strcmp(com, "rma") == 0) {
            remove_all_points(&list);
        }
        if (strcmp(com, "len") == 0) {
            int len = get_length(&list);
            printf("%d\n", len);
        }
        if (strcmp(com, "exit") == 0) {
            return 0;
        }
    }
    return 0;
}





