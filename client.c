#include <raylib.h>
#include <stdlib.h>
#include <cheese.h>
#include <chess.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

bool isNumber(char number[])
{
    int i = 0;
    for (; number[i] != 0; i++) {
        if (!isdigit(number[i]))
            return false;
    }
    return true;
}


static Texture get_piece_tex(Texture pieces_tex[12], char piece) {
  Texture piece_tex;
  piece_tex.width = 0;

  switch (piece) {
    case 'b':
      piece_tex = pieces_tex[0];
      break;
    case 'p':
      piece_tex = pieces_tex[1];
      break;
    case 'r':
      piece_tex = pieces_tex[2];
      break;
    case 'n':
      piece_tex = pieces_tex[3];
      break;
    case 'k':
      piece_tex = pieces_tex[4];
      break;
    case 'q':
      piece_tex = pieces_tex[5];
      break;
    case 'B':
      piece_tex = pieces_tex[6];
      break;
    case 'P':
      piece_tex = pieces_tex[7];
      break;
    case 'R':
      piece_tex = pieces_tex[8];
      break;
    case 'N':
      piece_tex = pieces_tex[9];
      break;
    case 'K':
      piece_tex = pieces_tex[10];
      break;
    case 'Q':
      piece_tex = pieces_tex[11];
      break;
  }

  return piece_tex;
}

