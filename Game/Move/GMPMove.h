#ifndef MOSAICGAME_GMPMOVE_H
#define MOSAICGAME_GMPMOVE_H

#include <vector>
#include "Move.h"
#include "../../Board/GMPBoard.h"

using MosaicGame::Board::GMPBoard;

namespace MosaicGame::Game::Move {
    class GMPMove : public Move<GMPBoard> {
    public:
        explicit GMPMove(unsigned int offset);

        [[nodiscard]] unsigned int toOffset() const override;

        [[nodiscard]] GMPBoard toBoard(unsigned int size) const override;

        static std::vector<GMPMove> fromBoard(const GMPBoard& board);

    private:
        unsigned int _offset;
    };
}

#endif //MOSAICGAME_GMPMOVE_H
