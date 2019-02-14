/* Project: A* Search for 8 Puzzle
/* File: astar.c
/* by:             _  __  
             )\/) / ` ) ) 
            (  ( (_. /_/            */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "search.h"
#include "8puzzle.h"
#include "heap.h"
#include "list.h"
#include "hash.h"
#include "vector.h"

//Functions Implementations -----------------
//Problem Solving Functions -----------------
bool Is_Solvable(State s, State goal_state){
	int i, j, k;
	int goal_state_index;
	int inversions = 0;

	for(i = 0 ; i < SIZE ; i++){
		if(i != s.k0){
			for(j = 0 ; j < SIZE ; j++)
				if(s.set[i] == goal_state.set[j]){
					goal_state_index = j;
					break;
				}

			for(j = (i + 1) ; j < SIZE ; j++)
				if(j != s.k0)
					for(k = 0 ;  k < goal_state_index ; k++)
						if(k != goal_state.k0)
							if(goal_state.set[k] == s.set[j]){
								inversions++;
								break;
							}
		}
	}

	if(inversions % 2 == 0)
		return true;

	return false;
}

bool States_Are_Equal(State s1, State s2){
	if(s1.key == s2.key){
		int k;

		for(k = 0 ; k < SIZE ; k++)
			if(s1.set[k] != s2.set[k])
				return false;

		return true;
	}

	return false;
}

bool State_Already_Opened(State s, Hash_Table ht, Heap *h){
	Node *aux = ht[s.key].first;

	while(aux != NULL){
		if(States_Are_Equal(aux->state, s)){
			if(s.f < aux->state.f){
				aux->state.g = s.g;
				aux->state.h = s.h;
				aux->state.f = s.f;
				aux->state.parent = s.parent;

				int index;

				for(index = 0 ; index <= h->last ; index++)
					if(h->node_adress[index] == aux)
						break;

				Adjust_Going_Up(h, index);
			}

			return true;
		}

		aux = aux->next;
	}

	return false;
}

bool State_Already_Closed(State s, Hash_Table h){
	Node *aux = h[s.key].first;

	while(aux != NULL){
		if(States_Are_Equal(aux->state, s))
			return true;

		aux = aux->next;
	}

	return false;
}

bool State_In_Heap(State s, Heap *h, int current){
	if(h->node_adress[current]->state.key == s.key)
		if(States_Are_Equal(h->node_adress[current]->state, s))
			return true;

	int left = 2 * current + 1;
	int right = 2 * current + 2;

	if(left <= h->last)
		if(s.key >= h->node_adress[left]->state.key)
			if(State_In_Heap(s, h, left))
				return true;

	if(right <= h->last)
		if(s.key >= h->node_adress[right]->state.key)
			if(State_In_Heap(s, h, right))
				return true;

	return false;
}

void Transfer_State(State *s1, State *s2){
	s2->key = s1->key;
	Transfer_Vector(s1->set, s2->set, SIZE);
	s2->k0 = s1->k0;
	s2->g = s1->g;
	s2->h = s1->h;
	s2->f = s1->f;
}

bool Is_Solution(State s){
	if(s.h == 0)
		return true;

	return false;
}

State *Solution(State *solution_state){
	State *solution = (State *) malloc(sizeof(State) * (solution_state->g + 1));
	State *aux = solution_state;
	State s;

	int g = solution_state->g;
	int index;

	for(index = 0 ; index <= g ; index++){
		s.set = New_Vector(SIZE);
		solution[index] = s;
		Transfer_State(aux, &(solution[index]));
		aux = aux->parent;
	}

	return solution;
}

void Free_Solution(State **solution){
	State *aux = *solution;

	if(*solution == NULL)
		return;

	int index;
	int g = aux[0].g;

	for(index = g ; index >= 0 ; index --)
		free(aux[index].set);

	free(aux);
	*solution = NULL;
}

//Search Functions --------------------------
void Heuristic(State *s, State goal_state){
	// s->h = 0;

	// int k;

	// for(k = 0 ; k < SIZE ; k++){
	// 	if(s->set[k] != goal_state.set[k] && s->set[k] != 0)
	// 		s->h++;
	// }

	// s->f = s->g + s->h;

	s->h = 0;

	int sk, si, sj;
	int gk, gi, gj;
	int di, dj;

	for(sk = 0 ; sk < SIZE ; sk++){
		if(s->set[sk] != 0){
			si = k2i(sk, N);
			sj = k2j(sk, N);

			for(gk = 0 ; gk < SIZE ; gk++)
				if(goal_state.set[gk] == s->set[sk])
					break;

			gi = k2i(gk, N);
			gj = k2j(gk, N);

			di = si - gi;
			dj = sj - gj;

			if(di < 0)
				di *= (-1);

			if(dj < 0)
				dj *= (-1);

			s->h += (di + dj);
		}
	}

	s->f = s->g + s->h;
}

