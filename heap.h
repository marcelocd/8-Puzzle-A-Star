/* UFG - Instituto de Informática      *
 * Inteligência Artificial: Trabalho 1 *
 * Aluno: Marcelo Cardoso Dias         *
 * Matrícula: 201305842                */

#ifndef _HEAP_H_
#define _HEAP_H_

#include <stdio.h>
#include <stdlib.h>
#include "8puzzle.h"
#include "list.h"

//Problem Models ----------------------------
typedef struct{
	Node **node_adress;
	int last;
	bool is_empty;
	bool is_full;
	int length;
}Heap;

//-------------------------------------------

//Functions Prototypes ----------------------
//Initializing Functions --------------------
void Init_Heap(Heap *, int);

//Problem Solving Functions -----------------
void Adjust_Going_Up(Heap *, int);
void Insert(Heap *, Node *);
Node *Remove(Heap *);
int Heap_Size(Heap);
void Delete_Heap(Heap *);

//Printing Functions ------------------------
int Print_Heap(Heap);

//-------------------------------------------

#endif