#ifndef MOSAICGAME_GMPBOARD_H
#define MOSAICGAME_GMPBOARD_H

#include "Board.h"
#include <gmpxx.h>
#include <unordered_map>

namespace MosaicGame::Board {
    class GMPBoard : public Board<GMPBoard> {
    public:
        explicit GMPBoard(unsigned char size, const mpz_class& mpz);

        explicit GMPBoard(unsigned int size, const std::string &mpzString);

        explicit GMPBoard(unsigned int size);

        static GMPBoard emptyBoard(unsigned char size);

        static GMPBoard groundBoard(unsigned char size);

        static GMPBoard neutralBoard(unsigned char size);

        [[nodiscard]] unsigned int size() const override;

        [[nodiscard]] std::string toString() const override;

        [[nodiscard]] unsigned int count() const override;

        [[nodiscard]] GMPBoard mirrorHorizontal() const override;

        [[nodiscard]] GMPBoard flipVertical() const override;

        [[nodiscard]] GMPBoard flipDiagonal() const override;

        [[nodiscard]] GMPBoard rotate90() const override;

        [[nodiscard]] GMPBoard rotate180() const override;

        [[nodiscard]] GMPBoard rotate270() const override;

        [[nodiscard]] bool operator==(const GMPBoard &other) const override;

        [[nodiscard]] GMPBoard operator&(const GMPBoard &other) const override;

        [[nodiscard]] GMPBoard operator|(const GMPBoard &other) const override;

        [[nodiscard]] GMPBoard operator^(const GMPBoard &other) const override;

        [[nodiscard]] GMPBoard operator<<(unsigned int amount) const override;

        [[nodiscard]] GMPBoard operator>>(unsigned int amount) const override;

        [[nodiscard]] GMPBoard flip() const override;

        [[nodiscard]] GMPBoard promoteZero() const override;

        [[nodiscard]] GMPBoard promoteOne() const override;

        [[nodiscard]] GMPBoard promoteTwo() const override;

        [[nodiscard]] GMPBoard promoteThree() const override;

        [[nodiscard]] GMPBoard promoteFour() const override;

        [[nodiscard]] GMPBoard promoteHalfOrMore() const override;

        [[nodiscard]] GMPBoard promoteMajority() const override;

    private:
        unsigned char _size;
        unsigned int _bitSize;
        mpz_class _mpz;
        static std::unordered_map<short, const mpz_class> _mirrorHorizontalMasks;
        static std::unordered_map<short, const mpz_class> _flipVerticalMasks;
        static std::unordered_map<short, const mpz_class> _flipDiagonalMasks;

        enum PromoteType : unsigned int {
            Zero = 0b0000001,
            One = 0b0000010,
            Two = 0b0000100,
            Three = 0b0001000,
            Four = 0b0010000,
            Majority = 0b0100000,
            HalfOrMore = 0b1000000,
        };

        [[nodiscard]] GMPBoard promote(PromoteType promoteType) const;

        static unsigned int sizeToBitSize(unsigned char size);

        static unsigned int layerShift(unsigned char layerSize);

        static mpz_class layerMaskMpz(unsigned char layerSize);

        static mpz_class rowMaskMpz(unsigned char layerSize, unsigned char rowIndex);
    };
}

#endif //MOSAICGAME_GMPBOARD_H
