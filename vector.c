/* UFG - Instituto de Informática      *
 * Inteligência Artificial: Trabalho 1 *
 * Aluno: Marcelo Cardoso Dias         *
 * Matrícula: 201305842                */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

//Functions Implementations -----------------
//Problem Solving Functions -----------------
short *New_Vector(int size){
	short *new_vector;

	if((new_vector = (short *) malloc(sizeof(short ) * size)) == NULL)
		return NULL;

	return new_vector;
}

void Clear_Vector(short *v, int size){
	int k;

	for(k = 0 ; k < size ; k++)
			v[k] = 0;
}

void Transfer_Vector(short *v1, short *v2, int size){
	int k;

	for(k = 0 ; k < size ; k++)
		v2[k] = v1[k];
}

int k2i(int k, int n){
	return k / n;
}

int k2j(int k, int n){
	return k % n;
}

//Printing Functions ------------------------
void Print_Border_Of_Matrix(int n){
	int j;

	printf("+");

	for(j = 1 ; j <= n ; j++)
		printf("--");

	printf("-+\n");
}

void Print_Matrix(short *v, int m, int n){
	int i, j;

	Print_Border_Of_Matrix(n);

	for(i = 0 ; i < m ; i++){
		printf("| ");

		for(j = 0 ; j < n ; j++){
			if(v[i * n + j] == 0)
				printf("  ");

			else
				printf("%hi ", v[i * n + j]);
		}

		printf("|\n");
	}

	Print_Border_Of_Matrix(n);
	printf("\n");
}

//-------------------------------------------