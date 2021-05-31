#include <ctype.h>
#include <stdlib.h>
#include <chess.h>

int chess_turn(char piece) {
  // Fully complete and working, do not touch(Okay, @aa2006???)
  if (piece == ' ') return CHESS_NONE;
  else if (isupper(piece)) return CHESS_WHITE;
  else return CHESS_BLACK;
}

int chess_valid(char *board, int *move, int turn) {
  if (move[0] == move[1]) return 0;
  else if (chess_turn(board[move[0]]) == chess_turn(board[move[1]])) return 0;

  // Check if the move from piece at move[0] to index move[1] is valid
  // for the specified player(CHESS_WHITE or CHESS_BLACK)

  return 1;
}

int **chess_get_moves(char *board, int turn) {
  // Get a list of moves for each piece of the specified player, checking
  // them with chess_valid() before
  return NULL;
}

void chess_move(char *board, int *move) {
  // Fully complete and working, do not touch(Okay, @aa2006???)
  board[move[1]] = board[move[0]];
  board[move[0]] = ' ';
}
