#ifndef MOSAICGAME_BOARD_H
#define MOSAICGAME_BOARD_H

#include<memory>

namespace MosaicGame::Board {
    template<class T>
    class Board {
    public:
        [[nodiscard]] virtual unsigned int size() const = 0;

        [[nodiscard]] virtual std::string toString() const = 0;

        [[nodiscard]] virtual unsigned int count() const = 0;

        [[nodiscard]] virtual T mirrorHorizontal() const = 0;

        [[nodiscard]] virtual T flipVertical() const = 0;

        [[nodiscard]] virtual T flipDiagonal() const = 0;

        [[nodiscard]] virtual T rotate90() const = 0;

        [[nodiscard]] virtual T rotate180() const = 0;

        [[nodiscard]] virtual T rotate270() const = 0;

        [[nodiscard]] virtual T promoteZero() const = 0;

        [[nodiscard]] virtual T promoteOne() const = 0;

        [[nodiscard]] virtual T promoteTwo() const = 0;

        [[nodiscard]] virtual T promoteThree() const = 0;

        [[nodiscard]] virtual T promoteFour() const = 0;

        [[nodiscard]] virtual T promoteHalfOrMore() const = 0;

        [[nodiscard]] virtual T promoteMajority() const = 0;

        [[nodiscard]] virtual bool operator==(const T &other) const = 0;

        [[nodiscard]] virtual T operator&(const T &other) const = 0;

        [[nodiscard]] virtual T operator|(const T &other) const = 0;

        [[nodiscard]] virtual T operator^(const T &other) const = 0;

        [[nodiscard]] virtual T operator<<(unsigned int amount) const = 0;

        [[nodiscard]] virtual T operator>>(unsigned int amount) const = 0;

        [[nodiscard]] virtual T flip() const = 0;
    };
}

#endif //MOSAICGAME_BOARD_H
