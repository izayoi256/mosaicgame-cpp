#include "BitsetOneToOneGame.h"

#include <utility>
#include "Move/BitsetMove.h"

namespace MosaicGame::Game {

    BitsetOneToOneGame::BitsetOneToOneGame(unsigned char size, std::vector<BitsetMove> moves, bool mirrored,
                                           short rotations) :
            _size(size),
            _firstBoard(BitsetBoard::emptyBoard(size)),
            _secondBoard(BitsetBoard::emptyBoard(size)),
            _neutralBoard(BitsetBoard::neutralBoard(size)),
            _groundBoard(BitsetBoard::groundBoard(size)),
            _moves(std::move(moves)),
            _undoCount(0),
            _piecesPerPlayer(BitsetBoard::emptyBoard(size).flip().count() / 2),
            _mirrored(mirrored),
            _rotations(rotations) {
        this->replay();
    }

    BitsetOneToOneGame::BitsetOneToOneGame(unsigned char size) :
            BitsetOneToOneGame(size, std::vector<BitsetMove>{}, false, 0) {}

    unsigned char BitsetOneToOneGame::size() const {
        return this->_size;
    }

    unsigned short BitsetOneToOneGame::piecesPerPlayer() const {
        return this->_piecesPerPlayer;
    }

    unsigned short BitsetOneToOneGame::movesMade() const {
        return this->moves().size();
    }

    std::vector<BitsetMove> BitsetOneToOneGame::moves() const {
        return std::vector<BitsetMove>(this->_moves.begin(), this->_moves.end() - this->_undoCount);
    }

    std::vector<BitsetMove> BitsetOneToOneGame::legalMoves() const {
        return BitsetMove::fromBoard(this->legalBoard());
    }

    bool BitsetOneToOneGame::isOver() const {
        return this->firstWins() || this->secondWins();
    }

    unsigned short BitsetOneToOneGame::firstScore() const {
        return this->_firstBoard.count();
    }

    unsigned short BitsetOneToOneGame::secondScore() const {
        return this->_secondBoard.count();
    }

    unsigned short BitsetOneToOneGame::playerScore() const {
        return this->playerBoard().count();
    }

    unsigned short BitsetOneToOneGame::opponentScore() const {
        return this->opponentBoard().count();
    }

    bool BitsetOneToOneGame::firstWins() const {
        return this->_piecesPerPlayer <= this->_firstBoard.count();
    }

    bool BitsetOneToOneGame::secondWins() const {
        return this->_piecesPerPlayer <= this->_secondBoard.count();
    }

    bool BitsetOneToOneGame::playerWins() const {
        return this->_piecesPerPlayer <= this->playerBoard().count();
    }

    bool BitsetOneToOneGame::opponentWins() const {
        return this->_piecesPerPlayer <= this->opponentBoard().count();
    }

    bool BitsetOneToOneGame::isFirstTurn() const {
        return (this->movesMade() % 2 == 0);
    }

    bool BitsetOneToOneGame::isSecondTurn() const {
        return !this->isFirstTurn();
    }

    bool BitsetOneToOneGame::isLegalMove(const BitsetMove &move) const {
        return (this->legalBoard() & move.toBoard(this->_size)).count() > 0;
    }

    BitsetBoard BitsetOneToOneGame::firstBoard() const {
        return this->_firstBoard;
    }

    BitsetBoard BitsetOneToOneGame::secondBoard() const {
        return this->_secondBoard;
    }

    BitsetBoard BitsetOneToOneGame::neutralBoard() const {
        return this->_neutralBoard;
    }

    BitsetBoard BitsetOneToOneGame::legalBoard() const {
        return this->vacantBoard() & this->scaffoldedBoard();
    }

    BitsetBoard BitsetOneToOneGame::vacantBoard() const {
        return this->occupiedBoard().flip();
    }

    BitsetBoard BitsetOneToOneGame::scaffoldedBoard() const {
        return this->_groundBoard | this->occupiedBoard().promoteFour();
    }

    BitsetBoard BitsetOneToOneGame::occupiedBoard() const {
        return this->_neutralBoard | this->_firstBoard | this->_secondBoard;
    }

