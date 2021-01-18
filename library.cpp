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

bool playerWins(void *gamePointer) {
    return ((BitsetOneToOneGame *) gamePointer)->playerWins();
}

bool opponentWins(void *gamePointer) {
    return ((BitsetOneToOneGame *) gamePointer)->opponentWins();
}

bool isLegalMove(void *gamePointer, unsigned int offset) {
    return ((BitsetOneToOneGame *) gamePointer)->isLegalMove(BitsetMove(offset));
}

unsigned short playerScore(void *gamePointer) {
    return ((BitsetOneToOneGame *) gamePointer)->playerScore();
}

unsigned short opponentScore(void *gamePointer) {
    return ((BitsetOneToOneGame *) gamePointer)->opponentScore();
}

char *firstBoard(void *gamePointer) {
    auto firstBoard = ((BitsetOneToOneGame *) gamePointer)->firstBoard().toString();
    char *result = new char[firstBoard.size() + 1];
    std::char_traits<char>::copy(result, firstBoard.c_str(), firstBoard.size() + 1);
    return result;
}

char *secondBoard(void *gamePointer) {
    auto secondBoard = ((BitsetOneToOneGame *) gamePointer)->secondBoard().toString();
    char *result = new char[secondBoard.size() + 1];
    std::char_traits<char>::copy(result, secondBoard.c_str(), secondBoard.size() + 1);
    return result;
}

char *playerBoard(void *gamePointer) {
    auto playerBoard = ((BitsetOneToOneGame *) gamePointer)->playerBoard().toString();
    char *result = new char[playerBoard.size() + 1];
    std::char_traits<char>::copy(result, playerBoard.c_str(), playerBoard.size() + 1);
    return result;
}

char *opponentBoard(void *gamePointer) {
    auto opponentBoard = ((BitsetOneToOneGame *) gamePointer)->opponentBoard().toString();
    char *result = new char[opponentBoard.size() + 1];
    std::char_traits<char>::copy(result, opponentBoard.c_str(), opponentBoard.size() + 1);
    return result;
}

char *neutralBoard(void *gamePointer) {
    auto neutralBoard = ((BitsetOneToOneGame *) gamePointer)->neutralBoard().toString();
    char *result = new char[neutralBoard.size() + 1];
    std::char_traits<char>::copy(result, neutralBoard.c_str(), neutralBoard.size() + 1);
    return result;
}

char *legalBoard(void *gamePointer) {
    auto legalBoard = ((BitsetOneToOneGame *) gamePointer)->legalBoard().toString();
    char *result = new char[legalBoard.size() + 1];
    std::char_traits<char>::copy(result, legalBoard.c_str(), legalBoard.size() + 1);
    return result;
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
