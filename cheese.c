#include <ctype.h>
#include <chess.h>
#include <stdlib.h>
#include <string.h>
#include <cheese.h>

static int cheese_value(char piece) {
  if (piece == ' ') return 0;
  if (piece >= 'a') piece -= 32;

  switch (piece) {
    case 'P':
      return 1;
    case 'B':
    case 'N':
      return 2;
    case 'R':
      return 5;
    case 'Q':
      return 7;
    case 'K':
      return 100;
  }

  return 0;
}

int cheese_eval(char *board, int turn) {
  int score = 0;

  for (int i = 0; i < 64; i++) {
    if (chess_turn(board[i]) == CHESS_NONE) {
      continue;
    } else if (chess_turn(board[i]) == turn) {
      score += cheese_value(board[i]);
    } else {
      score -= cheese_value(board[i]);
    }
  }

  return score;
}

void cheese_move(char *board, int turn) {
  int **moves = chess_get_moves(board, turn);

  int move_cnt = 0;

  while (moves[move_cnt] != NULL) move_cnt++;

  int best_move = -1;
  int best_score = -100;

  char *board_clone = malloc(64);

  for (int i = 0; i < move_cnt; i++) {
    memcpy(board_clone, board, 64);

    chess_move(board_clone, moves[i]);

    int score = cheese_eval(board_clone, turn);

    if (score > best_score) {
      best_move = i;
      best_score = score;
    }
  }

  free(board_clone);

  if (best_move >= 0) chess_move(board, moves[best_move]);

  chess_free(moves);

  return;
}
