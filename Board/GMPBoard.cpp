#include <gmpxx.h>
#include <unordered_map>

#include "GMPBoard.h"

using MosaicGame::Board::Board;
using MosaicGame::Board::GMPBoard;

namespace MosaicGame::Board {

    GMPBoard::GMPBoard(unsigned char size, const mpz_class &mpz) :
            _size(size),
            _bitSize(GMPBoard::sizeToBitSize(size)),
            _mpz(
                    (mpz_scan1(mpz.get_mpz_t(), this->_bitSize) != -1)
                    ? mpz & mpz_class(std::string(GMPBoard::sizeToBitSize(size), '1'), 2)
                    : mpz
            ) {}

    GMPBoard::GMPBoard(unsigned int size, const std::string &mpzString) :
            GMPBoard(size, mpz_class(mpzString, 2)) {}

    GMPBoard::GMPBoard(unsigned int size) : GMPBoard(size, "0") {}

    GMPBoard GMPBoard::emptyBoard(unsigned char size) {
        return GMPBoard(size);
    }

    GMPBoard GMPBoard::groundBoard(unsigned char size) {
        return GMPBoard(size, GMPBoard::layerMaskMpz(size));
    }

    GMPBoard GMPBoard::neutralBoard(unsigned char size) {
        if (size % 2 == 1) {
            auto mpz = mpz_class(1);
            for (auto i = 1; i < size; i++) {
                mpz <<= (i * i);
            }
            mpz <<= (size * size / 2);
            return GMPBoard(size, mpz);
        } else {
            return GMPBoard::emptyBoard(size);
        }
    }

    unsigned int GMPBoard::size() const {
        return this->_size;
    }

    std::string GMPBoard::toString() const {
        auto result = this->_mpz.get_str(2);
        auto length = result.length();
        if (length > this->_bitSize) {
            return result.substr(length - this->_bitSize);
        } else if (length == this->_bitSize) {
            return result;
        } else {
            result.insert(result.begin(), this->_bitSize - length, '0');
            return result;
        }
    }

    unsigned int GMPBoard::count() const {
        return mpz_popcount(this->_mpz.get_mpz_t());
    }

    std::unordered_map<short, const mpz_class> GMPBoard::_mirrorHorizontalMasks = {
            {0, mpz_class("10000001000000100000010000001000000100000010000000000000000000000000000000000000000010000100001000010000100000000000000000001001001000001", 2)},
            {1, mpz_class("10000010000010000010000010000010000000000000000000000000000010001000100010000000000010100", 2)},
            {-1, mpz_class("1000001000001000001000001000001000000000000000000000000000001000100010001000000000001010", 2)},
            {2, mpz_class("100000010000001000000100000010000001000000100000000000000000000000000000000000000000100001000010000100001000000000000000000010010010000000", 2)},
            {-2, mpz_class("1000000100000010000001000000100000010000001000000000000000000000000000000000000000001000010000100001000010000000000000000000100100100000", 2)},
            {3, mpz_class("100000100000100000100000100000100000000000000000000000000000100010001000100000000000000000", 2)},
            {-3, mpz_class("100000100000100000100000100000100000000000000000000000000000100010001000100000000000000", 2)},
            {4, mpz_class("1000000100000010000001000000100000010000001000000000000000000000000000000000000000001000010000100001000010000000000000000000000000000000000", 2)},
            {-4, mpz_class("100000010000001000000100000010000001000000100000000000000000000000000000000000000000100001000010000100001000000000000000000000000000000", 2)},
            {5, mpz_class("1000001000001000001000001000001000000000000000000000000000000000000000000000000000000000000", 2)},
            {-5, mpz_class("10000010000010000010000010000010000000000000000000000000000000000000000000000000000000", 2)},
            {6, mpz_class("10000001000000100000010000001000000100000010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", 2)},
            {-6, mpz_class("10000001000000100000010000001000000100000010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", 2)},
    };