    BitsetBoard BitsetOneToOneGame::playerBoardAtMovesMade(unsigned short movesMade) const {
        return (movesMade & 1) == 0
            ? this->_firstBoard
            : this->_secondBoard;
    }

    BitsetBoard BitsetOneToOneGame::playerBoard() const {
        return this->playerBoardAtMovesMade(this->movesMade());
    }

    BitsetBoard BitsetOneToOneGame::opponentBoard() const {
        return this->playerBoardAtMovesMade(this->movesMade() + 1);
    }

    bool BitsetOneToOneGame::isUndoable() const {
        return this->_undoCount < this->_moves.size();
    }

    bool BitsetOneToOneGame::isRedoable() const {
        return this->_undoCount > 0;
    }

    void BitsetOneToOneGame::makeMove(const BitsetMove &move) {

        if (this->isOver()) {
            throw std::runtime_error("The game is already over.");
        }

        if (!this->isLegalMove(move)) {
            throw std::runtime_error("Making an illegal move is attempted.");
        }

        this->handleMove(move, this->movesMade());

        this->_moves = this->moves();
        this->_moves.emplace_back(this->normalizeMove(move));
        this->_undoCount = 0;
    }

    void BitsetOneToOneGame::handleMove(const BitsetMove &move, unsigned int movesMade) {

        if (movesMade % 2 == 0) {
            this->_firstBoard = this->_firstBoard | move.toBoard(this->_size);
        } else {
            this->_secondBoard = this->_secondBoard | move.toBoard(this->_size);
        }

        auto legalBoard = this->legalBoard();
        auto firstMajorityBoard = this->firstBoard().promoteMajority();
        auto secondMajorityBoard = this->secondBoard().promoteMajority();

        do {
            auto chained = false;
            BitsetBoard firstChainBoard = legalBoard & firstMajorityBoard;
            if (firstChainBoard.count()) {
                auto firstVacancy = this->_piecesPerPlayer - this->_firstBoard.count();
                if (firstChainBoard.count() <= firstVacancy) {
                    this->_firstBoard = this->_firstBoard | firstChainBoard;
                } else {
                    auto chainMoves = BitsetMove::fromBoard(firstChainBoard);
                    for (auto i = 0; i < firstVacancy; i++) {
                        BitsetMove chainMove = chainMoves.front();
                        chainMoves.erase(chainMoves.begin());
                        this->_firstBoard = this->_firstBoard | chainMove.toBoard(this->_size);
                    }
                }
                chained = true;
                legalBoard = this->legalBoard();
                firstMajorityBoard = this->firstBoard().promoteMajority();
            }

            BitsetBoard secondChainBoard = legalBoard & secondMajorityBoard;
            if (secondChainBoard.count()) {
                auto secondVacancy = this->_piecesPerPlayer - this->_secondBoard.count();
                if (secondChainBoard.count() <= secondVacancy) {
                    this->_secondBoard = this->_secondBoard | secondChainBoard;
                } else {
                    auto chainMoves = BitsetMove::fromBoard(secondChainBoard);
                    for (auto i = 0; i < secondVacancy; i++) {
                        BitsetMove chainMove = chainMoves.front();
                        chainMoves.erase(chainMoves.begin());
                        this->_secondBoard = this->_secondBoard | chainMove.toBoard(this->_size);
                    }
                }
                chained = true;
                legalBoard = this->legalBoard();
                secondMajorityBoard = this->secondBoard().promoteMajority();
            }

            if (!chained) {
                break;
            }
        } while (!this->isOver());
    }

    std::size_t BitsetOneToOneGame::state() const {
        return std::hash<std::string>{}(this->_firstBoard.toString() + this->_secondBoard.toString());
    }

    void BitsetOneToOneGame::undo() {
        if (!this->isUndoable()) {
            throw std::runtime_error("The game is not undoable.");
        }

        this->_undoCount++;
        this->replay();
    }

    void BitsetOneToOneGame::redo() {
        if (!this->isRedoable()) {
            throw std::runtime_error("The game is not redoable.");
        }

        this->_undoCount--;
        this->replay();
    }

    void BitsetOneToOneGame::replay() {
        this->resetBoards();
        auto movesMade = 0;
        for (const auto &move: this->moves()) {
            this->handleMove(this->transformMove(move), movesMade);
        }
    }

