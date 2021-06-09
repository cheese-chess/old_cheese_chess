#ifdef CHEESE_ALGO_AA2006

// THIS ALGORITHM IS BASED OFF OF SEGFAULTDEV'S ALGORITHM
// SEE cheese_segfaultdev.c FOR THE ORIGINAL ALGORITHM

#include <ctype.h>
#include <chess.h>
#include <stdlib.h>
#include <string.h>
#include <cheese.h>
#include <stdio.h>
#include <math.h>

// King
const int king_table[] = {
  18, 20, 19, 20, 20, 19, 20, 18,
  17, 17, 18, 19, 19, 18, 17, 17,
  16, 16, 17, 18, 18, 17, 16, 16,
  15, 15, 16, 17, 17, 16, 15, 15,
  15, 15, 16, 17, 17, 16, 15, 15,
  16, 16, 17, 18, 18, 17, 16, 16,
  17, 17, 18, 19, 19, 18, 17, 17,
  18, 20, 19, 20, 20, 19, 20, 18
};

//Knight
const int knight_table[] = {
  11, 11, 11, 11, 11, 11, 11, 11,
  11, 13, 13, 13, 13, 13, 13, 11,
  11, 13, 15, 15, 15, 15, 13, 11,
  11, 13, 20, 20, 20, 20, 13, 11,
  11, 13, 20, 20, 20, 20, 13, 11,
  11, 13, 15, 15, 15, 15, 13, 11,
  11, 13, 13, 13, 13, 13, 13, 11,
  11, 11, 11, 11, 11, 11, 11, 11
};

//Bishop
const int bishop_table[] = {
  11, 12, 12, 12, 12, 12, 12, 11,
  12, 13, 13, 13, 13, 13, 13, 12,
  12, 13, 15, 15, 15, 15, 13, 12,
  12, 13, 15, 15, 15, 15, 13, 12,
  12, 13, 15, 15, 15, 15, 13, 12,
  12, 13, 15, 15, 15, 15, 13, 12,
  12, 13, 13, 13, 13, 13, 13, 12,
  11, 12, 12, 12, 12, 12, 12, 11
};

//Queen
const int queen_table[] = {
  11, 12, 12, 15, 15, 12, 12, 11,
  12, 13, 13, 13, 13, 13, 13, 12,
  12, 13, 15, 15, 15, 15, 13, 12,
  12, 13, 15, 15, 15, 15, 13, 12,
  12, 13, 15, 15, 15, 15, 13, 12,
  12, 13, 15, 15, 15, 15, 13, 12,
  12, 13, 13, 13, 13, 13, 13, 12,
  11, 12, 12, 15, 15, 12, 12, 11
};

//Rook
const int rook_table[] = {
  11, 12, 12, 12, 12, 12, 12, 11,
  12, 11, 11, 11, 11, 11, 11, 12,
  12, 11, 11, 11, 11, 11, 11, 12,
  12, 11, 11, 11, 11, 11, 11, 12,
  12, 11, 11, 11, 11, 11, 11, 12,
  12, 11, 11, 11, 11, 11, 11, 12,
  12, 11, 11, 11, 11, 11, 11, 12,
  11, 12, 12, 12, 12, 12, 12, 11
};

//Pawn
const int pawn_table[] = {
  20, 20, 20, 20, 20, 20, 20, 20,
  17, 17, 17, 17, 17, 17, 17, 17,
  13, 14, 15, 16, 16, 15, 14, 13,
  14, 18, 19, 20, 20, 19, 18, 14,
  14, 18, 19, 20, 20, 19, 18, 14,
  13, 14, 15, 16, 16, 15, 14, 13,
  17, 17, 17, 17, 17, 17, 17, 17,
  20, 20, 20, 20, 20, 20, 20, 20
};

static int cheese_value(char piece, int pos) {
    int black = 0;
    if (piece == ' ') return 0;
    if (piece >= 'a') piece -= 32;

    switch(piece) {
        case 'P':
            return 1 * pawn_table[pos];
        case 'B': 
            return 6 * bishop_table[pos];
        case 'N':
            return 5 * knight_table[pos];
        case 'R':
            return 10 * rook_table[pos];
        case 'Q':
            return 900 * queen_table[pos];
        case 'K':
            return 10000 * king_table[pos];
    }

    return 0;
}

int cheese_eval(char *board, int turn) {
  int score = 0;

  for (int i = 0; i < 64; i++) {
    if (chess_turn(board[i]) == CHESS_NONE) {
      continue;
    } else if (chess_turn(board[i]) == turn) {
      score += cheese_value(board[i], i);
    } else {
      score -= cheese_value(board[i], i);
    }
  }

  return score;
}

int cheese_move(char *board, int *move, int do_move, int turn, int layers) {
  int **moves = chess_get_moves(board, turn);
  if (!moves) return -10101010;

  int move_cnt = 0;

  while (moves[move_cnt] != NULL) move_cnt++;

  printf("Possible moves: %d\n", move_cnt);
  printf("Board: \"%s\"\n", board);

  int best_move = -1;
  int best_score = -10101010;

  char *board_clone = malloc(64);

  for (int i = 0; i < move_cnt; i++) {
    memcpy(board_clone, board, 64);

    chess_move(board_clone, moves[i]);

    int score = cheese_eval(board_clone, turn);

    if (layers > 0) {
      int temp_score = -cheese_move(board_clone, NULL, 0, 1 - turn, layers - 1);

      //score += temp_score;
      score = score < temp_score ? score : temp_score;
    }

    //printf("Move %d[%d('%c') to %d('%c')]: Score %d\n", i, moves[i][0], board[moves[i][0]], moves[i][1], board[moves[i][1]], score);

    if (score > best_score) {
      best_move = i;
      best_score = score;
    }
  }

  free(board_clone);

  if (best_move >= 0) {
    printf("Chosen move %d[%d('%c') to %d('%c')]: Score %d\n", best_move, moves[best_move][0], board[moves[best_move][0]], moves[best_move][1], board[moves[best_move][1]], best_score);
    if (do_move) chess_move(board, moves[best_move]);
    if (move != NULL) memcpy(move, moves[best_move], sizeof(int) * 2);
  } else {
    printf("No move chosen\n");
  }

  chess_free(moves);

  return best_score;
}

#endif