#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

LinkedList *ll_new()
{
    LinkedList *ll = malloc(sizeof(LinkedList));
    ll->head = LL_NULL;
    return ll;
}

void ll_append(LinkedList *list, const void *value)
{
    LinkedListNode *node = malloc(sizeof(LinkedListNode));
    node->value = value;
    node->next = LL_NULL;

    LinkedListNode *tail = ll_get_tail(list);
    if (LL_NULL == tail)
        list->head = node;
    else
        tail->next = node;
}

LinkedListNode *ll_get_tail(LinkedList *list)
{
    LinkedListNode *cursor = list->head;
    if (LL_NULL == cursor)
        return LL_NULL;
    while (cursor->next != LL_NULL)
    {
        cursor = cursor->next;
    }

    return cursor;
}

void ll_print(LinkedList *list, const char *format)
{
    LinkedListNode *cursor = list->head;
    while (cursor != LL_NULL)
    {
        printf(format, cursor->value);
        cursor = cursor->next;
    }
}