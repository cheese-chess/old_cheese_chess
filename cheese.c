#include <ctype.h>
#include <stdlib.h>
#include <cheese.h>

int cheese_turn(char piece) {
  if (piece == ' ') return CHEESE_NONE;
  else if (isupper(piece)) return CHEESE_WHITE;
  else return CHEESE_BLACK;
}

int cheese_eval(char *board) {
  return 0;
}

int cheese_valid(char *board, int *move, int turn) {
  if (move[0] == move[1]) return 0;
  else if (cheese_turn(board[move[0]]) == cheese_turn(board[move[1]])) return 0;

  return 1;
}

int **cheese_get_moves(char *board, int turn) {
  return NULL;
}

int **cheese_get_valid_moves(char *board, int turn) {
  return NULL;
}

void cheese_move(char *board, int *move) {
  board[move[1]] = board[move[0]];
  board[move[0]] = ' ';
}

void cheese_ai_move(char *board, int turn) {
  return;
}