    GMPBoard GMPBoard::mirrorHorizontal() const {
        auto result = mpz_class(0);
        for (const auto &mirrorHorizontalMask : GMPBoard::_mirrorHorizontalMasks) {
            auto shift = mirrorHorizontalMask.first;
            auto mask = mirrorHorizontalMask.second;
            if (shift < 0) {
                result = result | (mask & (this->_mpz >> abs(shift)));
            } else {
                result = result | (mask & (this->_mpz << shift));
            }
        }
        return GMPBoard(this->_size, result);
    }

    std::unordered_map<short, const mpz_class> GMPBoard::_flipVerticalMasks = {
            {0, mpz_class("11111110000000000000000000000000000000000000000000000000000000000000000000111110000000000000000000000000000011100000001", 2)},
            {-2, mpz_class("110", 2)},
            {2, mpz_class("11000", 2)},
            {-6, mpz_class("1111110000000000000000000000000000000000000000000000000000000000011100000", 2)},
            {6, mpz_class("1111110000000000000000000000000000000000000000000000000000000000011100000000000", 2)},
            {-12, mpz_class("111100000000000000", 2)},
            {-4, mpz_class("1111000000000000000000", 2)},
            {4, mpz_class("11110000000000000000000000", 2)},
            {12, mpz_class("111100000000000000000000000000", 2)},
            {-20, mpz_class("11111000000000000000000000000000000", 2)},
            {-10, mpz_class("1111100000000000000000000000000000000000", 2)},
            {10, mpz_class("11111000000000000000000000000000000000000000000000", 2)},
            {20, mpz_class("1111100000000000000000000000000000000000000000000000000", 2)},
            {-30, mpz_class("1111110000000000000000000000000000000000000000000000000000000", 2)},
            {-18, mpz_class("1111110000000000000000000000000000000000000000000000000000000000000", 2)},
            {18, mpz_class("1111110000000000000000000000000000000000000000000000000000000000000000000000000000000", 2)},
            {30, mpz_class("1111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000", 2)},
            {-42, mpz_class("11111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", 2)},
            {-28, mpz_class("111111100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", 2)},
            {-14, mpz_class("1111111000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", 2)},
            {14, mpz_class("111111100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", 2)},
            {28, mpz_class("1111111000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", 2)},
            {42, mpz_class("11111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", 2)},
    };

    GMPBoard GMPBoard::flipVertical() const {
        auto result = mpz_class(0);
        for (const auto &flipVerticalMask : GMPBoard::_flipVerticalMasks) {
            auto shift = flipVerticalMask.first;
            auto mask = flipVerticalMask.second;
            if (shift < 0) {
                result = result | (mask & (this->_mpz >> abs(shift)));
            } else {
                result = result | (mask & (this->_mpz << shift));
            }
        }
        return GMPBoard(this->_size, result);
    }

