#include <cstring>
#include "library.h"
#include "Game/BitsetOneToOneGame.h"
#include "Game/Move/BitsetMove.h"

using MosaicGame::Game::BitsetOneToOneGame;
using MosaicGame::Game::Move::BitsetMove;

void *create(unsigned char size) {
    return (void *) new BitsetOneToOneGame(size);
}

void destroy(void *gamePointer) {
    delete (BitsetOneToOneGame *) gamePointer;
}

bool isOver(void *gamePointer) {
    return ((BitsetOneToOneGame *) gamePointer)->isOver();
}

bool firstWins(void *gamePointer) {
    return ((BitsetOneToOneGame *) gamePointer)->firstWins();
}

bool secondWins(void *gamePointer) {
    return ((BitsetOneToOneGame *) gamePointer)->secondWins();
}

bool isFirstTurn(void *gamePointer) {
    return ((BitsetOneToOneGame *) gamePointer)->isFirstTurn();
}

bool isSecondTurn(void *gamePointer) {
    return ((BitsetOneToOneGame *) gamePointer)->isSecondTurn();
}

bool playerWins(void *gamePointer) {
    return ((BitsetOneToOneGame *) gamePointer)->playerWins();
}

bool opponentWins(void *gamePointer) {
    return ((BitsetOneToOneGame *) gamePointer)->opponentWins();
}

bool isLegalMove(void *gamePointer, unsigned int offset) {
    return ((BitsetOneToOneGame *) gamePointer)->isLegalMove(BitsetMove(offset));
}

unsigned short movesMade(void *gamePointer) {
    return ((BitsetOneToOneGame *) gamePointer)->movesMade();
}

unsigned int getMove(void *gamePointer, unsigned short moveIndex) {
    return ((BitsetOneToOneGame *) gamePointer)->moves()[moveIndex].toOffset();
}

unsigned short piecesPerPlayer(void *gamePointer) {
    return ((BitsetOneToOneGame *) gamePointer)->piecesPerPlayer();
}

unsigned short firstScore(void *gamePointer) {
    return ((BitsetOneToOneGame *) gamePointer)->firstScore();
}

unsigned short secondScore(void *gamePointer) {
    return ((BitsetOneToOneGame *) gamePointer)->secondScore();
}

unsigned short playerScore(void *gamePointer) {
    return ((BitsetOneToOneGame *) gamePointer)->playerScore();
}

unsigned short opponentScore(void *gamePointer) {
    return ((BitsetOneToOneGame *) gamePointer)->opponentScore();
}

void copyFirstBoard(void *gamePointer, char *returnPointer) {
    strcpy(returnPointer, ((BitsetOneToOneGame *) gamePointer)->firstBoard().toString().c_str());
}

void copySecondBoard(void *gamePointer, char *returnPointer) {
    strcpy(returnPointer, ((BitsetOneToOneGame *) gamePointer)->secondBoard().toString().c_str());
}

void copyPlayerBoard(void *gamePointer, char *returnPointer) {
    strcpy(returnPointer, ((BitsetOneToOneGame *) gamePointer)->playerBoard().toString().c_str());
}

void copyOpponentBoard(void *gamePointer, char *returnPointer) {
    strcpy(returnPointer, ((BitsetOneToOneGame *) gamePointer)->opponentBoard().toString().c_str());
}

void copyNeutralBoard(void *gamePointer, char *returnPointer) {
    strcpy(returnPointer, ((BitsetOneToOneGame *) gamePointer)->neutralBoard().toString().c_str());
}

void copyLegalBoard(void *gamePointer, char *returnPointer) {
    strcpy(returnPointer, ((BitsetOneToOneGame *) gamePointer)->legalBoard().toString().c_str());
}

void makeMove(void *gamePointer, unsigned int offset) {
    ((BitsetOneToOneGame *) gamePointer)->makeMove(BitsetMove(offset));
}

void flipVertical(void *gamePointer) {
    ((BitsetOneToOneGame *) gamePointer)->flipVertical();
}

void mirrorHorizontal(void *gamePointer) {
    ((BitsetOneToOneGame *) gamePointer)->mirrorHorizontal();
}

void flipDiagonal(void *gamePointer) {
    ((BitsetOneToOneGame *) gamePointer)->flipDiagonal();
}

void rotate90(void *gamePointer) {
    ((BitsetOneToOneGame *) gamePointer)->rotate90();
}

void rotate180(void *gamePointer) {
    ((BitsetOneToOneGame *) gamePointer)->rotate180();
}

void rotate270(void *gamePointer) {
    ((BitsetOneToOneGame *) gamePointer)->rotate270();
}

void transform(void *gamePointer) {
    ((BitsetOneToOneGame *) gamePointer)->transform();
}

void resetTransformation(void *gamePointer) {
    ((BitsetOneToOneGame *) gamePointer)->resetTransformation();
}
