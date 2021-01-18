#ifndef MOSAICGAME_LIBRARY_H
#define MOSAICGAME_LIBRARY_H

#ifdef __cplusplus
extern "C" {
#endif

void *create(unsigned char size);
void destroy(void *gamePointer);
bool firstWins(void *gamePointer);
bool secondWins(void *gamePointer);
bool playerWins(void *gamePointer);
bool opponentWins(void *gamePointer);
bool isOver(void *gamePointer);
bool isLegalMove(void *gamePointer, unsigned int offset);
unsigned short playerScore(void *gamePointer);
unsigned short opponentScore(void *gamePointer);
char *firstBoard(void *gamePointer);
char *secondBoard(void *gamePointer);
char *playerBoard(void *gamePointer);
char *opponentBoard(void *gamePointer);
char *neutralBoard(void *gamePointer);
char *legalBoard(void *gamePointer);
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
