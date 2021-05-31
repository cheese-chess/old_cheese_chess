#include <ctype.h>
#include <stdlib.h>
#include <chess.h>

#define CHESS_GET_X(idx) ((idx) % 8)
#define CHESS_GET_Y(idx) ((idx) / 8)

#define CHESS_GET_IDX(x, y) ((x) + (y) * 8)

#define ABS(x) ((x) < 0 ? -(x) : (x))

int chess_turn(char piece) {
  // Fully complete and working, do not touch
  if (piece == ' ') return CHESS_NONE;
  else if (isupper(piece)) return CHESS_WHITE;
  else return CHESS_BLACK;
}

int chess_valid(char *board, int *move, int turn) {
  if (move[0] == move[1]) return 0;
  else if (chess_turn(board[move[0]]) == chess_turn(board[move[1]])) return 0;
  else if (chess_turn(board[move[0]]) != turn) return 0;

  // Check if the move from piece at move[0] to index move[1] is valid
  // for the specified player(CHESS_WHITE or CHESS_BLACK)

  int pos_0[2] = {CHESS_GET_X(move[0]), CHESS_GET_Y(move[0])};
  int pos_1[2] = {CHESS_GET_X(move[1]), CHESS_GET_Y(move[1])};

  if (board[move[0]] == 'P') {
    if (board[move[1]] == ' ' && pos_0[0] == pos_1[0]) {
      if (pos_0[1] == pos_1[1] + 1)
        return 1;

      if (pos_0[1] == 6 && pos_1[1] == 4) {
        if (chess_turn(board[CHESS_GET_IDX(pos_0[0], 5)]) == CHESS_NONE)
          return 1;
      }
    }

    if (pos_0[0] > 0) {
      if (pos_1[0] == pos_0[0] - 1 && pos_1[1] == pos_0[1] - 1) {
        if (chess_turn(board[CHESS_GET_IDX(pos_0[0] - 1, pos_0[1] - 1)]) == CHESS_BLACK)
          return 1;
      }
    }

    if (pos_0[0] < 7) {
      if (pos_1[0] == pos_0[0] + 1 && pos_1[1] == pos_0[1] - 1) {
        if (chess_turn(board[CHESS_GET_IDX(pos_0[0] + 1, pos_0[1] - 1)]) == CHESS_BLACK)
          return 1;
      }
    }
  }

  if (board[move[0]] == 'p') {
    if (board[move[1]] == ' ' && pos_0[0] == pos_1[0]) {
      if (pos_0[1] == pos_1[1] - 1)
        return 1;

      if (pos_0[1] == 1 && pos_1[1] == 3) {
        if (chess_turn(board[CHESS_GET_IDX(pos_0[0], 2)]) == CHESS_NONE)
          return 1;
      }
    }

    if (pos_0[0] > 0) {
      if (pos_1[0] == pos_0[0] - 1 && pos_1[1] == pos_0[1] + 1) {
        if (chess_turn(board[CHESS_GET_IDX(pos_0[0] - 1, pos_0[1] + 1)]) == CHESS_WHITE)
          return 1;
      }
    }

    if (pos_0[0] < 7) {
      if (pos_1[0] == pos_0[0] + 1 && pos_1[1] == pos_0[1] + 1) {
        if (chess_turn(board[CHESS_GET_IDX(pos_0[0] + 1, pos_0[1] + 1)]) == CHESS_WHITE)
          return 1;
      }
    }
  }

  if (board[move[0]] == 'R' || board[move[0]] == 'r' || board[move[0]] == 'Q' || board[move[0]] == 'q') {
    if (pos_0[0] == pos_1[0]) {
      if (pos_0[1] > pos_1[1]) {
        for (int i = pos_1[1]; i <= pos_0[1] - 1; i++) {
          if (chess_turn(board[CHESS_GET_IDX(pos_0[0], i)]) == turn)
            return 0;
          if (i != pos_1[1] && chess_turn(board[CHESS_GET_IDX(pos_0[0], i)]) != CHESS_NONE && chess_turn(board[CHESS_GET_IDX(pos_0[0], i)]) != turn)
            return 0;
        }
      } else {
        for (int i = pos_0[1] + 1; i <= pos_1[1]; i++) {
          if (chess_turn(board[CHESS_GET_IDX(pos_0[0], i)]) == turn)
            return 0;
          if (i != pos_1[1] && chess_turn(board[CHESS_GET_IDX(pos_0[0], i)]) != CHESS_NONE && chess_turn(board[CHESS_GET_IDX(pos_0[0], i)]) != turn)
            return 0;
        }
      }

      return 1;
    }

    if (pos_0[1] == pos_1[1]) {
      if (pos_0[0] > pos_1[0]) {
        for (int i = pos_1[0]; i <= pos_0[0] - 1; i++) {
          if (chess_turn(board[CHESS_GET_IDX(i, pos_0[1])]) == turn)
            return 0;
          if (i != pos_1[0] && chess_turn(board[CHESS_GET_IDX(i, pos_0[1])]) != CHESS_NONE && chess_turn(board[CHESS_GET_IDX(i, pos_0[1])]) != turn)
            return 0;
        }
      } else {
        for (int i = pos_0[0] + 1; i <= pos_1[0]; i++) {
          if (chess_turn(board[CHESS_GET_IDX(i, pos_0[1])]) == turn)
            return 0;
          if (i != pos_1[0] && chess_turn(board[CHESS_GET_IDX(i, pos_0[1])]) != CHESS_NONE && chess_turn(board[CHESS_GET_IDX(i, pos_0[1])]) != turn)
            return 0;
        }
      }

      return 1;
    }
  }

  if (board[move[0]] == 'B' || board[move[0]] == 'b' || board[move[0]] == 'Q' || board[move[0]] == 'q') {
    if (ABS(pos_0[0] - pos_1[0]) == ABS(pos_0[1] - pos_1[1])) {
      if ((pos_1[0] - pos_0[0]) > 0 && (pos_1[1] - pos_0[1]) > 0) {
        // Down-right

        for (int i = pos_0[0] + 1; i <= pos_1[0]; i++) {
          if (chess_turn(board[CHESS_GET_IDX(i, pos_0[1] + (i - pos_0[0]))]) == turn)
            return 0;
          if (i != pos_1[0] && chess_turn(board[CHESS_GET_IDX(i, pos_0[1] + (i - pos_0[0]))]) != CHESS_NONE && chess_turn(board[CHESS_GET_IDX(i, pos_0[1] + (i - pos_0[0]))]) != turn)
            return 0;
        }
      } else if ((pos_1[0] - pos_0[0]) < 0 && (pos_1[1] - pos_0[1]) > 0) {
        // Down-left

        for (int i = pos_1[0]; i <= pos_0[0] - 1; i++) {
          if (chess_turn(board[CHESS_GET_IDX(i, pos_0[1] + (i - pos_0[0]))]) == turn)
            return 0;
          if (i != pos_1[0] && chess_turn(board[CHESS_GET_IDX(i, pos_0[1] + (i - pos_0[0]))]) != CHESS_NONE && chess_turn(board[CHESS_GET_IDX(i, pos_0[1] + (i - pos_0[0]))]) != turn)
            return 0;
        }
      } else if ((pos_1[0] - pos_0[0]) > 0 && (pos_1[1] - pos_0[1]) < 0) {
        // Up-right

        for (int i = pos_0[0] + 1; i <= pos_1[0]; i++) {
          if (chess_turn(board[CHESS_GET_IDX(i, pos_0[1] + (i - pos_0[0]))]) == turn)
            return 0;
          if (i != pos_1[0] && chess_turn(board[CHESS_GET_IDX(i, pos_0[1] + (i - pos_0[0]))]) != CHESS_NONE && chess_turn(board[CHESS_GET_IDX(i, pos_0[1] + (i - pos_0[0]))]) != turn)
            return 0;
        }
      } else if ((pos_1[0] - pos_0[0]) < 0 && (pos_1[1] - pos_0[1]) < 0) {
        // Up-left

        for (int i = pos_1[0]; i <= pos_0[0] - 1; i++) {
          if (chess_turn(board[CHESS_GET_IDX(i, pos_0[1] + (i - pos_0[0]))]) == turn)
            return 0;
          if (i != pos_1[0] && chess_turn(board[CHESS_GET_IDX(i, pos_0[1] + (i - pos_0[0]))]) != CHESS_NONE && chess_turn(board[CHESS_GET_IDX(i, pos_0[1] + (i - pos_0[0]))]) != turn)
            return 0;
        }
      }

      return 1;
    }
  }

  if (board[move[0]] == 'K' || board[move[0]] == 'k') {
    int off_x = ABS(pos_0[0] - pos_1[0]);
    int off_y = ABS(pos_0[1] - pos_1[1]);

    if (off_x < 2 && off_y < 2 && !(off_x == 0 && off_y == 0)) {
      return 1;
    }
  }

  return 0;
}

