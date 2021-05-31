#include <ctype.h>
#include <stdlib.h>
#include <chess.h>

int chess_turn(char piece) {
  // Fully complete and working, do not touch
  if (piece == ' ') return CHESS_NONE;
  else if (isupper(piece)) return CHESS_WHITE;
  else return CHESS_BLACK;
}

int chess_valid(char *board, int *move, int turn) {
  if (move[0] == move[1]) return 0;
  else if (chess_turn(board[move[0]]) == chess_turn(board[move[1]])) return 0;

  // Check if the move from piece at move[0] to index move[1] is valid
  // for the specified player(CHESS_WHITE or CHESS_BLACK)

if (board[move[0]] == 'P') {
  if (board[move[1]] == ' ') {
    if (move[1] == move[0] - 8) {
      return 1;
    } else if (move[0] / 8 == 6 && move[1] == move[0] - 16) {
      return 1;
    }
  } 
  if (chess_turn(board[move[0]] - 7) == CHESS_BLACK || chess_turn(board[move[0]] - 9 == CHESS_BLACK)) {
    if (move[1] == move[0] - 7 || move[1] == move[0] - 9) {
      return 1;
    }
  }
}

  return 0;
}

int **chess_get_moves(char *board, int turn) {
  // Get a list of moves for each piece of the specified player, checking
  // them with chess_valid() before
  return NULL;
}

void chess_move(char *board, int *move) {
  // Fully complete and working, do not touch
  board[move[1]] = board[move[0]];
  board[move[0]] = ' ';
}
