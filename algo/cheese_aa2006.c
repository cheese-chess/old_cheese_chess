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
  13, 13, 13, 13, 13, 13, 13, 13,
  13, 13, 13, 13, 13, 13, 13, 13,
  13, 13, 15, 15, 15, 15, 13, 13,
  13, 13, 20, 20, 20, 20, 13, 13,
  13, 13, 20, 20, 20, 20, 13, 13,
  13, 13, 15, 15, 15, 15, 13, 13,
  13, 13, 13, 13, 13, 13, 13, 13,
  13, 13, 13, 13, 13, 13, 13, 13
};

//Bishop
const int bishop_table[] = {
  13, 14, 14, 14, 14, 14, 14, 13,
  14, 13, 13, 13, 13, 13, 13, 14,
  14, 13, 15, 15, 15, 15, 13, 14,
  14, 13, 15, 15, 15, 15, 13, 14,
  14, 13, 15, 15, 15, 15, 13, 14,
  14, 13, 15, 15, 15, 15, 13, 14,
  14, 13, 13, 13, 13, 13, 13, 14,
  13, 14, 14, 14, 14, 14, 14, 13
};

//Queen
const int queen_table[] = {
  13, 14, 14, 15, 15, 14, 14, 13,
  14, 13, 13, 13, 13, 13, 13, 14,
  14, 13, 15, 15, 15, 15, 13, 14,
  14, 13, 15, 15, 15, 15, 13, 14,
  14, 13, 15, 15, 15, 15, 13, 14,
  14, 13, 15, 15, 15, 15, 13, 14,
  14, 13, 13, 13, 13, 13, 13, 14,
  13, 14, 14, 15, 15, 14, 14, 13
};

//Rook
const int rook_table[] = {
  14, 14, 14, 14, 14, 14, 14, 14,
  14, 13, 13, 13, 13, 13, 13, 14,
  14, 13, 13, 13, 13, 13, 13, 14,
  14, 13, 13, 13, 13, 13, 13, 14,
  14, 13, 13, 13, 13, 13, 13, 14,
  14, 13, 13, 13, 13, 13, 13, 14,
  14, 13, 13, 13, 13, 13, 13, 14,
  14, 14, 14, 14, 14, 14, 14, 14
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

const int stages_table[] = {
  1, 3, 3, 10, 900, 10000,
  1, 6, 6, 10, 1800, 10000,
  3, 3, 3, 100, 1800, 10000
};

static int cheese_value(char piece, int pos, int stage) {
    int black = 0;
    if (piece == ' ') return 0;
    if (piece >= 'a') piece -= 32;

    switch(piece) {
        case 'P':
            return stages_table[stage * 6] * pawn_table[pos];
        case 'B': 
            return stages_table[stage * 6 + 1] * bishop_table[pos];
        case 'N':
            return stages_table[stage * 6 + 2] * knight_table[pos];
        case 'R':
            return stages_table[stage * 6 + 3] * rook_table[pos];
        case 'Q':
            return stages_table[stage * 6 + 4] * queen_table[pos];
        case 'K':
            return stages_table[stage * 6 + 5] * king_table[pos];
    }

    return 0;
}

int cheese_eval(char *board, int turn) {
  int score = 0, pieces = 0, squares = 64;
  
  while (squares --) {
    int temp = chess_turn(board[squares]);
    if (turn == temp) pieces ++;
  }
  printf("%i\n", pieces);
  int stage = 0; //opening
  if (pieces <= 7) {stage = 2;}//endgame
  else if (pieces <= 14) {stage = 1;} //middlegame

  for (int i = 0; i < 64; i++) {
    if (chess_turn(board[i]) == CHESS_NONE) {
      continue;
    } else if (chess_turn(board[i]) == turn) {
      score += cheese_value(board[i], i, stage);
    } else {
      score -= cheese_value(board[i], i, stage);
    }
  }

  return score;
}

int cheese_move(char *board, int *move, int do_move, int turn, int layers) {
  int **moves = chess_get_moves(board, turn);
  if (!moves) return -10101010;

  int move_cnt = 0;

  while (moves[move_cnt] != NULL) move_cnt++;

  //printf("Possible moves: %d\n", move_cnt);
  //printf("Board: \"%s\"\n", board);

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
    //printf("Chosen move %d[%d('%c') to %d('%c')]: Score %d\n", best_move, moves[best_move][0], board[moves[best_move][0]], moves[best_move][1], board[moves[best_move][1]], best_score);
    if (do_move) chess_move(board, moves[best_move]);
    if (move != NULL) memcpy(move, moves[best_move], sizeof(int) * 2);
  } else {
    //printf("No move chosen\n");
  }

  chess_free(moves);

  return best_score;
}

#endif