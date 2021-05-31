#ifndef __CHEESE_H__
#define __CHEESE_H__

#define CHEESE_WHITE 0
#define CHEESE_BLACK 1
#define CHEESE_NONE  2

int cheese_turn(char piece);

int cheese_eval(char *board);
int cheese_valid(char *board, int *move, int turn);

int **cheese_get_moves(char *board, int turn);
int **cheese_get_valid_moves(char *board, int turn);

void cheese_move(char *board, int *move);
void cheese_ai_move(char *board, int turn);

#endif
