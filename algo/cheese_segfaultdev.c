#ifdef CHEESE_ALGO_SEGFAULTDEV

#include <ctype.h>
#include <chess.h>
#include <stdlib.h>
#include <string.h>
#include <cheese.h>
#include <stdio.h>

const int pawn_table[] = {
  7, 7, 7, 8, 8, 7, 7, 7,
  6, 6, 6, 7, 7, 6, 6, 6,
  5, 5, 5, 6, 6, 5, 5, 5,
  4, 4, 4, 5, 5, 4, 4, 4,
  3, 3, 3, 4, 4, 3, 3, 3,
  2, 2, 2, 3, 3, 2, 2, 2,
  1, 1, 1, 2, 2, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1
};

const int knight_table[] = {
  4, 4, 4, 8, 8, 4, 4, 4,
  4, 6, 6, 4, 4, 6, 6, 4,
  4, 2, 6, 6, 6, 6, 2, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
  2, 4, 4, 4, 4, 4, 4, 2,
  2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 2, 2,
  1, 1, 1, 1, 1, 1, 1, 1
};

const int rook_table[] = {
  8, 7, 7, 8, 8, 7, 7, 8,
  6, 5, 5, 6, 6, 5, 5, 6,
  6, 5, 3, 5, 5, 3, 5, 6,
  7, 6, 1, 5, 5, 1, 6, 7,
  7, 6, 2, 5, 5, 2, 6, 7,
  6, 5, 3, 5, 5, 3, 5, 6,
  6, 5, 5, 6, 6, 5, 5, 6,
  8, 7, 7, 8, 8, 7, 7, 8,
};

const int default_table[] = {
  2, 3, 4, 5, 5, 4, 3, 2,
  3, 4, 5, 6, 6, 5, 4, 3,
  4, 5, 6, 7, 7, 6, 5, 4,
  5, 6, 7, 8, 8, 7, 6, 5,
  4, 5, 6, 7, 7, 6, 5, 4,
  3, 4, 5, 6, 6, 5, 4, 3,
  2, 3, 4, 5, 5, 4, 3, 2,
  1, 2, 3, 4, 4, 3, 2, 1,
};

const int king_table[] = {
  1, 1, 4, 5, 5, 4, 1, 1,
  1, 2, 4, 6, 6, 4, 2, 1,
  1, 2, 4, 5, 5, 4, 2, 1,
  1, 2, 3, 4, 4, 3, 2, 1,
  2, 3, 4, 5, 5, 4, 3, 2,
  1, 2, 5, 6, 6, 5, 2, 1,
  2, 3, 5, 7, 7, 5, 3, 2,
  2, 2, 6, 8, 8, 6, 2, 2,
};

const int value_table[] = {
  1, 4, 4, 6, 12, 1001,
  1, 3, 3, 6, 12, 1000,
  2, 3, 4, 5, 11, 1001
};

static int cheese_value(char piece, int pos, int part) {
  if (piece == ' ') return 0;

  if (piece >= 'a') {
    piece -= 32;
  } else {
    pos = pos % 8 + (7 - (pos / 8)) * 8;
  }

  switch (piece) {
    case 'P':
      return value_table[part * 6 + 0] * pawn_table[pos];
    case 'B':
      return value_table[part * 6 + 1] * default_table[pos];
    case 'N':
      return value_table[part * 6 + 2] * default_table[pos];
    case 'R':
      return value_table[part * 6 + 3] * default_table[pos];
    case 'Q':
      return value_table[part * 6 + 4] * default_table[pos];
    case 'K':
      return value_table[part * 6 + 5] * king_table[pos];
  }

  return 0;
}

int cheese_eval(char *board, int turn) {
  int score = 0, pieces = 0;

  for (int i = 0; i < 64; i++) {
    int temp_turn = chess_turn(board[i]);

    if (turn == temp_turn) pieces++;
  }

  int part = 0;

  if (pieces <= 11) part = 1;
  if (pieces <= 5) part = 2;

  for (int i = 0; i < 64; i++) {
    if (chess_turn(board[i]) == CHESS_NONE) {
      continue;
    } else if (chess_turn(board[i]) == turn) {
      score += cheese_value(board[i], i, part);
    } else {
      score -= cheese_value(board[i], i, part);
    }
  }

  return score;
}

int cheese_move(char *board, int *move, int do_move, int turn, int layers) {
  int **moves = chess_get_moves(board, turn);
  if (!moves) return -CHESS_MAX_SCORE;

  int move_cnt = 0;

  while (moves[move_cnt] != NULL) move_cnt++;

  if (move_cnt) {
    for (int i = 0; i < move_cnt; i++) {
      int idx_1 = rand() % move_cnt;
      int idx_2 = rand() % move_cnt;

      if (idx_1 == idx_2) {
        i--;
        continue;
      }

      int *temp = moves[idx_1];
      moves[idx_1] = moves[idx_2];
      moves[idx_2] = temp;
    }
  }

  // printf("Possible moves: %d\n", move_cnt);
  // printf("Board: \"%s\"\n", board);

  int best_move = -1;
  int best_score = -CHESS_MAX_SCORE;

  char *board_clone = malloc(64);

  for (int i = 0; i < move_cnt; i++) {
    memcpy(board_clone, board, 64);

    chess_move(board_clone, moves[i]);

    int score = cheese_eval(board_clone, turn);

    if (score < best_score) continue;

    if (layers > 0) {
      int temp_score = -cheese_move(board_clone, NULL, 0, 1 - turn, layers - 1);

      // score += temp_score;
      score = score < temp_score ? score : temp_score;
    }

    // printf("Move %d[%d('%c') to %d('%c')]: Score %d\n", i, moves[i][0], board[moves[i][0]], moves[i][1], board[moves[i][1]], score);

    if (score > best_score) {
      best_move = i;
      best_score = score;
    }
  }

  free(board_clone);

  if (best_move >= 0) {
    // printf("Chosen move %d[%d('%c') to %d('%c')]: Score %d\n", best_move, moves[best_move][0], board[moves[best_move][0]], moves[best_move][1], board[moves[best_move][1]], best_score);
    if (do_move) chess_move(board, moves[best_move]);
    if (move != NULL) memcpy(move, moves[best_move], sizeof(int) * 2);
  } else {
    // printf("No move chosen\n");
  }

  chess_free(moves);

  return best_score;
}

#endif
