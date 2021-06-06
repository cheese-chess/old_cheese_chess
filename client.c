#include <raylib.h>
#include <stdlib.h>
#include <cheese.h>
#include <chess.h>
#include <math.h>
#include <stdio.h>

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

  if (argc != 2) {
    printf("Usage: ./cheese <depth>\n");
    exit(1);
  }

  char *p;
  int depth = strtol(argv[1], &p, 10);

  const int scr_width = 144 * 4;
  const int scr_height = 132 * 4;

  InitWindow(scr_width, scr_height, "cheese_chess");

  Texture pieces_tex[12] = {
    LoadTexture("assets/bishop_black.png"),
    LoadTexture("assets/pawn_black.png"),
    LoadTexture("assets/rook_black.png"),
    LoadTexture("assets/knight_black.png"),
    LoadTexture("assets/king_black.png"),
    LoadTexture("assets/queen_black.png"),
    LoadTexture("assets/bishop_white.png"),
    LoadTexture("assets/pawn_white.png"),
    LoadTexture("assets/rook_white.png"),
    LoadTexture("assets/knight_white.png"),
    LoadTexture("assets/king_white.png"),
    LoadTexture("assets/queen_white.png")
  };

  Texture board_tex = LoadTexture("assets/board.png");
  Texture shadow_tex = LoadTexture("assets/shadow.png");

  Texture option_black_tex = LoadTexture("assets/option_black.png");
  Texture option_white_tex = LoadTexture("assets/option_white.png");

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
