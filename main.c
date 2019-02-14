/* Project: A* Search for 8 Puzzle
/* File: main.c
/* by:             _  __  
             )\/) / ` ) ) 
            (  ( (_. /_/            */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <windows.h>
#include "search.h"
#include "8puzzle.h"
#include "list.h"
#include "hash.h"
#include "vector.h"

#define   EXIT   7
#define   DELAY  500

#include <time.h>
void Sleep(unsigned long delay)
{
    usleep(delay*1000);
}

//Functions Prototypes ----------------------
//Initializing Functions --------------------
void Init_Initial_States(State **);
void Init_Goal_States(State **);

//Menu Functions ----------------------------
int Menu();
int Option1(State *);           /* PICK INITIAL STATE */
int Option2(State *);           /* ENTER INITIAL STATE */
int Option3(State *);           /* PICK GOAL STATE */
int Option4(State *);           /* ENTER GOAL STATE */
State *Option5(State, State);   /* A* */
void Option6(State *);          /* SHOW MOVES */

//Printing Functions ------------------------
void Print_Menu();
void Show_Moves(State *);

//Exception Functions -----------------------
void Exception_Message(char *);

//Control Functions -------------------------
void Control();

//-------------------------------------------

//Test --------------------------------------
int main(int argc, char *argv[]){
	
	Control();

	return 0;
}

//-------------------------------------------

//Functions Implementations -----------------
//Initializing Functions --------------------
void Init_Initial_States(State **initial_state){
	*initial_state = (State *) malloc(sizeof(State) * 100);

	State aux;
	aux.key = -1;
	aux.parent = NULL;

	int index;

	for(index = 0 ; index < 100 ; index++){
		(*initial_state)[index] = aux;
		(*initial_state)[index].set = New_Vector(SIZE);
	}

	Initial_State1(&((*initial_state)[0]));
	Initial_State2(&((*initial_state)[1]));
	Initial_State3(&((*initial_state)[2]));
}

void Init_Goal_States(State **goal_state){
	*goal_state = (State *) malloc(sizeof(State) * 100);

	State aux;
	aux.key = -1;
	aux.parent = NULL;

	int index;

	for(index = 0 ; index < 100 ; index++){
		(*goal_state)[index] = aux;
		(*goal_state)[index].set = New_Vector(SIZE);
	}

	Goal_State1(&((*goal_state)[0]));
	Goal_State2(&((*goal_state)[1]));
	Goal_State3(&((*goal_state)[2]));
}

//Menu Functions ----------------------------
int Menu(){
	int option;

	Print_Menu();

	printf("\nOption: ");
	scanf("%d", &option);
	system("cls || clear");

	while(option < 1 || option > EXIT){
		Print_Menu();

		printf("\nENTER A NUMBER FROM 1 TO %d!", EXIT);
		printf("\nOption: ");
		scanf("%d", &option);
		system("cls || clear");
	}

	return option;
}

int Option1(State *initial_state){   /* PICK INITIAL STATE */   
	int index;
	int i;

	printf("%d) default\n", 1);
	Print_Matrix(initial_state[0].set, M, N);

	for(i = 1 ; i < 100 ; i++){
		if(initial_state[i].key == -1) break;

		printf("%d)\n", i + 1);
		Print_Matrix(initial_state[i].set, M, N);
	}

	printf("Option: ");
	scanf("%d", &index);
	system("cls || clear");

	if(index >= 1 && index <= i){
		Print_Matrix(initial_state[index - 1].set, M, N);
		return (index - 1);
	}

	Exception_Message("INVALID INPUT!");

	return;
}

int Option2(State *initial_state){   /* ENTER INITIAL STATE */   
	if(initial_state[99].key != -1){
		Exception_Message("NO MORE SPACE!");
		return;
	}

	short *new_set = New_Vector(SIZE);
	int i, j;
	int k0 = -1;

	printf("Enter set values:\n");

	for(i = 0 ; i < M ; i++)
		for(j = 0 ; j < N ; j++)
			scanf("%d", &new_set[i * N + j]);

	for(i = 0 ; i < SIZE ; i++)
		if(new_set[i] == 0){
			k0 = i;
			break;
		}

	if(k0 != -1){
		State *new_state = New_State(new_set, k0, 0, NULL);

		for(i = 0 ; i < 100 ; i++)
			if(initial_state[i].key == -1)
				break;

		Transfer_State(new_state, &(initial_state[i]));
		system("cls || clear");
		Print_Matrix(new_state->set, M, N);
		return i;
	}

	else
		free(new_set);
	
	system("cls || clear");
	return;
}

