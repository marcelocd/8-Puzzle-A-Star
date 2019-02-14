/* UFG - Instituto de Informática      *
 * Inteligência Artificial: Trabalho 1 *
 * Aluno: Marcelo Cardoso Dias         *
 * Matrícula: 201305842                */

#ifndef _HASH_H_
#define _HASH_H_

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define   A            400135675
#define   B            551284587
#define   C            334466698
#define   D            199874534
#define   E            111457792
#define   F            766521303
#define   G            988745444
#define   H            133467095
#define   I            677721349
#define   J            26666912345
#define   PRIME        32920473601
#define   MAX_STATES   181440

//Problem Models ----------------------------
typedef   List *  Hash_Table;

//-------------------------------------------

//Functions Prototypes ----------------------
//Initializing Functions --------------------
void Init_Hash_Table(Hash_Table *, int);

//Problem Solving Functions -----------------
int Hash(short *);
int Hash_Table_Size(Hash_Table, int);
void Delete_Hash_Table(Hash_Table *, int);

//Printing Functions ------------------------
void Print_Hash_Table(Hash_Table);

//-------------------------------------------

#endif