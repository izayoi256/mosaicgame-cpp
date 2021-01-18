#include <chrono>
#include <iostream>

#include "Game/BitsetOneToOneGame.h"
//#include "Game/GMPOneToOneGame.h"

using MosaicGame::Game::BitsetOneToOneGame;
//using MosaicGame::Game::GMPOneToOneGame;

int main() {
    auto start = std::chrono::system_clock::now();
    for (auto i = 0; i < 100; i++) {
        auto game = BitsetOneToOneGame(7);
        while (!game.isOver()) {
            auto legalMoves = game.legalMoves();
            game.makeMove(legalMoves[0]);
        }
    }

    auto end = std::chrono::system_clock::now();
    auto duration = end - start;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    std::cout << ms / (double)1000 << " seconds" << std::endl;

    return 0;
}