    void BitsetOneToOneGame::resetBoards() {
        this->_firstBoard = BitsetBoard::emptyBoard(this->_size);
        this->_secondBoard = BitsetBoard::emptyBoard(this->_size);
        this->_neutralBoard = BitsetBoard::neutralBoard(this->_size);
    }

    void BitsetOneToOneGame::flipVertical() {
        this->mirrored();
        this->rotated(2);
        this->_firstBoard = this->_firstBoard.flipVertical();
        this->_secondBoard = this->_secondBoard.flipVertical();
    }

    void BitsetOneToOneGame::mirrorHorizontal() {
        this->mirrored();
        this->_firstBoard = this->_firstBoard.mirrorHorizontal();
        this->_secondBoard = this->_secondBoard.mirrorHorizontal();
    }

    void BitsetOneToOneGame::flipDiagonal() {
        this->mirrored();
        this->rotated(1);
        this->_firstBoard = this->_firstBoard.flipDiagonal();
        this->_secondBoard = this->_secondBoard.flipDiagonal();
    }

    void BitsetOneToOneGame::rotate90() {
        this->rotated(1);
        this->_firstBoard = this->_firstBoard.rotate90();
        this->_secondBoard = this->_secondBoard.rotate90();
    }

    void BitsetOneToOneGame::rotate180() {
        this->rotated(2);
        this->_firstBoard = this->_firstBoard.rotate180();
        this->_secondBoard = this->_secondBoard.rotate180();
    }

    void BitsetOneToOneGame::rotate270() {
        this->rotated(3);
        this->_firstBoard = this->_firstBoard.rotate270();
        this->_secondBoard = this->_secondBoard.rotate270();
    }

    void BitsetOneToOneGame::transform() {
        auto minimumState = this->state();
        auto mirrored = this->_mirrored;
        auto rotations = this->_rotations;
        auto minimumFirstBoard = this->_firstBoard;
        auto minimumSecondBoard = this->_secondBoard;
        for (auto i = 0; i < 7; i++) {
            if (i == 3) {
                mirrorHorizontal();
            } else {
                rotate90();
            }
            auto newState = this->state();
            if (newState < minimumState) {
                minimumState = newState;
                mirrored = this->_mirrored;
                rotations = this->_rotations;
                minimumFirstBoard = this->_firstBoard;
                minimumSecondBoard = this->_secondBoard;
            }
        }
        this->_mirrored = mirrored;
        this->_rotations = rotations;
        this->_firstBoard = minimumFirstBoard;
        this->_secondBoard = minimumSecondBoard;
    }

    void BitsetOneToOneGame::resetTransformation() {
        switch (this->_rotations % 4) {
            case 1:
            case -3:
                this->rotate270();
                break;
            case 2:
            case -2:
                this->rotate180();
                break;
            case 3:
            case -1:
                this->rotate90();
                break;
        }
        if (this->_mirrored) {
            this->mirrorHorizontal();
        }
    }

    void BitsetOneToOneGame::mirrored() {
        this->_mirrored = !this->_mirrored;
        this->_rotations = -this->_rotations;
    }

    void BitsetOneToOneGame::rotated(int rotations) {
        this->_rotations = (this->_rotations + rotations) % 4;
    }

    BitsetMove BitsetOneToOneGame::normalizeMove(const BitsetMove &move) const {
        auto board = move.toBoard(this->_size);
        switch (this->_rotations % 4) {
            case 1:
                board = board.rotate270();
                break;
            case 2:
                board = board.rotate180();
                break;
            case 3:
                board = board.rotate90();
                break;
        }
        if (this->_mirrored) {
            board = board.mirrorHorizontal();
        }
        return BitsetMove::fromBoard(board).front();
    }

    BitsetMove BitsetOneToOneGame::transformMove(const BitsetMove &move) const {
        auto board = move.toBoard(this->_size);
        switch (this->_rotations % 4) {
            case 1:
                board = board.rotate90();
                break;
            case 2:
                board = board.rotate180();
                break;
            case 3:
                board = board.rotate270();
                break;
        }
        if (this->_mirrored) {
            board = board.mirrorHorizontal();
        }
        return BitsetMove::fromBoard(board).front();
    }
}