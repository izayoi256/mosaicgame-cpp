#ifndef MOSAICGAME_MOVE_H
#define MOSAICGAME_MOVE_H

namespace MosaicGame::Game::Move {
    template<class BOARD>
    class Move {
    public:
        [[nodiscard]] virtual unsigned int toOffset() const = 0;

        [[nodiscard]] virtual BOARD toBoard(unsigned int size) const = 0;
    };
}

#endif //MOSAICGAME_MOVE_H
