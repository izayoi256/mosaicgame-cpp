#ifndef MOSAICGAME_BITSETMOVE_H
#define MOSAICGAME_BITSETMOVE_H

#include <vector>
#include "Move.h"
#include "../../Board/BitsetBoard.h"

using MosaicGame::Board::BitsetBoard;

namespace MosaicGame::Game::Move {
    class BitsetMove : public Move<BitsetBoard> {
    public:
        explicit BitsetMove(unsigned int offset);

        [[nodiscard]] unsigned int toOffset() const override;

        [[nodiscard]] BitsetBoard toBoard(unsigned int size) const override;

        static std::vector<BitsetMove> fromBoard(const BitsetBoard& board);

    private:
        unsigned int _offset;
    };
}

#endif //MOSAICGAME_BITSETMOVE_H
