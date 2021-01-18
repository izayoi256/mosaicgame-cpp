#ifndef MOSAICGAME_LIBRARY_H
#define MOSAICGAME_LIBRARY_H

#ifdef __cplusplus
extern "C" {
#endif

void *create(unsigned char size);
void destroy(void *gamePointer);
bool isFirstTurn(void *gamePointer);
bool isSecondTurn(void *gamePointer);
bool firstWins(void *gamePointer);
bool secondWins(void *gamePointer);
bool playerWins(void *gamePointer);
bool opponentWins(void *gamePointer);
bool isOver(void *gamePointer);
bool isLegalMove(void *gamePointer, unsigned int offset);
unsigned short movesMade(void *gamePointer);
unsigned int getMove(void *gamePointer, unsigned short moveIndex);
unsigned short piecesPerPlayer(void *gamePointer);
unsigned short firstScore(void *gamePointer);
unsigned short secondScore(void *gamePointer);
unsigned short playerScore(void *gamePointer);
unsigned short opponentScore(void *gamePointer);
void copyPlayerBoard(void *gamePointer, char *returnPointer);
void copyOpponentBoard(void *gamePointer, char *returnPointer);
void copyFirstBoard(void *gamePointer, char *returnPointer);
void copySecondBoard(void *gamePointer, char *returnPointer);
void copyNeutralBoard(void *gamePointer, char *returnPointer);
void copyLegalBoard(void *gamePointer, char *returnPointer);
void makeMove(void *gamePointer, unsigned int offset);
void flipVertical(void *gamePointer);
void mirrorHorizontal(void *gamePointer);
void flipDiagonal(void *gamePointer);
void rotate90(void *gamePointer);
void rotate180(void *gamePointer);
void rotate270(void *gamePointer);
void transform(void *gamePointer);
void resetTransformation(void *gamePointer);

#ifdef __cplusplus
}
#endif

#endif //MOSAICGAME_LIBRARY_H
