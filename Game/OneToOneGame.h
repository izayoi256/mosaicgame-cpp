#ifndef MOSAICGAME_ONETOONEGAME_H
#define MOSAICGAME_ONETOONEGAME_H

#include <vector>

namespace MosaicGame::Game {
    template<class BOARD, class MOVE>
    class OneToOneGame {
    public:
        [[nodiscard]] virtual unsigned char size() const = 0;

        [[nodiscard]] virtual unsigned short piecesPerPlayer() const = 0;

        [[nodiscard]] virtual unsigned short movesMade() const = 0;

        [[nodiscard]] virtual std::vector<MOVE> moves() const = 0;

        [[nodiscard]] virtual std::vector<MOVE> legalMoves() const = 0;

        [[nodiscard]] virtual bool isOver() const = 0;

        [[nodiscard]] virtual unsigned short firstScore() const = 0;

        [[nodiscard]] virtual unsigned short secondScore() const = 0;

        [[nodiscard]] virtual unsigned short playerScore() const = 0;

        [[nodiscard]] virtual unsigned short opponentScore() const = 0;

        [[nodiscard]] virtual bool firstWins() const = 0;

        [[nodiscard]] virtual bool secondWins() const = 0;

        [[nodiscard]] virtual bool playerWins() const = 0;

        [[nodiscard]] virtual bool opponentWins() const = 0;

        [[nodiscard]] virtual bool isFirstTurn() const = 0;

        [[nodiscard]] virtual bool isSecondTurn() const = 0;

        [[nodiscard]] virtual bool isLegalMove(const MOVE &move) const = 0;

        [[nodiscard]] virtual BOARD firstBoard() const = 0;

        [[nodiscard]] virtual BOARD secondBoard() const = 0;

        [[nodiscard]] virtual BOARD neutralBoard() const = 0;

        [[nodiscard]] virtual BOARD legalBoard() const = 0;

        [[nodiscard]] virtual BOARD playerBoard() const = 0;

        [[nodiscard]] virtual BOARD opponentBoard() const = 0;

        [[nodiscard]] virtual bool isUndoable() const = 0;

        [[nodiscard]] virtual bool isRedoable() const = 0;

        [[nodiscard]] virtual std::size_t state() const = 0;

        virtual void makeMove(const MOVE &move) = 0;

        virtual void undo() = 0;

        virtual void redo() = 0;

        virtual void flipVertical() = 0;

        virtual void mirrorHorizontal() = 0;

        virtual void flipDiagonal() = 0;

        virtual void rotate90() = 0;

        virtual void rotate180() = 0;

        virtual void rotate270() = 0;

        virtual void transform() = 0;

        virtual void resetTransformation() = 0;
    };
}

#endif //MOSAICGAME_ONETOONEGAME_H
