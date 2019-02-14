/* Project: A* Search for 8 Puzzle
/* File: heap.c
/* by:             _  __  
             )\/) / ` ) ) 
            (  ( (_. /_/            */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "heap.h"
#include "vector.h"

int Print_Heap();

//Functions Implementations -----------------
//Initializing Functions --------------------
void Init_Heap(Heap *h, int length){
	h->node_adress = (Node **) malloc(sizeof(Node *) * length);
	h->last = -1;
	h->length = length;
}

//Problem Solving Functions -----------------
void Adjust_Going_Up(Heap *h, int index){
	Node  *aux;

	int parent = (index + 1) / 2 - 1;

	while(index > 0){
		if((h->node_adress[index])->state.f >= h->node_adress[parent]->state.f)
			break;

		aux = h->node_adress[parent];
		h->node_adress[parent] = h->node_adress[index];
		h->node_adress[index] = aux;

		index = parent;
		parent = (index + 1) / 2 - 1;
	}
}

void Adjust_From_Root(Heap *h){
	if(h->last < 1)
		return;

	Node *aux = NULL;

	int current = 0;
	int left = 1;
	int right = 2;
	int flag = 1;
	int smallest;

	do{
		smallest = current;

		if(h->node_adress[left]->state.f >= h->node_adress[current]->state.f){
			if(right <= h->last){
				if(h->node_adress[right]->state.f >= h->node_adress[current]->state.f)
					flag = 0;

				else{
					if(h->node_adress[left]->state.f <= h->node_adress[right]->state.f)
						smallest = left;

					else
						smallest = right;
				}
			}

			else
				flag = 0;
		}

		else
			smallest = left;

		if(flag != 0){
			aux = h->node_adress[current];
	 		h->node_adress[current] = h->node_adress[smallest];
	 		h->node_adress[smallest] = aux;

	 		current = smallest;
	 		left = 2 * current + 1;
		 	right = 2 * current + 2;
		}

	}while(flag != 0 && left <= h->last);
}

void Insert(Heap *h, Node *node){
	if(h == NULL)
		return;

	if(h->last == h->length - 1)
		return;

	h->last++;
	h->node_adress[h->last] = node;

	Adjust_Going_Up(h, h->last);
}

Node *Remove(Heap *h){
	if(h == NULL)
		return NULL;

	if(h->last < 0)
		return NULL;

	Node *bye = h->node_adress[0];

	if(h->last > 0){
		h->node_adress[0] = h->node_adress[h->last];
		h->node_adress[h->last] = NULL;
		h->last--;

		Adjust_From_Root(h);
	}

	else{
		h->node_adress[h->last] = NULL;
		h->last--;
	}

	return bye;
}

int Heap_Size(Heap h){
	return h.last + 1;
}

void Delete_Heap(Heap *h){
	if(h == NULL)
		return;

	int count;

	for(count = 0 ; count < h->length ; count++)
		free(h->node_adress[count]->state.set);

	free(h->node_adress);
	h->last = h->length = 0;

	free(h);
}

//Printing Functions ------------------------
int Print_Heap(Heap h){
	int index;

	printf("Heap\n");
	printf("---------------------\n");

	for(index = 0 ; index <= h.last ; index++){
		printf("f: %d\n", h.node_adress[index]->state.f);
		Print_Matrix(h.node_adress[index]->state.set, M, N);
	}

	printf("---------------------\n");

	return 0;
}

//-------------------------------------------