    std::unordered_map<short, const mpz_class> GMPBoard::_flipDiagonalMasks = {
            {0, mpz_class("10000010000010000010000010000010000010000000000010000100001000010000100001000000000100010001000100010000000100100100100000101010001101", 2)},
            {3, mpz_class("10000", 2)},
            {-3, mpz_class("10", 2)},
            {4, mpz_class("1010000000000", 2)},
            {-4, mpz_class("101000000", 2)},
            {8, mpz_class("100000100000100000100000100000100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010000000000000", 2)},
            {-8, mpz_class("1000001000001000001000001000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000100000", 2)},
            {5, mpz_class("1001001000000000000000000000", 2)},
            {-5, mpz_class("10010010000000000000000", 2)},
            {10, mpz_class("10010000000000000000000000000", 2)},
            {-10, mpz_class("1001000000000000000", 2)},
            {15, mpz_class("100000000000000000000000000000", 2)},
            {-15, mpz_class("100000000000000", 2)},
            {6, mpz_class("1000100010001000000000000000000000000000000000000000", 2)},
            {-6, mpz_class("1000100010001000000000000000000000000000000000", 2)},
            {12, mpz_class("10001000100000000000000000000000000000000000000000000", 2)},
            {-12, mpz_class("10001000100000000000000000000000000000000", 2)},
            {18, mpz_class("100010000000000000000000000000000000000000000000000000", 2)},
            {-18, mpz_class("100010000000000000000000000000000000", 2)},
            {24, mpz_class("10000010000010000010000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000", 2)},
            {-24, mpz_class("10000010000010000010000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000", 2)},
            {7, mpz_class("100001000010000100001000000000000000000000000000000000000000000000000000000000000000000", 2)},
            {-7, mpz_class("10000100001000010000100000000000000000000000000000000000000000000000000000000000", 2)},
            {14, mpz_class("1000010000100001000000000000000000000000000000000000000000000000000000000000000000000000", 2)},
            {-14, mpz_class("10000100001000010000000000000000000000000000000000000000000000000000000000", 2)},
            {21, mpz_class("10000100001000000000000000000000000000000000000000000000000000000000000000000000000000000", 2)},
            {-21, mpz_class("10000100001000000000000000000000000000000000000000000000000000000000", 2)},
            {28, mpz_class("100001000000000000000000000000000000000000000000000000000000000000000000000000000000000000", 2)},
            {-28, mpz_class("10000100000000000000000000000000000000000000000000000000000000", 2)},
            {35, mpz_class("1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", 2)},
            {-35, mpz_class("10000000000000000000000000000000000000000000000000000000", 2)},
            {16, mpz_class("1000001000001000001000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", 2)},
            {-16, mpz_class("100000100000100000100000100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", 2)},
            {32, mpz_class("100000100000100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", 2)},
            {-32, mpz_class("1000001000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", 2)},
            {40, mpz_class("1000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", 2)},
            {-40, mpz_class("100000100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", 2)},
            {48, mpz_class("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", 2)},
            {-48, mpz_class("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", 2)},
    };

    GMPBoard GMPBoard::flipDiagonal() const {
        auto result = mpz_class(0);
        for (const auto &flipDiagonalMask : GMPBoard::_flipDiagonalMasks) {
            auto shift = flipDiagonalMask.first;
            auto mask = flipDiagonalMask.second;
            if (shift < 0) {
                result = result | (mask & (this->_mpz >> abs(shift)));
            } else {
                result = result | (mask & (this->_mpz << shift));
            }
        }
        return GMPBoard(this->_size, result);
    }

    GMPBoard GMPBoard::rotate90() const {
        return this->flipDiagonal().flipVertical();
    }

    GMPBoard GMPBoard::rotate180() const {
        return this->mirrorHorizontal().flipVertical();
    }

    GMPBoard GMPBoard::rotate270() const {
        return this->flipVertical().flipDiagonal();
    }

    GMPBoard GMPBoard::promoteZero() const {
        return this->promote(PromoteType::Zero);
    }

    GMPBoard GMPBoard::promoteOne() const {
        return this->promote(PromoteType::One);
    }

    GMPBoard GMPBoard::promoteTwo() const {
        return this->promote(PromoteType::Two);
    }

    GMPBoard GMPBoard::promoteThree() const {
        return this->promote(PromoteType::Three);
    }

    GMPBoard GMPBoard::promoteFour() const {
        return this->promote(PromoteType::Four);
    }

    GMPBoard GMPBoard::promoteHalfOrMore() const {
        return this->promote(PromoteType::HalfOrMore);
    }

    GMPBoard GMPBoard::promoteMajority() const {
        return this->promote(PromoteType::Majority);
    }

