#include <vector>
#include "BitsetMove.h"

namespace MosaicGame::Game::Move {

    BitsetMove::BitsetMove(unsigned int offset) : _offset(offset) {}

    unsigned int BitsetMove::toOffset() const {
        return this->_offset;
    }

    BitsetBoard BitsetMove::toBoard(unsigned int size) const {
        return BitsetBoard(size, std::bitset<140>().set(this->_offset));
    }

    std::vector<BitsetMove> BitsetMove::fromBoard(const BitsetBoard &board) {
        std::vector<BitsetMove> moves = {};
        moves.reserve(board.count());
        auto boardString = board.toString();
        auto length = boardString.length();
        for (auto i = 0; i < length; i++) {
            if (boardString[length - i - 1] == '1') {
                moves.emplace_back(BitsetMove(i));
            }
        }
        return moves;
    }
}
