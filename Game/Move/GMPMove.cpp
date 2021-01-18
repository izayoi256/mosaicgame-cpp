#include <vector>
#include "GMPMove.h"

namespace MosaicGame::Game::Move {

    GMPMove::GMPMove(unsigned int offset) : _offset(offset) {}

    unsigned int GMPMove::toOffset() const {
        return this->_offset;
    }

    GMPBoard GMPMove::toBoard(unsigned int size) const {
        return GMPBoard(size, std::string("1") + std::string(this->_offset, '0'));
    }

    std::vector<GMPMove> GMPMove::fromBoard(const GMPBoard &board) {
        std::vector<GMPMove> moves = {};
        moves.reserve(board.count());
        auto boardString = board.toString();
        auto length = boardString.length();
        for (auto i = 0; i < length; i++) {
            if (boardString[length - i - 1] == '1') {
                moves.emplace_back(GMPMove(i));
            }
        }
        return moves;
    }
}
