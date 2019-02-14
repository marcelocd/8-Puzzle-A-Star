/* UFG - Instituto de Informática      *
 * Inteligência Artificial: Trabalho 1 *
 * Aluno: Marcelo Cardoso Dias         *
 * Matrícula: 201305842                */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "list.h"

//Functions Implementation ------------------
//Initializing Functions --------------------
void Init_Hash_Table(Hash_Table *h, int length){
	*h = (Hash_Table) malloc(sizeof(List) * length);

	List aux;

	int i;

	for(i = 0 ; i < length ; i ++){
		(*h)[i] = aux;
		(*h)[i].first = (*h)[i].last = NULL;
	}
}

//Problem Solving Functions -----------------
int Hash(short *set){
	unsigned long long int key = 0;

	key += ((unsigned long long int)(set[0])) * A;
	key += ((unsigned long long int)(set[1])) * B;
	key += ((unsigned long long int)(set[2])) * C;
	key += ((unsigned long long int)(set[3])) * D;
	key += ((unsigned long long int)(set[4])) * E;
	key += ((unsigned long long int)(set[5])) * F;
	key += ((unsigned long long int)(set[6])) * G;
	key += ((unsigned long long int)(set[7])) * H;
	key += ((unsigned long long int)(set[8])) * I;

	return ((int)(((key + J) % PRIME) % MAX_STATES));
}

int Hash_Table_Size(Hash_Table h, int length){
	int i;
	int size = 0;

	for(i = 0 ; i < length ; i++)
		if(h[i].first != NULL)
			size += List_Size(h[i]);

	return size;
}

void Delete_Hash_Table(Hash_Table *h, int length){
	int i;

	for(i = 0 ; i < length ; i++)
		if((*h)[i].first != NULL)
			Delete_List(&((*h)[i]));

	free(*h);
	*h = NULL;
}

//Printing Functions ------------------------
void Print_Hash_Table(Hash_Table h){
	int i;

	for(i = 0 ; i < MAX_STATES ; i++)
		if(h[i].first != NULL)
			Print_List(h[i]);
}

//-------------------------------------------