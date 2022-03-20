#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List *list = (List*) calloc(1, sizeof(List));
  list->head=NULL;
  list->current=NULL;
  list->tail=NULL;
     return list;
}

void * firstList(List * list) {
  if(list->head && list->head->data){
    list->current=list->head;
    return list->head->data;
  }
    return NULL;
}

void * nextList(List * list) {
  if(list->current && list->current->next){
    list->current =list->current->next;
    return list->current->data;
  }
    return NULL;
}

void * lastList(List * list) {
  if(list->tail && list->tail->data){
    list->current = list->tail;
    return list->tail->data;
  }
    return NULL;
}

void * prevList(List * list) {
  if(list->current && list->current->prev){
    list->current = list->current->prev;
    return list->current->data;
    
  }
    return NULL;
}

void pushFront(List * list, void * data) {
  Node *node = createNode(data);
  node->next = list->head;
  if(list->head){
    list->head->prev=node;
  }
  else
    list->tail=node;
  list->head=node;
  node->prev=NULL;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  Node *node = createNode(data);
  if(list->current->next != NULL){ 
    list->current->next->prev=node;
    list->current->next=node;
    node->prev=list->current;
    node->next=list->current;
  
    
  }else{ 
    list->current->next=node;
    node->prev=list->current;
    list->tail=node;
  }
}

void * popFront(List * list) {
  
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  
  Node *node = list->current->data;

  if(list->current == list->head){
    list->head=list->current->next;
    list->current->next->prev=NULL;
    list->current=list->current->next;
  }
  if(list->current == list->tail){
    list->tail=list->current->prev;
    list->current->next->prev=NULL;
    list->current=list->tail;
  }
  if(list->current != list->head && list->current != list->tail){
    list->current->prev->next=list->current->next;
    list->current->prev=list->current->next->prev;
    list->current=list->current->next;
  }
  else{
    list->current=list->head;
    list->current=list->tail;
  }
  free(list->current);
  return node;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}