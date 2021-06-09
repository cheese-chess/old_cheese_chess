<center><img src="./assets/cheese.png"></center>

# CCE - Cheese Chess Engine
Like chess but cheesy? A hobbyist chess engine/game (with high ambitions).

## Algorithms
CCE currently has 3 algorithms. You can change the algorithm used by editing ```build.sh```. The ELO rating for the algorithms is represented below. (data from various games against Stockfish and human players) 
| Algorithm   | Approx. ELO Rating |
|-------------|--------------------|
| segfaultdev | 1400               |
| aa2006      | 1250               |
| values      | 1000               |

## Building
Building from source is really easy. Go into a suitable directory and clone this repo:
```bash
git clone https://github.com/cheese-chess/cheese_chess.git
```
Then, execute ```build.sh```:
```bash
chmod +x build.sh
./build.sh
```
After that, you should see a ```cheese``` executable. Run it to open the game:
```
./cheese <depth> <theme>
```
where depth is the number of layers the algorithm should search and 'theme' the number of the theme you would like. Recommended depth: 4.<br>

## Themes
CCE currently has two themes, both pixelated:

### pixelated_default (num: ```1```):
The original theme, with pixelated pieces.<br>
![White King](./assets/pixelated_default/king_white.png)
![White Queen](./assets/pixelated_default/queen_white.png)
![White Rook](./assets/pixelated_default/rook_white.png)
![White Bishop](./assets/pixelated_default/bishop_white.png)
![White Knight](./assets/pixelated_default/knight_white.png)
![White Pawn](./assets/pixelated_default/pawn_white.png)<br>
![Black King](./assets/pixelated_default/king_black.png)
![Black Queen](./assets/pixelated_default/queen_black.png)
![Black Rook](./assets/pixelated_default/rook_black.png)
![Black Bishop](./assets/pixelated_default/bishop_black.png)
![Black Knight](./assets/pixelated_default/knight_black.png)
![Black Pawn](./assets/pixelated_default/pawn_black.png)<br>
![Board](./assets/pixelated_default/board.png)

### pixelated_modern (num: ```2```):
An upgrade of the original theme, with different kings/queens.<br>
![White King](./assets/pixelated_modern/king_white.png)
![White Queen](./assets/pixelated_modern/queen_white.png)
![White Rook](./assets/pixelated_modern/rook_white.png)
![White Bishop](./assets/pixelated_modern/bishop_white.png)
![White Knight](./assets/pixelated_modern/knight_white.png)
![White Pawn](./assets/pixelated_modern/pawn_white.png)<br>
![Black King](./assets/pixelated_modern/king_black.png)
![Black Queen](./assets/pixelated_modern/queen_black.png)
![Black Rook](./assets/pixelated_modern/rook_black.png)
![Black Bishop](./assets/pixelated_modern/bishop_black.png)
![Black Knight](./assets/pixelated_modern/knight_black.png)
![Black Pawn](./assets/pixelated_modern/pawn_black.png)<br>
![Board](./assets/pixelated_modern/board.png)

## Changing the Algorithm
To change the algorithm, open ```build.sh``` and put the name of your algorithm. For example, if the algorithm is ```CHEESE_ALGO_SEGFAULTDEV``` and you want to try the aa2006 algorithm, you would change it to ```CHEESE_ALGO_AA2006```. After that, build again, and execute.