int main(int argc, char *argv[]) {
  char *p;
  if (argc < 3) {
    printf("Usage: ./cheese <depth> <theme>\n");
    exit(1);
  } else {
    if (!isNumber(argv[1]) || !isNumber(argv[2])) {
      printf("Depth and Theme must be integers!\n");
      exit(3);
    }
  }

  char *folder;
  int theme = strtol(argv[2], &p, 10);
  if (!isNumber(argv[2]) || theme > 2 || theme < 1) {
    printf("Theme not found.\n");
    exit(2);
  }
  if (theme == 1) folder = "assets/pixelated_default";
  if (theme == 2) folder = "assets/pixelated_modern";

  char *k;
  int depth = strtol(argv[1], &k, 10);

  const int scr_width = 144 * 4;
  const int scr_height = 132 * 4;

  char *bishop_black = "/bishop_black.png";
  char *pawn_black = "/pawn_black.png";
  char *rook_black = "/rook_black.png";
  char *king_black = "/king_black.png";
  char *queen_black = "/queen_black.png";
  char *knight_black = "/knight_black.png";
  
  char *bishop_white = "/bishop_white.png";
  char *pawn_white = "/pawn_white.png";
  char *rook_white = "/rook_white.png";
  char *king_white = "/king_white.png";
  char *queen_white = "/queen_white.png";
  char *knight_white = "/knight_white.png";

  char * bishop_black_malloc = (char *) malloc(1 + strlen(bishop_black)+ strlen(folder) );
  char * pawn_black_malloc = (char *) malloc(1 + strlen(pawn_black)+ strlen(folder) );
  char * rook_black_malloc = (char *) malloc(1 + strlen(rook_black)+ strlen(folder) );
  char * king_black_malloc = (char *) malloc(1 + strlen(king_black)+ strlen(folder) );
  char * queen_black_malloc = (char *) malloc(1 + strlen(queen_black)+ strlen(folder) );
  char * knight_black_malloc = (char *) malloc(1 + strlen(knight_black)+ strlen(folder) );
  char * bishop_white_malloc = (char *) malloc(1 + strlen(bishop_white)+ strlen(folder) );
  char * pawn_white_malloc = (char *) malloc(1 + strlen(pawn_white)+ strlen(folder) );
  char * rook_white_malloc = (char *) malloc(1 + strlen(rook_white)+ strlen(folder) );
  char * queen_white_malloc = (char *) malloc(1 + strlen(queen_white)+ strlen(folder) );
  char * knight_white_malloc = (char *) malloc(1 + strlen(knight_white)+ strlen(folder) );
  char * king_white_malloc = (char *) malloc(1 + strlen(king_white)+ strlen(folder) );

  strcpy(bishop_black_malloc, folder);
  strcpy(pawn_black_malloc, folder);
  strcpy(rook_black_malloc, folder);
  strcpy(king_black_malloc, folder);
  strcpy(queen_black_malloc, folder);
  strcpy(knight_black_malloc, folder);
  strcpy(bishop_white_malloc, folder);
  strcpy(pawn_white_malloc, folder);
  strcpy(rook_white_malloc, folder);
  strcpy(queen_white_malloc, folder);
  strcpy(knight_white_malloc, folder);
  strcpy(king_white_malloc, folder);

  strcat(bishop_black_malloc, bishop_black);
  strcat(pawn_black_malloc, pawn_black);
  strcat(rook_black_malloc, rook_black);
  strcat(king_black_malloc, king_black);
  strcat(queen_black_malloc, queen_black);
  strcat(knight_black_malloc, knight_black);
  strcat(bishop_white_malloc, bishop_white);
  strcat(pawn_white_malloc, pawn_white);
  strcat(rook_white_malloc, rook_white);
  strcat(king_white_malloc, king_white);
  strcat(queen_white_malloc, queen_white);
  strcat(knight_white_malloc, knight_white);
  
  InitWindow(scr_width, scr_height, "cheese_chess");

  Texture pieces_tex[12] = {
    LoadTexture(bishop_black_malloc),
    LoadTexture(pawn_black_malloc),
    LoadTexture(rook_black_malloc),
    LoadTexture(knight_black_malloc),
    LoadTexture(king_black_malloc),
    LoadTexture(queen_black_malloc),
    LoadTexture(bishop_white_malloc),
    LoadTexture(pawn_white_malloc),
    LoadTexture(rook_white_malloc),
    LoadTexture(knight_white_malloc),
    LoadTexture(king_white_malloc),
    LoadTexture(queen_white_malloc)
  };

  Texture board_tex = LoadTexture("assets/pixelated_default/board.png");
  Texture shadow_tex = LoadTexture("assets/pixelated_default/shadow.png");

  Texture option_black_tex = LoadTexture("assets/pixelated_default/option_black.png");
  Texture option_white_tex = LoadTexture("assets/pixelated_default/option_white.png");


 char board[65] = \
    "rnbqkbnr" \
    "pppppppp" \
    "        " \
    "        " \
    "        " \
    "        " \
    "PPPPPPPP" \
    "RNBQKBNR" \
  ; 

  /*char board[64] = \
    "r bqkb r" \
    "pppppppp" \
    "        " \
    "        " \
    "        " \
    "        " \
    "PPPPPPPP" \
    "R BQKB R" \
  ;*/

  int moving_idx = -1, moving_rel_x = 0, moving_rel_y = 0;

  int move_changed = 1;

  int best_move[2] = {0, 0};

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground((Color){41, 26, 43, 255});
    DrawTextureEx(board_tex, (Vector2){0, 0}, 0, 4, WHITE);

    for (int i = 0; i < 64; i++) {
      int x = i % 8;
      int y = i / 8;

      Texture piece_tex = get_piece_tex(pieces_tex, board[i]);
      if (piece_tex.width == 0) continue;

      if (i != moving_idx) {
        DrawTextureEx(piece_tex, (Vector2){x * 64 + 32, y * 56}, 0, 4, WHITE);
      }
    }

    if (move_changed) {
      cheese_move(board, best_move, 0, CHESS_WHITE, depth - 1);
      move_changed = 0;
    } else {
      int x_0 = best_move[0] % 8;
      int y_0 = best_move[0] / 8;
      int x_1 = best_move[1] % 8;
      int y_1 = best_move[1] / 8;

      // DrawTextureEx(option_white_tex, (Vector2){x * 64 + 32, y * 56}, 0, 4, WHITE);

      float dist = sqrtf(
                        ((float)(x_0) - (float)(x_1)) * ((float)(x_0) - (float)(x_1)) +
                        ((float)(y_0) - (float)(y_1)) * ((float)(y_0) - (float)(y_1))
                      ) * 64;

      float angle = (atan2f((float)(y_1) - (float)(y_0), (float)(x_1) - (float)(x_0)) * 180.0) / PI;

      DrawTexturePro(option_white_tex, (Rectangle){0, 0, 16, 16}, (Rectangle){x_0 * 64 + 64, y_0 * 56 + 56, 64, dist}, (Vector2){32, 32}, angle - 90.0, WHITE);

      DrawLineEx((Vector2){x_0 * 64 + 64, y_0 * 56 + 84}, (Vector2){x_1 * 64 + 64, y_1 * 56 + 84}, 5, RED);
    }

    if (moving_idx != -1) {
      Texture piece_tex = get_piece_tex(pieces_tex, board[moving_idx]);
      if (piece_tex.width == 0) continue;

      DrawTextureEx(shadow_tex, (Vector2){(GetMouseX() + moving_rel_x) & ~3, ((GetMouseY() + moving_rel_y) & ~3) - 8}, 0, 4, WHITE);
      DrawTextureEx(piece_tex, (Vector2){(GetMouseX() + moving_rel_x) & ~3, ((GetMouseY() + moving_rel_y) & ~3) - 8}, 0, 4, WHITE);
    }

    EndDrawing();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      int x = (GetMouseX() - 32) / 64;
      int y = (GetMouseY() - 56) / 56;

      if (x >= 0 && x < 8 && y >= 0 && y < 8) {
        if (moving_idx == -1) {
          if (chess_turn(board[x + (y * 8)]) == CHESS_WHITE) {
            moving_idx = x + (y * 8);

            moving_rel_x = (x * 64 + 32) - GetMouseX();
            moving_rel_y = (y * 56) - GetMouseY();
          }
        } else {
          int move[2] = {moving_idx, x + (y * 8)};

          if (chess_valid(board, move, CHESS_WHITE)) {
            chess_move(board, move);

            moving_idx = -1;

            cheese_move(board, NULL, 1, CHESS_BLACK, depth);

            move_changed = 1;
          } else if (move[0] == move[1]) {
            moving_idx = -1;
          }
        }
      } else {
        moving_idx = -1;
      }
    } else if (IsKeyPressed(KEY_SPACE)) {
      if (moving_idx == -1) {
        cheese_move(board, NULL, 1, CHESS_WHITE, depth);
        cheese_move(board, NULL, 1, CHESS_BLACK, depth);

        move_changed = 1;
      }
    }
  }

  return 0;
}
