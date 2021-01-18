#ifndef MOSAICGAME_BITSETONETOONEGAME_H
#define MOSAICGAME_BITSETONETOONEGAME_H

#include "OneToOneGame.h"
#include "Move/BitsetMove.h"
#include "../Board/BitsetBoard.h"

using MosaicGame::Board::BitsetBoard;
using MosaicGame::Game::Move::BitsetMove;

namespace MosaicGame::Game {
    class BitsetOneToOneGame : public OneToOneGame<BitsetBoard, BitsetMove> {
    public:
        explicit BitsetOneToOneGame(unsigned char size, std::vector<BitsetMove> moves, bool mirrored, short rotations);

        explicit BitsetOneToOneGame(unsigned char size);

        [[nodiscard]] unsigned char size() const override;

        [[nodiscard]] unsigned short piecesPerPlayer() const override;

        [[nodiscard]] unsigned short movesMade() const override;

        [[nodiscard]] std::vector<BitsetMove> moves() const override;

        [[nodiscard]] std::vector<BitsetMove> legalMoves() const override;

        [[nodiscard]] bool isOver() const override;

        [[nodiscard]] unsigned short firstScore() const override;

        [[nodiscard]] unsigned short secondScore() const override;

        [[nodiscard]] unsigned short playerScore() const override;

        [[nodiscard]] unsigned short opponentScore() const override;

        [[nodiscard]] bool firstWins() const override;

        [[nodiscard]] bool secondWins() const override;

        [[nodiscard]] bool playerWins() const override;

        [[nodiscard]] bool opponentWins() const override;

        [[nodiscard]] bool isFirstTurn() const override;

        [[nodiscard]] bool isSecondTurn() const override;

        [[nodiscard]] bool isLegalMove(const BitsetMove &move) const override;

        [[nodiscard]] BitsetBoard firstBoard() const override;

        [[nodiscard]] BitsetBoard secondBoard() const override;

        [[nodiscard]] BitsetBoard playerBoard() const override;

        [[nodiscard]] BitsetBoard opponentBoard() const override;

        [[nodiscard]] BitsetBoard neutralBoard() const override;

        [[nodiscard]] BitsetBoard legalBoard() const override;

        [[nodiscard]] bool isUndoable() const override;

        [[nodiscard]] bool isRedoable() const override;

        [[nodiscard]] std::size_t state() const override;

        void makeMove(const BitsetMove &move) override;

        void undo() override;

        void redo() override;

        void flipVertical() override;

        void mirrorHorizontal() override;

        void flipDiagonal() override;

        void rotate90() override;

        void rotate180() override;

        void rotate270() override;

        void transform() override;

        void resetTransformation() override;

    private:
        const unsigned char _size;
        BitsetBoard _firstBoard;
        BitsetBoard _secondBoard;
        BitsetBoard _neutralBoard;
        BitsetBoard _groundBoard;
        std::vector<BitsetMove> _moves;
        unsigned int _undoCount;
        unsigned short _piecesPerPlayer;
        bool _mirrored;
        int _rotations;

    private:
        void replay();

        void resetBoards();

        void handleMove(const BitsetMove &move, unsigned int movesMade);

        [[nodiscard]] BitsetBoard playerBoardAtMovesMade(unsigned short movesMade) const;

        [[nodiscard]] BitsetBoard vacantBoard() const;

        [[nodiscard]] BitsetBoard occupiedBoard() const;

        [[nodiscard]] BitsetBoard scaffoldedBoard() const;

        [[nodiscard]] BitsetMove normalizeMove(const BitsetMove &move) const;

        [[nodiscard]] BitsetMove transformMove(const BitsetMove &move) const;

        void mirrored();

        void rotated(int rotations);
    };
}

#endif //MOSAICGAME_BITSETONETOONEGAME_H
