/* Project: A* Search for 8 Puzzle
/* File: list.c
/* by:             _  __  
             )\/) / ` ) ) 
            (  ( (_. /_/            */

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "vector.h"

//Functions Implementation ------------------
//Problem Solving Functions -----------------
Node *New_Node(State s){
	Node *new_node = (Node *) malloc(sizeof(Node));

	if(new_node != NULL){
		new_node->state = s;
		new_node->previous = NULL;
		new_node->next = NULL;
	}

	return new_node;
}

void Push(List *list, Node *node){
	if(node == NULL)
		return;

	node->next = NULL;

	if(list->first == NULL)
		list->first = list->last = node;

	else{
		list->last->next = node;
		node->previous = list->last;
		list->last = node;
	}
}

void Pop(List *list, Node *node){
	if(list->first == NULL)
		return;

	if(node != NULL){
		if(node->previous != NULL)
			node->previous->next = node->next;

		if(node->next != NULL)
			node->next->previous = node->previous;

		if(node == list->first)
			list->first = node->next;

		if(node == list->last)
			list->last = node->previous;
	}
}

int List_Size(List list){
	if(list.first == NULL)
		return -1;

	Node *aux;
	int size = 0;

	for(aux = list.first ; aux != NULL ; aux = aux->next)
		size++;

	return size;
}

void Clear_Node(Node *node){
	if(node == NULL)
		return;

	node->state.key = 0;
	Clear_Vector(node->state.set, M);
	node->previous = node->next = NULL;
}


void Delete_List(List *list){
	if(list->first == NULL)
		return;

	Node *bye;

	while(list->first != NULL){
		bye = list->first;
		list->first = list->first->next;

		Clear_Node(bye);
		free(bye);
	}

	list->last = NULL;
}

//Printing Functions ------------------------
int Print_List(List list){
	if(list.first == NULL)
		return -1;

	Node *aux = list.first;
	int index = 0;

	printf("List\n");
	printf("---------------------\n");

	while(aux != NULL){
		printf("f: %d\n", aux->state.f);
		Print_Matrix(aux->state.set, M, N);
		aux = aux->next;
		index++;
	}

	printf("---------------------\n");

	return 0;
}

//-------------------------------------------