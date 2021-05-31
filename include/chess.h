#ifndef __CHESS_H__
#define __CHESS_H__

#define CHESS_WHITE 0
#define CHESS_BLACK 1
#define CHESS_NONE  2

int chess_turn(char piece);

int chess_valid(char *board, int *move, int turn);

int **chess_get_moves(char *board, int turn);
int **chess_get_valid_moves(char *board, int turn);

void chess_move(char *board, int *move);

#endif