    GMPBoard GMPBoard::promote(const GMPBoard::PromoteType promoteType) const {
        auto result = GMPBoard(this->_size);
        for (auto srcLayerSize = this->_size; srcLayerSize > 1; srcLayerSize--) {
            unsigned int dstLayerSize = srcLayerSize - 1;
            GMPBoard srcLayerMask = GMPBoard(this->_size, GMPBoard::layerMaskMpz(srcLayerSize));
            GMPBoard srcLayer = *this & srcLayerMask;
            GMPBoard promotionLayer = GMPBoard(this->_size);

            if (promoteType & (PromoteType::Zero | PromoteType::One)) {
                srcLayer = srcLayer.flip() & srcLayerMask;
            }

            if (promoteType & (PromoteType::Zero | PromoteType::Four)) {
                auto p = srcLayer & (srcLayer >> 1);
                p = p & (p >> srcLayerSize);
                promotionLayer = promotionLayer | p;
            }

            if (promoteType & (PromoteType::One | PromoteType::Three)) {
                auto p1 = srcLayer & (srcLayer >> 1);
                p1 = p1 ^ (p1 >> srcLayerSize);
                auto p2 = srcLayer ^(srcLayer >> 1);
                p2 = p2 ^ (p2 >> srcLayerSize);
                promotionLayer = promotionLayer | (p1 & p2);
            }

            if (promoteType & PromoteType::Two) {
                auto p1 = srcLayer ^(srcLayer >> 1);
                p1 = p1 & (p1 >> srcLayerSize);
                auto p2 = srcLayer ^(srcLayer >> srcLayerSize);
                p2 = p2 & (p2 >> 1);
                promotionLayer = promotionLayer | p1 | p2;
            }

            if (promoteType & PromoteType::Majority) {
                auto p1 = srcLayer & (srcLayer >> 1);
                p1 = p1 | (p1 >> srcLayerSize);
                auto p2 = srcLayer & (srcLayer >> srcLayerSize);
                p2 = p2 | (p2 >> 1);
                promotionLayer = promotionLayer | (p1 & p2);
            }

            if (promoteType & PromoteType::HalfOrMore) {
                auto p1 = srcLayer | (srcLayer >> 1);
                p1 = p1 & (p1 >> srcLayerSize);
                auto p2 = srcLayer | (srcLayer >> srcLayerSize);
                p2 = p2 & (p2 >> 1);
                promotionLayer = promotionLayer | p1 | p2;
            }

            for (auto i = 0; i < dstLayerSize; i++) {
                auto rowMask = GMPBoard(this->_size, GMPBoard::rowMaskMpz(dstLayerSize, i));
                auto promotionRow = promotionLayer & rowMask;
                promotionRow = promotionRow >> (dstLayerSize * dstLayerSize + i);
                result = result | promotionRow;
            }
        }
        return result;
    }

    bool GMPBoard::operator==(const GMPBoard &other) const {
        return this->_mpz == other._mpz;
    }

    GMPBoard GMPBoard::operator&(const GMPBoard &other) const {
        return GMPBoard(this->_size, this->_mpz & other._mpz);
    }

    GMPBoard GMPBoard::operator|(const GMPBoard &other) const {
        return GMPBoard(this->_size, this->_mpz | other._mpz);
    }

    GMPBoard GMPBoard::operator^(const GMPBoard &other) const {
        return GMPBoard(this->_size, this->_mpz ^ other._mpz);
    }

    GMPBoard GMPBoard::operator<<(unsigned int amount) const {
        return GMPBoard(this->_size, this->_mpz << amount);
    }

    GMPBoard GMPBoard::operator>>(unsigned int amount) const {
        return GMPBoard(this->_size, this->_mpz >> amount);
    }

    GMPBoard GMPBoard::flip() const {
        mpz_class newMpz;
        mpz_neg(newMpz.get_mpz_t(), this->_mpz.get_mpz_t());
        return GMPBoard(this->_size, newMpz - 1);
    }

    unsigned int GMPBoard::sizeToBitSize(unsigned char size) {
        unsigned int bitSize = 0;
        for (auto i = 1; i <= size; i++) {
            bitSize += i * i;
        }
        return bitSize;
    }

    unsigned int GMPBoard::layerShift(unsigned char layerSize) {
        unsigned int layerShift = 0;
        for (auto i = 0; i < layerSize; i++) {
            layerShift += i * i;
        }
        return layerShift;
    }

    mpz_class GMPBoard::layerMaskMpz(unsigned char layerSize) {
        auto mpzString = std::string(layerSize * layerSize, '1');
        auto mpz = mpz_class(mpzString, 2);
        mpz = mpz << GMPBoard::layerShift(layerSize);
        return mpz;
    }

    mpz_class GMPBoard::rowMaskMpz(unsigned char layerSize, unsigned char rowIndex) {
        auto result = mpz_class(std::string(layerSize, '1'), 2);
        result = result << GMPBoard::layerShift(layerSize + 1);
        result = result << ((layerSize + 1) * rowIndex);
        return result;
    }
}
