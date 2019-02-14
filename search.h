/* Project: A* Search for 8 Puzzle
/* File: astar.h
/* by:             _  __  
             )\/) / ` ) ) 
            (  ( (_. /_/            */

#ifndef _SEARCH_H_
#define _SEARCH_H_

#include "8puzzle.h"
#include "heap.h"
#include "hash.h"

//Functions Prototypes ----------------------
//Problem Solving Functions -----------------
bool State_Already_Opened(State, Hash_Table, Heap *);
bool State_Already_Closed(State, Hash_Table);
bool State_In_Heap(State, Heap *, int);
bool Is_Solution(State);
State *Solution(State *);
void Free_Solution(State **);

//Search Functions --------------------------
State *A_Star(State , State);

//Printing Functions ------------------------
void Print_Solution(State *);

//-------------------------------------------

#endif