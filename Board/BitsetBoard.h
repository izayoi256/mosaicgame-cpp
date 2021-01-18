#ifndef MOSAICGAME_BITSETBOARD_H
#define MOSAICGAME_BITSETBOARD_H

#include <bitset>
#include <memory>
#include <unordered_map>
#include "Board.h"

namespace MosaicGame::Board {
    class BitsetBoard : public Board<BitsetBoard> {
    public:
        explicit BitsetBoard(unsigned char size, const std::bitset<140> &bitset);

        explicit BitsetBoard(unsigned int size, const std::string &bitsetString);

        explicit BitsetBoard(unsigned int size);

        static BitsetBoard emptyBoard(unsigned char size);

        static BitsetBoard groundBoard(unsigned char size);

        static BitsetBoard neutralBoard(unsigned char size);

        [[nodiscard]] unsigned int size() const override;

        [[nodiscard]] std::string toString() const override;

        [[nodiscard]] unsigned int count() const override;

        [[nodiscard]] BitsetBoard mirrorHorizontal() const override;

        [[nodiscard]] BitsetBoard flipVertical() const override;

        [[nodiscard]] BitsetBoard flipDiagonal() const override;

        [[nodiscard]] BitsetBoard rotate90() const override;

        [[nodiscard]] BitsetBoard rotate180() const override;

        [[nodiscard]] BitsetBoard rotate270() const override;

        [[nodiscard]] bool operator==(const BitsetBoard &other) const override;

        [[nodiscard]] BitsetBoard operator&(const BitsetBoard &other) const override;

        [[nodiscard]] BitsetBoard operator|(const BitsetBoard &other) const override;

        [[nodiscard]] BitsetBoard operator^(const BitsetBoard &other) const override;

        [[nodiscard]] BitsetBoard operator<<(unsigned int amount) const override;

        [[nodiscard]] BitsetBoard operator>>(unsigned int amount) const override;

        [[nodiscard]] BitsetBoard flip() const override;

        [[nodiscard]] BitsetBoard promoteZero() const override;

        [[nodiscard]] BitsetBoard promoteOne() const override;

        [[nodiscard]] BitsetBoard promoteTwo() const override;

        [[nodiscard]] BitsetBoard promoteThree() const override;

        [[nodiscard]] BitsetBoard promoteFour() const override;

        [[nodiscard]] BitsetBoard promoteHalfOrMore() const override;

        [[nodiscard]] BitsetBoard promoteMajority() const override;

    private:
        unsigned char _size;
        unsigned int _bitSize;
        std::bitset<140> _bitset;
        static std::unordered_map<unsigned char, std::shared_ptr<BitsetBoard>> _neutralBoards;
        static std::unordered_map<unsigned char, std::shared_ptr<BitsetBoard>> _groundBoards;
        static std::unordered_map<short, std::bitset<140>> _mirrorHorizontalMasks;
        static std::unordered_map<short, std::bitset<140>> _flipVerticalMasks;
        static std::unordered_map<short, std::bitset<140>> _flipDiagonalMasks;
        static std::unordered_map<unsigned char, std::bitset<140>> _boardMasks;

        enum PromoteType : unsigned int {
            Zero = 0b0000001,
            One = 0b0000010,
            Two = 0b0000100,
            Three = 0b0001000,
            Four = 0b0010000,
            Majority = 0b0100000,
            HalfOrMore = 0b1000000,
        };

        [[nodiscard]] BitsetBoard promote(PromoteType promoteType) const;

        static unsigned int sizeToBitsetSize(unsigned char size);

        static std::bitset<140> layerMask(unsigned char layerSize);

        static unsigned int layerShift(unsigned char layerSize);

        static std::bitset<140> rowMask(unsigned char layerSize, unsigned char rowIndex);

        static std::bitset<140> boardMask(unsigned char size);
    };
}

#endif //MOSAICGAME_BITSETBOARD_H
