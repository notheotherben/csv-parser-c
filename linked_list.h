#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#define LL_NULL 0

typedef struct LinkedListNode
{
    const void *value;
    struct LinkedListNode *next;
} LinkedListNode;

typedef struct
{
    LinkedListNode *head;
} LinkedList;

LinkedList *ll_new();
void ll_append(LinkedList *list, const void *value);
LinkedListNode *ll_get_tail(LinkedList *list);

void ll_print(LinkedList *list, const char *format);

#endif