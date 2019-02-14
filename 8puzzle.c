/* Project: A* Search for 8 Puzzle
/* File: 8puzzle.c
/* by:             _  __  
             )\/) / ` ) ) 
            (  ( (_. /_/            */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "8puzzle.h"
#include "vector.h"
#include "hash.h"

//Functions Implementations -----------------
//Initializing Functions --------------------
State *New_State(short *set, int k0, int g, State *parent){
	State *new_state = (State *) malloc(sizeof(State));

	if(new_state != NULL){
		new_state->key = Hash(set);
		new_state->set = New_Vector(SIZE);
		Transfer_Vector(set, new_state->set, SIZE);
		new_state->k0 = k0;
		new_state->g = g;
		new_state->parent = parent;
	}

	return new_state;
}

void Initial_State1(State *s1){
	s1->set = New_Vector(SIZE);

	s1->set[0] = 3;
	s1->set[1] = 4;
	s1->set[2] = 2;
	s1->set[3] = 5;
	s1->set[4] = 1;
	s1->set[5] = 7;
	s1->set[6] = 6;
	s1->set[7] = 0;
	s1->set[8] = 8;

	s1->key = Hash(s1->set);
	s1->k0 = 7;
	s1->g = 0;
	s1->parent = NULL;
}

void Initial_State2(State *s2){
	s2->set = New_Vector(SIZE);

	s2->set[0] = 2;
	s2->set[1] = 8;
	s2->set[2] = 3;
	s2->set[3] = 1;
	s2->set[4] = 6;
	s2->set[5] = 4;
	s2->set[6] = 7;
	s2->set[7] = 0;
	s2->set[8] = 5;

	s2->key = Hash(s2->set);
	s2->k0 = 7;
	s2->g = 0;
	s2->parent = NULL;
}

void Initial_State3(State *s3){
	s3->set = New_Vector(SIZE);

	s3->set[0] = 6;
	s3->set[1] = 2;
	s3->set[2] = 7;
	s3->set[3] = 5;
	s3->set[4] = 0;
	s3->set[5] = 3;
	s3->set[6] = 8;
	s3->set[7] = 1;
	s3->set[8] = 4;

	s3->key = Hash(s3->set);
	s3->k0 = 4;
	s3->g = 0;
	s3->parent = NULL;
}

void Goal_State1(State *gs1){
	gs1->set = New_Vector(SIZE);

	gs1->set[0] = 1;
	gs1->set[1] = 2;
	gs1->set[2] = 3;
	gs1->set[3] = 8;
	gs1->set[4] = 0;
	gs1->set[5] = 4;
	gs1->set[6] = 7;
	gs1->set[7] = 6;
	gs1->set[8] = 5;

	gs1->key = Hash(gs1->set);
	gs1->k0 = 4;
	gs1->g = -1;
	gs1->parent = NULL;
}

void Goal_State2(State *gs2){
	gs2->set = New_Vector(SIZE);

	gs2->set[0] = 1;
	gs2->set[1] = 2;
	gs2->set[2] = 3;
	gs2->set[3] = 4;
	gs2->set[4] = 5;
	gs2->set[5] = 6;
	gs2->set[6] = 7;
	gs2->set[7] = 8;
	gs2->set[8] = 0;

	gs2->key = Hash(gs2->set);
	gs2->k0 = 8;
	gs2->g = -1;
	gs2->parent = NULL;
}

void Goal_State3(State *gs3){
	gs3->set = New_Vector(SIZE);

	gs3->set[0] = 0;
	gs3->set[1] = 1;
	gs3->set[2] = 2;
	gs3->set[3] = 3;
	gs3->set[4] = 4;
	gs3->set[5] = 5;
	gs3->set[6] = 6;
	gs3->set[7] = 7;
	gs3->set[8] = 8;

	gs3->key = Hash(gs3->set);
	gs3->k0 = 0;
	gs3->g = -1;
	gs3->parent = NULL;
}

//Problem Solving Functions -----------------
void Free_State(State *s){
	free(s->set);
	free(s);
}

//Rules Functions ---------------------------
void Move_Up(State *s){
	s->set[s->k0] = s->set[s->k0 - N];
	s->set[s->k0 - N] = 0;
	s->k0 = s->k0 - N;
	s->g++;
	s->key = Hash(s->set);
}

void Move_Down(State *s){
	s->set[s->k0] = s->set[s->k0 + N];
	s->set[s->k0 + N] = 0;
	s->k0 = s->k0 + N;
	s->g++;
	s->key = Hash(s->set);
}

void Move_Right(State *s){
	s->set[s->k0] = s->set[s->k0 + 1] ;
	s->set[s->k0 + 1] = 0;
	s->k0 = s->k0 + 1;
	s->g++;
	s->key = Hash(s->set);
}

void Move_Left(State *s){
	s->set[s->k0] = s->set[s->k0 - 1];
	s->set[s->k0 - 1] = 0;
	s->k0 = s->k0 - 1;
	s->g++;
	s->key = Hash(s->set);
}

//-------------------------------------------