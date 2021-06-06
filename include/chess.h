#ifndef __CHESS_H__
#define __CHESS_H__

#define CHESS_WHITE 0
#define CHESS_BLACK 1
#define CHESS_NONE  2

#define CHESS_MAX_SCORE 1048576

int chess_turn(char piece);

int chess_ended(char *board);
int chess_valid(char *board, int *move, int turn);

int **chess_get_moves(char *board, int turn);
void chess_free(int **moves);

void chess_move(char *board, int *move);

#endif