int **chess_get_moves(char *board, int turn) {
  // I mean, it technically works, but it is the fuckin
  // slowest way of doing it in the entire universe...

  int **move_arr = malloc(sizeof(int *));
  int move_cnt = 0;

  move_arr[move_cnt] = NULL;

  for (int i = 0; i < 64; i++) {
    if (chess_turn(board[i]) == turn) {
      for (int j = 0; j < 64; j++) {
        if (i != j && chess_turn(board[j]) != turn) {
          int move[2] = {i, j};

          if (chess_valid(board, move, turn)) {
            move_arr = realloc(move_arr, (move_cnt + 2) * sizeof(int *));

            move_arr[move_cnt] = malloc(2 * sizeof(int));
            move_arr[move_cnt][0] = i;
            move_arr[move_cnt][1] = j;

            move_arr[++move_cnt] = NULL;
          }
        }
      }
    }
  }

  return move_arr;
}

void chess_free(int **moves) {
  int move_cnt = 0;

  while (moves[move_cnt] != NULL)
    free(moves[move_cnt++]);

  free(moves);
}

void chess_move(char *board, int *move) {
  // Fully complete and working, do not touch
  if (CHESS_GET_Y(move[1]) == 7 && board[move[0]] == 'p')
    board[move[0]] = 'q';
  if (CHESS_GET_Y(move[1]) == 0 && board[move[0]] == 'P')
    board[move[0]] = 'Q';

  board[move[1]] = board[move[0]];
  board[move[0]] = ' ';
}
