/*-----------------------------------------------------------------*/
/*
 Licence Informatique - Structures de données
 Mathias Paulin (Mathias.Paulin@irit.fr)
 
 Implantation du TAD List vu en cours.
 */
/*-----------------------------------------------------------------*/
#include <stdlib.h>
#include <assert.h>
#include "list.h"

#define SIZE l->sentinel->value

typedef struct s_LinkedElement {
    int value;
    struct s_LinkedElement *previous;
    struct s_LinkedElement *next;
} LinkedElement;

typedef struct s_SubList {
    struct s_LinkedElement *head;
    struct s_LinkedElement *tail;
} SubList;

/* Use of a sentinel for implementing the list :
 The sentinel is a LinkedElement* whose next pointer refer always to the head of the list and previous pointer to the tail of the list
 */
struct s_List {
    LinkedElement *sentinel;
};

/*-----------------------------------------------------------------*/

List *list_create(void) {
    LinkedElement *sentinelle = malloc(sizeof(LinkedElement));
    List *l = malloc(sizeof(List));
    l->sentinel = sentinelle;
    //value of sentinel is the size of the list
    SIZE = 0;
    l->sentinel->next = l->sentinel->previous = sentinelle;
    return l;
}

/*-----------------------------------------------------------------*/

List *list_push_back(List *l, int v) {
    struct s_LinkedElement *e = malloc(sizeof(LinkedElement));
    e->value = v;
    e->next = l->sentinel;
    e->previous = e->next->previous;
    e->previous->next = e;
    e->next->previous = e;
    (SIZE)++;
    return l;
}

/*-----------------------------------------------------------------*/

void list_delete(ptrList *l) {
    for (int i = 0; i < ((*l)->sentinel->value); i++) {
        (*l)->sentinel->next = (*l)->sentinel->next->next;
        free((*l)->sentinel->next->previous);
        (*l)->sentinel->next->previous = (*l)->sentinel;
    }
    free((*l)->sentinel);
    free(*l);
    *l=NULL;
}

/*-----------------------------------------------------------------*/

List *list_push_front(List *l, int v) {
    LinkedElement *e = malloc(sizeof(LinkedElement));
    e->value = v;
    e->previous = l->sentinel;
    e->next = e->previous->next;
    e->next->previous = e;
    e->previous->next = e;
    (SIZE)++;
    return l;
}

/*-----------------------------------------------------------------*/

int list_front(const List *l) {
    return l->sentinel->next->value;
}

/*-----------------------------------------------------------------*/

int list_back(const List *l) {
    return l->sentinel->previous->value;
}

/*-----------------------------------------------------------------*/

List *list_pop_front(List *l) {
    l->sentinel->next = l->sentinel->next->next;
    free(l->sentinel->next->previous);
    l->sentinel->next->previous = l->sentinel;
    (l->sentinel->value)--;
    return l;
}

/*-----------------------------------------------------------------*/

List *list_pop_back(List *l) {
    l->sentinel->previous = l->sentinel->previous->previous;
    free(l->sentinel->previous->next);
    l->sentinel->previous->next = l->sentinel;
    (l->sentinel->value)--;
    return l;
}

/*-----------------------------------------------------------------*/

List *list_insert_at(List *l, int p, int v) {
    assert((0 <= p) && (p <= SIZE));
    LinkedElement *insert;
    if (p<=SIZE/2) {
        insert = l->sentinel->next;
        while (p--) insert = insert->next;
    } else {
        insert = l->sentinel;
        int a = SIZE-p;
        while (a--) insert=insert->previous;
    }
    LinkedElement *e = malloc(sizeof(LinkedElement));
    e->value = v;
    e->next = insert;
    e->previous = insert->previous;
    e->previous->next = e;
    e->next->previous = e;
    ++SIZE;
    return l;
}

/*-----------------------------------------------------------------*/

List *list_remove_at(List *l, int p) {
    assert((0 <= p) && (p < SIZE));
    LinkedElement *remove;
    if(p<=SIZE/2) {
        remove = l->sentinel->next;
        while (p--) remove = remove->next;
    } else {
        remove = l->sentinel->previous;
        int a = SIZE-p-1;
        while (a--) remove = remove->previous;
    }
    remove->previous->next = remove->next;
    remove->next->previous = remove->previous;
    free(remove);
    --SIZE;
    return l;
}

/*-----------------------------------------------------------------*/

