#ifndef MOSAICGAME_GMPONETOONEGAME_H
#define MOSAICGAME_GMPONETOONEGAME_H

#include "OneToOneGame.h"
#include "Move/GMPMove.h"
#include "../Board/GMPBoard.h"

using MosaicGame::Board::GMPBoard;
using MosaicGame::Game::Move::GMPMove;

namespace MosaicGame::Game {
    class GMPOneToOneGame : public OneToOneGame<GMPBoard, GMPMove> {
    public:
        explicit GMPOneToOneGame(unsigned char size, std::vector<GMPMove> moves, bool mirrored, short rotations);

        explicit GMPOneToOneGame(unsigned char size);

        [[nodiscard]] unsigned char size() const override;

        [[nodiscard]] unsigned short piecesPerPlayer() const override;

        [[nodiscard]] unsigned short movesMade() const override;

        [[nodiscard]] std::vector<GMPMove> moves() const override;

        [[nodiscard]] std::vector<GMPMove> legalMoves() const override;

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

        [[nodiscard]] bool isLegalMove(const GMPMove &move) const override;

        [[nodiscard]] GMPBoard firstBoard() const override;

        [[nodiscard]] GMPBoard secondBoard() const override;

        [[nodiscard]] GMPBoard playerBoard() const override;

        [[nodiscard]] GMPBoard opponentBoard() const override;

        [[nodiscard]] GMPBoard neutralBoard() const override;

        [[nodiscard]] GMPBoard legalBoard() const override;

        [[nodiscard]] bool isUndoable() const override;

        [[nodiscard]] bool isRedoable() const override;

        [[nodiscard]] std::size_t state() const override;

        void makeMove(const GMPMove &move) override;

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
        GMPBoard _firstBoard;
        GMPBoard _secondBoard;
        GMPBoard _neutralBoard;
        GMPBoard _groundBoard;
        std::vector<GMPMove> _moves;
        unsigned int _undoCount;
        unsigned short _piecesPerPlayer;
        bool _mirrored;
        int _rotations;

    private:
        void replay();

        void resetBoards();

        void handleMove(const GMPMove &move, unsigned int movesMade);

        [[nodiscard]] GMPBoard playerBoardAtMovesMade(unsigned short movesMade) const;

        [[nodiscard]] GMPBoard vacantBoard() const;

        [[nodiscard]] GMPBoard occupiedBoard() const;

        [[nodiscard]] GMPBoard scaffoldedBoard() const;

        [[nodiscard]] GMPMove normalizeMove(const GMPMove &move) const;

        [[nodiscard]] GMPMove transformMove(const GMPMove &move) const;

        void mirrored();

        void rotated(int rotations);
    };
}

#endif //MOSAICGAME_GMPONETOONEGAME_H
