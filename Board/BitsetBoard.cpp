#include <bitset>
#include <memory>
#include <unordered_map>

#include "BitsetBoard.h"

namespace MosaicGame::Board {

    BitsetBoard::BitsetBoard(unsigned char size, const std::bitset<140> &bitset) :
            _size(size),
            _bitSize(BitsetBoard::sizeToBitsetSize(size)),
            _bitset(bitset) {
        if (this->_bitSize < 140) {
            this->_bitset &= BitsetBoard::boardMask(this->_size);
        }
    }

    BitsetBoard::BitsetBoard(unsigned int size, const std::string &bitsetString) :
            BitsetBoard(
                    size,
                    std::bitset<140>(bitsetString)
            ) {}

    BitsetBoard::BitsetBoard(unsigned int size) :
            BitsetBoard(
                    size,
                    std::bitset<140>(0)
            ) {}

    BitsetBoard BitsetBoard::emptyBoard(unsigned char size) {
        return BitsetBoard(size);
    }

    std::unordered_map<unsigned char, std::shared_ptr<BitsetBoard>> BitsetBoard::_neutralBoards = {};

    BitsetBoard BitsetBoard::neutralBoard(unsigned char size) {
        if (!BitsetBoard::_neutralBoards.count(size)) {
            if (size % 2 == 1) {
                auto bitset = std::bitset<140>(1);
                for (auto i = 1; i < size; i++) {
                    bitset <<= (i * i);
                }
                bitset <<= (size * size / 2);
                BitsetBoard::_neutralBoards[size] = std::make_shared<BitsetBoard>(size, bitset);
            } else {
                BitsetBoard::_neutralBoards[size] = std::make_shared<BitsetBoard>(size);
            }
        }
        return *BitsetBoard::_neutralBoards[size];
    }

    std::unordered_map<unsigned char, std::shared_ptr<BitsetBoard>> BitsetBoard::_groundBoards = {};

    BitsetBoard BitsetBoard::groundBoard(unsigned char size) {
        if (!BitsetBoard::_groundBoards.count(size)) {
            BitsetBoard::_groundBoards[size] = std::make_shared<BitsetBoard>(size, BitsetBoard::layerMask(size));
        }
        return *BitsetBoard::_groundBoards[size];
    }

    unsigned int BitsetBoard::size() const {
        return this->_size;
    }