State *A_Star(State initial_state, State goal_state){
	clock_t t0, t1;
	double t;

	t0 = clock();

	if(!Is_Solvable(initial_state, goal_state)){
		t1 = clock();
		t = (((t1 - t0) * 1000) / (double) CLOCKS_PER_SEC);

		printf("UNSOLVABLE!\n\n");
		printf("Time: %.4f s\n", ((t / 60000) - ((int) (t / 60000))) * 60);
		printf("Opened States: 0\n");
		printf("Closed States: 0\n");
		printf("Total States: 0\n\n");

		return NULL;
	}

	Hash_Table opened;
	Init_Hash_Table(&opened, MAX_STATES);

	Hash_Table closed;
	Init_Hash_Table(&closed, MAX_STATES);

	Heap h;
	Init_Heap(&h, MAX_STATES);

	State *current = New_State(initial_state.set, initial_state.k0, 0, initial_state.parent);
	Heuristic(current, goal_state);

	State *successor;
	State s[4];

	Node *current_node = New_Node(*current);
	Node *successor_node;

	int k0;
	int i;

	for(i = 0 ; i < 4 ; i++)
		s[i].set = New_Vector(SIZE);

	/* A* Search begins */
	t0 = clock();
	Push(&(opened[current->key]), current_node);

	while(current != NULL){
		if(Is_Solution(*current)){
			/* A* Search ends */
			t1 = clock();
			t = (((t1 - t0) * 1000) / (double) CLOCKS_PER_SEC);

			for(i = 0 ; i < 4 ; i++)
				free(s[i].set);

			State *solution = Solution(current);

			Print_Solution(solution);
			printf("\nSOLUTION FOUND!\n\n");
			printf("Time: %.4f s\n", ((t / 60000) - ((int) (t / 60000))) * 60);
			printf("Cost: %d\n", solution[0].g);
			printf("Opened States: %d\n", Hash_Table_Size(opened, MAX_STATES));
			printf("Closed States: %d\n", Hash_Table_Size(closed, MAX_STATES));
			printf("Total States: %d\n\n", Hash_Table_Size(opened, MAX_STATES) + Hash_Table_Size(closed, MAX_STATES));

			Delete_Hash_Table(&opened, MAX_STATES);
			Delete_Hash_Table(&closed, MAX_STATES);

			return solution;
		}

		k0 = current->k0;

		/* MOVE UP */ 
		if(k0 - M >= 0){
			Transfer_State(current, &s[0]);
			Move_Up(&s[0]);
			Heuristic(&s[0], goal_state);

			if(!State_Already_Closed(s[0], closed) && !State_Already_Opened(s[0], opened, &h)){
				successor = New_State(s[0].set, s[0].k0, s[0].g, current);
				successor->h = s[0].h;
				successor->f = s[0].g + s[0].h;
				successor_node = New_Node(*successor);

				Push(&(opened[successor->key]), successor_node);
				Insert(&h, successor_node);
			}
		}
			
		/* MOVE DOWN */			
		if(k0 + M < SIZE){
			Transfer_State(current, &s[1]);
			Move_Down(&s[1]);
			Heuristic(&s[1], goal_state);

			if(!State_Already_Closed(s[1], closed) && !State_Already_Opened(s[1], opened, &h)){
				successor = New_State(s[1].set, s[1].k0, s[1].g, current);
				successor->h = s[1].h;
				successor->f = s[1].g + s[1].h;
				successor_node = New_Node(*successor);

				Push(&(opened[successor->key]), successor_node);
				Insert(&h, successor_node);
			}
		}

		/* MOVE RIGHT */ 
		if(k0 % N + 1 < N){
			Transfer_State(current, &s[2]);
			Move_Right(&s[2]);
			Heuristic(&s[2], goal_state);

			if(!State_Already_Closed(s[2], closed) && !State_Already_Opened(s[2], opened, &h)){
				successor = New_State(s[2].set, s[2].k0, s[2].g, current);
				successor->h = s[2].h;
				successor->f = s[2].g + s[2].h;
				successor_node = New_Node(*successor);

				Push(&(opened[successor->key]), successor_node);
				Insert(&h, successor_node);
			}
		}		

		/* MOVE LEFT */
		if(k0 % N - 1 >= 0){
			Transfer_State(current, &s[3]);
			Move_Left(&s[3]);
			Heuristic(&s[3], goal_state);

			if(!State_Already_Closed(s[3], closed) && !State_Already_Opened(s[3], opened, &h)){
				successor = New_State(s[3].set, s[3].k0, s[3].g, current);
				successor->h = s[3].h;
				successor->f = s[3].g + s[3].h;
				successor_node = New_Node(*successor);

				Push(&(opened[successor->key]), successor_node);
				Insert(&h, successor_node);
			}
		}

		Pop(&(opened[current->key]), current_node);
		Push(&(closed[current->key]), current_node);

		current_node = Remove(&h);

		if(current_node != NULL)
			current = &(current_node->state);
	}

	return NULL;
}

//Printing Functions ------------------------
void Print_Solution(State *solution){
	int index;
	int g = solution[0].g;

	printf("Solution:\n");

	printf("------------------------\n");

	for(index = g ; index >= 0 ; index --){
		printf("Cost: %d\n", g - index);
		Print_Matrix(solution[index].set, M, N);
	}

	printf("------------------------\n");
}

//-------------------------------------------