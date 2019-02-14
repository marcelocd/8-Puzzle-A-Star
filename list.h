/* Doubly Linked List
/* by:       _  __  
       )\/) / ` ) ) 
      (  ( (_. /_/   */

#ifndef _LIST_H_
#define _LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include "8puzzle.h"

//Problem Models ----------------------------
typedef struct node{
	State state;
	struct node *previous;
	struct node *next;
}Node;

typedef struct{
	Node *first;
	Node *last;
}List;

//-------------------------------------------

//Functions Prototypes ----------------------
//Problem Solving Functions -----------------
Node *New_Node(State);
void Push(List *, Node *);
void Pop(List *, Node *);
int List_Size(List);
void Delete_List(List *);

//Printing Functions ------------------------
int Print_List(List list);

//-------------------------------------------

#endif