    std::string BitsetBoard::toString() const {
        auto result = this->_bitset.to_string();
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

    unsigned int BitsetBoard::count() const {
        return this->_bitset.count();
    }

    std::unordered_map<short, std::bitset<140>> BitsetBoard::_mirrorHorizontalMasks = {
            {0, std::bitset<140>("10000001000000100000010000001000000100000010000000000000000000000000000000000000000010000100001000010000100000000000000000001001001000001")},
            {1, std::bitset<140>("10000010000010000010000010000010000000000000000000000000000010001000100010000000000010100")},
            {-1, std::bitset<140>("1000001000001000001000001000001000000000000000000000000000001000100010001000000000001010")},
            {2, std::bitset<140>("100000010000001000000100000010000001000000100000000000000000000000000000000000000000100001000010000100001000000000000000000010010010000000")},
            {-2, std::bitset<140>("1000000100000010000001000000100000010000001000000000000000000000000000000000000000001000010000100001000010000000000000000000100100100000")},
            {3, std::bitset<140>("100000100000100000100000100000100000000000000000000000000000100010001000100000000000000000")},
            {-3, std::bitset<140>("100000100000100000100000100000100000000000000000000000000000100010001000100000000000000")},
            {4, std::bitset<140>("1000000100000010000001000000100000010000001000000000000000000000000000000000000000001000010000100001000010000000000000000000000000000000000")},
            {-4, std::bitset<140>("100000010000001000000100000010000001000000100000000000000000000000000000000000000000100001000010000100001000000000000000000000000000000")},
            {5, std::bitset<140>("1000001000001000001000001000001000000000000000000000000000000000000000000000000000000000000")},
            {-5, std::bitset<140>("10000010000010000010000010000010000000000000000000000000000000000000000000000000000000")},
            {6, std::bitset<140>("10000001000000100000010000001000000100000010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000")},
            {-6, std::bitset<140>("10000001000000100000010000001000000100000010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000")},
    };

    BitsetBoard BitsetBoard::mirrorHorizontal() const {
        auto result = std::bitset<140>(0);
        for (const auto &mirrorHorizontalMask : BitsetBoard::_mirrorHorizontalMasks) {
            auto shift = mirrorHorizontalMask.first;
            auto mask = mirrorHorizontalMask.second;
            if (shift < 0) {
                result = result | (mask & (this->_bitset >> abs(shift)));
            } else {
                result = result | (mask & (this->_bitset << shift));
            }
        }
        return BitsetBoard(this->_size, result);
    }

    std::unordered_map<short, std::bitset<140>> BitsetBoard::_flipVerticalMasks = {
            {0, std::bitset<140>("11111110000000000000000000000000000000000000000000000000000000000000000000111110000000000000000000000000000011100000001")},
            {-2, std::bitset<140>("110")},
            {2, std::bitset<140>("11000")},
            {-6, std::bitset<140>("1111110000000000000000000000000000000000000000000000000000000000011100000")},
            {6, std::bitset<140>("1111110000000000000000000000000000000000000000000000000000000000011100000000000")},
            {-12, std::bitset<140>("111100000000000000")},
            {-4, std::bitset<140>("1111000000000000000000")},
            {4, std::bitset<140>("11110000000000000000000000")},
            {12, std::bitset<140>("111100000000000000000000000000")},
            {-20, std::bitset<140>("11111000000000000000000000000000000")},
            {-10, std::bitset<140>("1111100000000000000000000000000000000000")},
            {10, std::bitset<140>("11111000000000000000000000000000000000000000000000")},
            {20, std::bitset<140>("1111100000000000000000000000000000000000000000000000000")},
            {-30, std::bitset<140>("1111110000000000000000000000000000000000000000000000000000000")},
            {-18, std::bitset<140>("1111110000000000000000000000000000000000000000000000000000000000000")},
            {18, std::bitset<140>("1111110000000000000000000000000000000000000000000000000000000000000000000000000000000")},
            {30, std::bitset<140>("1111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000")},
            {-42, std::bitset<140>("11111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000")},
            {-28, std::bitset<140>("111111100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000")},
            {-14, std::bitset<140>("1111111000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000")},
            {14, std::bitset<140>("111111100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000")},
            {28, std::bitset<140>("1111111000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000")},
            {42, std::bitset<140>("11111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000")},
    };

    BitsetBoard BitsetBoard::flipVertical() const {
        auto result = std::bitset<140>(0);
        for (const auto &flipVerticalMask : BitsetBoard::_flipVerticalMasks) {
            auto shift = flipVerticalMask.first;
            auto mask = flipVerticalMask.second;
            if (shift < 0) {
                result = result | (mask & (this->_bitset >> abs(shift)));
            } else {
                result = result | (mask & (this->_bitset << shift));
            }
        }
        return BitsetBoard(this->_size, result);
    }

    std::unordered_map<short, std::bitset<140>> BitsetBoard::_flipDiagonalMasks = {
            {0, std::bitset<140>("10000010000010000010000010000010000010000000000010000100001000010000100001000000000100010001000100010000000100100100100000101010001101")},
            {3, std::bitset<140>("10000")},
            {-3, std::bitset<140>("10")},
            {4, std::bitset<140>("1010000000000")},
            {-4, std::bitset<140>("101000000")},
            {8, std::bitset<140>("100000100000100000100000100000100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010000000000000")},
            {-8, std::bitset<140>("1000001000001000001000001000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000100000")},
            {5, std::bitset<140>("1001001000000000000000000000")},
            {-5, std::bitset<140>("10010010000000000000000")},
            {10, std::bitset<140>("10010000000000000000000000000")},
            {-10, std::bitset<140>("1001000000000000000")},
            {15, std::bitset<140>("100000000000000000000000000000")},
            {-15, std::bitset<140>("100000000000000")},
            {6, std::bitset<140>("1000100010001000000000000000000000000000000000000000")},
            {-6, std::bitset<140>("1000100010001000000000000000000000000000000000")},
            {12, std::bitset<140>("10001000100000000000000000000000000000000000000000000")},
            {-12, std::bitset<140>("10001000100000000000000000000000000000000")},
            {18, std::bitset<140>("100010000000000000000000000000000000000000000000000000")},
            {-18, std::bitset<140>("100010000000000000000000000000000000")},
            {24, std::bitset<140>("10000010000010000010000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000")},
            {-24, std::bitset<140>("10000010000010000010000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000")},
            {7, std::bitset<140>("100001000010000100001000000000000000000000000000000000000000000000000000000000000000000")},
            {-7, std::bitset<140>("10000100001000010000100000000000000000000000000000000000000000000000000000000000")},
            {14, std::bitset<140>("1000010000100001000000000000000000000000000000000000000000000000000000000000000000000000")},
            {-14, std::bitset<140>("10000100001000010000000000000000000000000000000000000000000000000000000000")},
            {21, std::bitset<140>("10000100001000000000000000000000000000000000000000000000000000000000000000000000000000000")},
            {-21, std::bitset<140>("10000100001000000000000000000000000000000000000000000000000000000000")},
            {28, std::bitset<140>("100001000000000000000000000000000000000000000000000000000000000000000000000000000000000000")},
            {-28, std::bitset<140>("10000100000000000000000000000000000000000000000000000000000000")},
            {35, std::bitset<140>("1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000")},
            {-35, std::bitset<140>("10000000000000000000000000000000000000000000000000000000")},
            {16, std::bitset<140>("1000001000001000001000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000")},
            {-16, std::bitset<140>("100000100000100000100000100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000")},
            {32, std::bitset<140>("100000100000100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000")},
            {-32, std::bitset<140>("1000001000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000")},
            {40, std::bitset<140>("1000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000")},
            {-40, std::bitset<140>("100000100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000")},
            {48, std::bitset<140>("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000")},
            {-48, std::bitset<140>("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000")},
    };

    BitsetBoard BitsetBoard::flipDiagonal() const {
        auto result = std::bitset<140>(0);
        for (const auto &flipDiagonalMask : BitsetBoard::_flipDiagonalMasks) {
            auto shift = flipDiagonalMask.first;
            auto mask = flipDiagonalMask.second;
            if (shift < 0) {
                result = result | (mask & (this->_bitset >> abs(shift)));
            } else {
                result = result | (mask & (this->_bitset << shift));
            }
        }
        return BitsetBoard(this->_size, result);
    }

    BitsetBoard BitsetBoard::rotate90() const {
        return this->flipDiagonal().flipVertical();
    }

    BitsetBoard BitsetBoard::rotate180() const {
        return this->mirrorHorizontal().flipVertical();
    }

    BitsetBoard BitsetBoard::rotate270() const {
        return this->flipVertical().flipDiagonal();
    }

    BitsetBoard BitsetBoard::promoteZero() const {
        return this->promote(PromoteType::Zero);
    }

    BitsetBoard BitsetBoard::promoteOne() const {
        return this->promote(PromoteType::One);
    }

    BitsetBoard BitsetBoard::promoteTwo() const {
        return this->promote(PromoteType::Two);
    }

    BitsetBoard BitsetBoard::promoteThree() const {
        return this->promote(PromoteType::Three);
    }

    BitsetBoard BitsetBoard::promoteFour() const {
        return this->promote(PromoteType::Four);
    }

    BitsetBoard BitsetBoard::promoteHalfOrMore() const {
        return this->promote(PromoteType::HalfOrMore);
    }

    BitsetBoard BitsetBoard::promoteMajority() const {
        return this->promote(PromoteType::Majority);
    }

    BitsetBoard BitsetBoard::promote(const BitsetBoard::PromoteType promoteType) const {
        auto result = BitsetBoard::emptyBoard(this->_size);
        for (auto srcLayerSize = this->_size; srcLayerSize > 1; srcLayerSize--) {
            unsigned int dstLayerSize = srcLayerSize - 1;
            BitsetBoard srcLayerMask = BitsetBoard(this->_size, BitsetBoard::layerMask(srcLayerSize));
            BitsetBoard srcLayer = *this & srcLayerMask;
            auto promotionLayer = BitsetBoard::emptyBoard(this->_size);

            if (promoteType & (PromoteType::Zero | PromoteType::One)) {
                srcLayer = srcLayer.flip() & srcLayerMask;
            }

            if (srcLayer.count() == 0) {
                continue;
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

            if (promotionLayer.count() == 0) {
                continue;
            }

            for (auto i = 0; i < dstLayerSize; i++) {
                auto rowMask = BitsetBoard(this->_size, BitsetBoard::rowMask(dstLayerSize, i));
                auto promotionRow = promotionLayer & rowMask;
                if (promotionRow.count() == 0) {
                    continue;
                }
                promotionRow = promotionRow >> (dstLayerSize * dstLayerSize + i);
                result = result | promotionRow;
            }
        }
        return result;
    }

    bool BitsetBoard::operator==(const BitsetBoard &other) const {
        return this->_bitset == other._bitset;
    }

    BitsetBoard BitsetBoard::operator&(const BitsetBoard &other) const {
        return BitsetBoard(this->_size, this->_bitset & other._bitset);
    }

    BitsetBoard BitsetBoard::operator|(const BitsetBoard &other) const {
        return BitsetBoard(this->_size, this->_bitset | other._bitset);
    }

    BitsetBoard BitsetBoard::operator^(const BitsetBoard &other) const {
        return BitsetBoard(this->_size, this->_bitset ^ other._bitset);
    }

    BitsetBoard BitsetBoard::operator<<(unsigned int amount) const {
        return BitsetBoard(this->_size, this->_bitset << amount);
    }

    BitsetBoard BitsetBoard::operator>>(unsigned int amount) const {
        return BitsetBoard(this->_size, this->_bitset >> amount);
    }

    BitsetBoard BitsetBoard::flip() const {
        auto bitset = this->_bitset;
        return BitsetBoard(this->_size, bitset.flip());
    }

    unsigned int BitsetBoard::sizeToBitsetSize(unsigned char size) {
        unsigned int bitSetSize = 0;
        for (auto i = 1; i <= size; i++) {
            bitSetSize += i * i;
        }
        return bitSetSize;
    }

    unsigned int BitsetBoard::layerShift(unsigned char layerSize) {
        unsigned int layerShift = 0;
        for (auto i = 0; i < layerSize; i++) {
            layerShift += i * i;
        }
        return layerShift;
    }

    std::bitset<140> BitsetBoard::layerMask(unsigned char layerSize) {
        auto bitset = std::bitset<140>(0);
        const auto j = layerSize * layerSize;
        for (auto i = 0; i < j; i++) {
            bitset.set(i);
        }
        bitset <<= BitsetBoard::layerShift(layerSize);
        return bitset;
    }

    std::bitset<140> BitsetBoard::rowMask(unsigned char layerSize, unsigned char rowIndex) {
        auto result = std::bitset<140>(std::string(layerSize, '1'));
        result <<= BitsetBoard::layerShift(layerSize + 1);
        result <<= ((layerSize + 1) * rowIndex);
        return result;
    }

    std::unordered_map<unsigned char, std::bitset<140>> BitsetBoard::_boardMasks = {};

    std::bitset<140> BitsetBoard::boardMask(unsigned char size) {
        if (BitsetBoard::_boardMasks.count(size) < 1) {
            auto bitset = std::bitset<140>(0);
            for (unsigned int i = 1; i <= size; i++) {
                bitset |= BitsetBoard::layerMask(i);
            }
            BitsetBoard::_boardMasks[size] = bitset;
        }
        return BitsetBoard::_boardMasks[size];
    }
}
