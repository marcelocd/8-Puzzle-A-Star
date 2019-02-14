/* UFG - Instituto de Informática      *
 * Inteligência Artificial: Trabalho 1 *
 * Aluno: Marcelo Cardoso Dias         *
 * Matrícula: 201305842                */

#ifndef _8PUZZLE_H_
#define _8PUZZLE_H_

#define   M              3
#define   N              3
#define   SIZE         (M * N)
#define   MAX_STATES   181440

//Problem Models ----------------------------
typedef struct st{
	int key;     /* Hash */
	short *set;  /* Game Matrix */
	int k0;
	int g;
	int h;
	int f;
	struct st *parent; 
}State;

//------------------------------------------- 

//Functions Prototypes ----------------------
//Initializing Functions --------------------
State *New_State(short *, int, int, State *);
void Initial_State1(State *);
void Initial_State2(State *);
void Initial_State3(State *);
void Goal_State1(State *);
void Goal_State2(State *);
void Goal_State3(State *);

//Problem Solving Functions -----------------
void Free_State(State *);
void Heuristic(State *, State);

//Rules Functions ---------------------------
void Move_Up(State *s);
void Move_Down(State *s);
void Move_Right(State *s);
void Move_Left(State *s);

//-------------------------------------------

#endif