int Option3(State *goal_state){   /* PICK GOAL STATE */   
	int index;
	int i;

	printf("%d) default\n", 1);
	Print_Matrix(goal_state[0].set, M, N);

	for(i = 1 ; i < 100 ; i++){
		if(goal_state[i].key == -1) break;

		printf("%d)\n", i + 1);
		Print_Matrix(goal_state[i].set, M, N);
	}

	printf("Option: ");
	scanf("%d", &index);
	system("cls || clear");

	if(index >= 1 && index <= i){
		Print_Matrix(goal_state[index - 1].set, M, N);
		return (index - 1);
	}

	Exception_Message("INVALID INPUT!");

	return;
}

int Option4(State *goal_state){   /* ENTER GOAL STATE */   
	if(goal_state[99].key != -1){
		Exception_Message("NO MORE SPACE!");
		return;
	}

	short *new_set = New_Vector(SIZE);
	int i, j;
	int k0 = -1;

	printf("Enter set values:\n");

	for(i = 0 ; i < M ; i++)
		for(j = 0 ; j < N ; j++)
			scanf("%d", &new_set[i * N + j]);

	for(i = 0 ; i < SIZE ; i++)
		if(new_set[i] == 0){
			k0 = i;
			break;
		}

	if(k0 != -1){
		State *new_state = New_State(new_set, k0, 0, NULL);

		for(i = 0 ; i < 100 ; i++)
			if(goal_state[i].key == -1)
				break;

		Transfer_State(new_state, &(goal_state[i]));
		system("cls || clear");
		Print_Matrix(new_state->set, M, N);
		return i;
	}

	else
		free(new_set);
	
	system("cls || clear");
	return;
}

State *Option5(State initial_state, State gs){   /* A* */ 
	system("cls || clear");  

	Print_Matrix(initial_state.set, M, N);

	State *solution = A_Star(initial_state, gs);

	return solution;
}

void Option6(State *solution){   /* SHOW MOVES */   
	if(solution == NULL){
		Exception_Message("NO SOLUTION TO PLAY!");
		return;
	}

	int index;
	int g = solution[0].g;

	Show_Moves(solution);
}

//Printing Functions ------------------------
void Print_Menu(){
	printf("Menu - 8 Puzzle\n\n");
	printf("1) Pick Initial State\n");
	printf("2) Enter Initial State\n");
	printf("3) Pick Goal State\n");
	printf("4) Enter Goal State\n");
	printf("5) A* Search\n");
	printf("6) Show Moves\n");
	printf("%d) Exit\n", EXIT);
}

void Show_Moves(State *solution){
	int index;
	int g = solution[0].g;

	for(index = g ; index >= 0 ; index--){
		system("cls || clear");
		printf("%d\n", solution[index].g);
		Print_Matrix(solution[index].set, M, N);
		Sleep(DELAY);
	}
}

//Exception Functions -----------------------
void Exception_Message(char *message){
	system("cls || clear");
	printf("%s\n", message);
	Sleep(1200);
	system("cls || clear");
}

//Control Functions -------------------------
void Control(){
	system("cls || clear");

	State *initial_state, *goal_state;
	State *solution = NULL;

	int initial_index = 0;
	int goal_index = 0;
	int option;

	Init_Initial_States(&initial_state);
	Init_Goal_States(&goal_state);

	do{
		option = Menu();

		switch(option){
			case 1:	/* PICK INITIAL STATE */
					initial_index = Option1(initial_state);
					Free_Solution(&solution);   
					break;

			case 2: /* ENTER INITIAL STATE */
					initial_index = Option2(initial_state);    
					break;

			case 3: /* PICK GOAL STATE */
					goal_index = Option3(goal_state);
					Free_Solution(&solution);   
					break;

			case 4: /* ENTER GOAL STATE */
					goal_index = Option4(goal_state);
					break;

			case 5: /* A* */
					Free_Solution(&solution);
					solution = Option5(initial_state[initial_index], goal_state[goal_index]);
					break;

			case 6: /* SHOW MOVES */
					Option6(solution);
					break;

			default: /* EXIT */
					 break;                       
		}	
	}while(option != EXIT);
}

//-------------------------------------------
