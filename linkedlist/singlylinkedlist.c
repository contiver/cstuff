#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include "../util.h"
#include "singlylinkedlist.h"

/* From 'The Practice of Programming'
 *
 * Rather than defining an explicit List type, the usual way lists are used in
 * C is to start with a type for the elements, and add a pointer that links to
 * the next element.
 */

struct Node{
    dataT data;
    Node *next;
};

struct List{
    Node* first;
    Node* last;
    long size;
};

Node*
newnode(dataT data) {
    Node* np = xmalloc(sizeof(*np));

    np->data = data;
    np->next = NULL;
    return np;
}

List*
newlist(void) {
    List* list  = xmalloc(sizeof(*list));

    list->first = list->last = NULL;
    list->size  = 0;
    return list;
}

void
freelist(List* list) {
    Node* np;

    if(list->first != NULL){
        Node* next;

        for(np = list->first; np != NULL; np = next){
            next = np->next;
            free(np);
        }
    }
    free(list);
}

/* O(1) */
void
insert(List* list, dataT data) {
    Node* np = newnode(data);

    if(list->first == NULL){
        list->first = list->last = np;
        list->size = 1;
        return;
    }

    list->last->next = np;
    list->last = np;
    list->size++;
}

/* O(1) */
void
insertfirst(List* list, dataT data){
    Node* np = newnode(data);

    if(list->first == NULL){
        list->first = list->last = np;
        list->size = 1;
        return;
    }

    np->next = list->first;
    list->first = np;
    list->size++;
}

/*
 * Depending on the data type, an equality function might be needed.
 * Worst case: O(n)
 */
bool
delete(List* list, dataT data){
    Node* np;
    Node* prev;

    if(list == NULL)
        return false;

    prev = list->first;
    if(data == list->first->data){
        list->first = list->first->next;
        list->size--;
        free(prev);
        return true;
    }

    for(np = list->first->next; np != NULL; np = np->next){
        if(data == np->data){
            prev->next = np->next;
            list->size--;
            free(np);
            return true;
        }
        prev = np;
    }
    return false;
}

/*
 * Complexity: O(1)
 */
bool
deletefirst(List* list){
    Node* np;

    if(list->first == NULL)
        return false;

    np = list->first;
    list->first = list->first->next;
    free(np);
}

/*
dataT
get(List* list, long index){
    Node* np;
    long i;

    if(list->size < index)
        return NULL;

    for(i = 0; i < index; i++)
        np = np->next;

    return np->data;
}
*/