int list_at(const List *l, int p) {
    assert(!list_is_empty(l) && (0 <= p) && p < SIZE);
    LinkedElement *e;
    if(p<SIZE/2) {
        e = l->sentinel->next;
        while (p--) e = e->next;
    } else {
        e = l->sentinel->previous;
        int a = SIZE-p-1;
        while (a--) e = e->previous;
    }
    return e->value;
}

/*-----------------------------------------------------------------*/

bool list_is_empty(const List *l) {
    return (!(SIZE));
}

/*-----------------------------------------------------------------*/

int list_size(const List *l) {
    return SIZE;
}

/*-----------------------------------------------------------------*/

List *list_map(List *l, SimpleFunctor f) {
    for (LinkedElement *e = l->sentinel->next; e != l->sentinel; e = e->next) {
        e->value = f(e->value);
    }
    return l;
}

/*-----------------------------------------------------------------*/

List *list_reduce(List *l, ReduceFunctor f, void *userData) {
    for (LinkedElement *e = l->sentinel->next; e != l->sentinel; e = e->next) f(e->value, userData);
    return l;
}

/*-----------------------------------------------------------------*/

SubList *list_split(SubList *l){
    SubList *subList = malloc(sizeof(SubList));
    subList->head = l->head, subList->tail =l->tail;
    while(subList->head->next!=subList->tail) {
        subList->head = subList->head->next;
        if (subList->head->next != subList->tail) subList->tail = subList->tail->previous;
    }
    return subList;
}

/*-----------------------------------------------------------------*/

SubList *list_merge(SubList *leftlist, SubList *rightlist, OrderFunctor f){
    SubList *sublist = malloc(sizeof(SubList)); //Creation de la liste triée qui sera retournée
    sublist->head=NULL, sublist->tail=NULL;
    while(leftlist->head!=NULL || rightlist->head!=NULL) {
        if(leftlist->head==NULL) {
            sublist->tail->next=rightlist->head;
            sublist->tail->next->previous = sublist->tail;
            sublist->tail=rightlist->tail;
            sublist->tail->next=NULL;
            rightlist->head=NULL,rightlist->tail=NULL;
        } else if(rightlist->head==NULL) {
            sublist->tail->next=leftlist->head;
            sublist->tail->next->previous = sublist->tail;
            sublist->tail=leftlist->tail;
            leftlist->head=NULL,leftlist->tail=NULL;
        } else if(f(leftlist->head->value,rightlist->head->value)) {
            if(sublist->head==NULL){
                sublist->head=leftlist->head;
                sublist->tail=leftlist->head;
                sublist->head->previous = NULL;
            } else {
                sublist->tail->next=leftlist->head;
                sublist->tail->next->previous = sublist->tail;
                sublist->tail=sublist->tail->next;
            }
            leftlist->head = leftlist->head->next;
        } else {
            if(sublist->head==NULL){
                sublist->head=rightlist->head;
                sublist->tail=rightlist->head;
                sublist->head->previous = NULL;
            } else {
                sublist->tail->next=rightlist->head;
                sublist->tail->next->previous = sublist->tail;
                sublist->tail=sublist->tail->next;
            }
            rightlist->head = rightlist->head->next;
        }
    }
    free(leftlist);
    free(rightlist);
    return sublist;
}

/*-----------------------------------------------------------------*/

SubList *list_mergesort(SubList *l, OrderFunctor f){
    if(l->head!=l->tail) {
        SubList *left = malloc(sizeof(SubList));
        SubList *right = malloc(sizeof(SubList));
        SubList *splited = list_split(l);
        left->head = l->head;
        left->tail = splited->head;
        right->head = splited->tail;
        free(splited);
        right->tail = l->tail;
        left->tail->next=NULL;
        right->head->previous=NULL;
        right = list_mergesort(right, f);
        left = list_mergesort(left, f);
        SubList *mergedlist = list_merge(left,right,f);
        mergedlist->head->previous=NULL;
        mergedlist->tail->next=NULL;
        free(l);
        return mergedlist;
    }
    return l;
}

/*-----------------------------------------------------------------*/

List *list_sort(List *l, OrderFunctor f){
    if(list_size(l)==1) return l;
    else {
        SubList *subList = malloc(sizeof(SubList)), *sorted;
        subList->head = l->sentinel->next;
        subList->tail = l->sentinel->previous;
        subList->head->previous = NULL;
        subList->tail->next = NULL;
        sorted = list_mergesort(subList, f);
        l->sentinel->next = sorted->head;
        l->sentinel->previous = sorted->tail;
        l->sentinel->next->previous = l->sentinel;
        l->sentinel->previous->next = l->sentinel;
        free(sorted);
        return l;
    }
}

/*-----------------------------------------------------------------*/