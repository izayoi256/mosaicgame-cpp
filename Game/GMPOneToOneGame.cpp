#include "GMPOneToOneGame.h"

#include <utility>
#include "Move/GMPMove.h"

namespace MosaicGame::Game {

    GMPOneToOneGame::GMPOneToOneGame(unsigned char size, std::vector<GMPMove> moves, bool mirrored,
                                           short rotations) :
            _size(size),
            _firstBoard(GMPBoard::emptyBoard(size)),
            _secondBoard(GMPBoard::emptyBoard(size)),
            _neutralBoard(GMPBoard::neutralBoard(size)),
            _groundBoard(GMPBoard::groundBoard(size)),
            _moves(std::move(moves)),
            _undoCount(0),
            _piecesPerPlayer(GMPBoard::emptyBoard(size).flip().count() / 2),
            _mirrored(mirrored),
            _rotations(rotations) {
        this->replay();
    }

    GMPOneToOneGame::GMPOneToOneGame(unsigned char size) :
            GMPOneToOneGame(size, std::vector<GMPMove>{}, false, 0) {}

    unsigned char GMPOneToOneGame::size() const {
        return this->_size;
    }

    unsigned short GMPOneToOneGame::piecesPerPlayer() const {
        return this->_piecesPerPlayer;
    }

    unsigned short GMPOneToOneGame::movesMade() const {
        return this->moves().size();
    }

    std::vector<GMPMove> GMPOneToOneGame::moves() const {
        return std::vector<GMPMove>(this->_moves.begin(), this->_moves.end() - this->_undoCount);
    }

    std::vector<GMPMove> GMPOneToOneGame::legalMoves() const {
        return GMPMove::fromBoard(this->legalBoard());
    }

    bool GMPOneToOneGame::isOver() const {
        return this->firstWins() || this->secondWins();
    }

    unsigned short GMPOneToOneGame::firstScore() const {
        return this->_firstBoard.count();
    }

    unsigned short GMPOneToOneGame::secondScore() const {
        return this->_secondBoard.count();
    }

    unsigned short GMPOneToOneGame::playerScore() const {
        return this->playerBoard().count();
    }

    unsigned short GMPOneToOneGame::opponentScore() const {
        return this->opponentBoard().count();
    }

    bool GMPOneToOneGame::firstWins() const {
        return this->_piecesPerPlayer <= this->_firstBoard.count();
    }

    bool GMPOneToOneGame::secondWins() const {
        return this->_piecesPerPlayer <= this->_secondBoard.count();
    }

    bool GMPOneToOneGame::playerWins() const {
        return this->_piecesPerPlayer <= this->playerBoard().count();
    }

    bool GMPOneToOneGame::opponentWins() const {
        return this->_piecesPerPlayer <= this->opponentBoard().count();
    }

    bool GMPOneToOneGame::isFirstTurn() const {
        return (this->movesMade() % 2 == 0);
    }

    bool GMPOneToOneGame::isSecondTurn() const {
        return !this->isFirstTurn();
    }

    bool GMPOneToOneGame::isLegalMove(const GMPMove &move) const {
        return (this->legalBoard() & move.toBoard(this->_size)).count() > 0;
    }

    GMPBoard GMPOneToOneGame::firstBoard() const {
        return this->_firstBoard;
    }

    GMPBoard GMPOneToOneGame::secondBoard() const {
        return this->_secondBoard;
    }

    GMPBoard GMPOneToOneGame::neutralBoard() const {
        return this->_neutralBoard;
    }

    GMPBoard GMPOneToOneGame::legalBoard() const {
        return this->vacantBoard() & this->scaffoldedBoard();
    }

    GMPBoard GMPOneToOneGame::vacantBoard() const {
        return this->occupiedBoard().flip();
    }

    GMPBoard GMPOneToOneGame::scaffoldedBoard() const {
        return this->_groundBoard | this->occupiedBoard().promoteFour();
    }

    GMPBoard GMPOneToOneGame::occupiedBoard() const {
        return this->_neutralBoard | this->_firstBoard | this->_secondBoard;
    }

    GMPBoard GMPOneToOneGame::playerBoardAtMovesMade(unsigned short movesMade) const {
        return (movesMade & 1) == 0
               ? this->_firstBoard
               : this->_secondBoard;
    }

    GMPBoard GMPOneToOneGame::playerBoard() const {
        return this->playerBoardAtMovesMade(this->movesMade());
    }

    GMPBoard GMPOneToOneGame::opponentBoard() const {
        return this->playerBoardAtMovesMade(this->movesMade() + 1);
    }

    bool GMPOneToOneGame::isUndoable() const {
        return this->_undoCount < this->_moves.size();
    }

    bool GMPOneToOneGame::isRedoable() const {
        return this->_undoCount > 0;
    }

    void GMPOneToOneGame::makeMove(const GMPMove &move) {

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

    void GMPOneToOneGame::handleMove(const GMPMove &move, unsigned int movesMade) {

        if (movesMade % 2 == 0) {
            this->_firstBoard = this->_firstBoard | move.toBoard(this->_size);
        } else {
            this->_secondBoard = this->_secondBoard | move.toBoard(this->_size);
        }

        GMPBoard occupiedBoard = this->occupiedBoard();

        do {
            GMPBoard firstChainBoard = this->legalBoard() & this->_firstBoard.promoteMajority();
            auto firstVacancy = this->_piecesPerPlayer - this->_firstBoard.count();
            if (firstChainBoard.count() <= firstVacancy) {
                this->_firstBoard = this->_firstBoard | firstChainBoard;
            } else {
                auto chainMoves = GMPMove::fromBoard(firstChainBoard);
                for (auto i = 0; i < firstVacancy; i++) {
                    GMPMove chainMove = chainMoves.front();
                    chainMoves.erase(chainMoves.begin());
                    this->_firstBoard = this->_firstBoard | chainMove.toBoard(this->_size);
                }
            }

            GMPBoard secondChainBoard = this->legalBoard() & this->_secondBoard.promoteMajority();
            auto secondVacancy = this->_piecesPerPlayer - this->_secondBoard.count();
            if (secondChainBoard.count() <= secondVacancy) {
                this->_secondBoard = this->_secondBoard | secondChainBoard;
            } else {
                auto chainMoves = GMPMove::fromBoard(secondChainBoard);
                for (auto i = 0; i < secondVacancy; i++) {
                    GMPMove chainMove = chainMoves.front();
                    chainMoves.erase(chainMoves.begin());
                    this->_secondBoard = this->_secondBoard | chainMove.toBoard(this->_size);
                }
            }

            GMPBoard newOccupiedBoard = this->occupiedBoard();
            if (occupiedBoard == newOccupiedBoard) {
                break;
            }

            occupiedBoard = newOccupiedBoard;

        } while (!this->isOver());
    }

    std::size_t GMPOneToOneGame::state() const {
        return std::hash<std::string>{}(this->_firstBoard.toString() + this->_secondBoard.toString());
    }

    void GMPOneToOneGame::undo() {
        if (!this->isUndoable()) {
            throw std::runtime_error("The game is not undoable.");
        }

        this->_undoCount++;
        this->replay();
    }

    void GMPOneToOneGame::redo() {
        if (!this->isRedoable()) {
            throw std::runtime_error("The game is not redoable.");
        }

        this->_undoCount--;
        this->replay();
    }

    void GMPOneToOneGame::replay() {
        this->resetBoards();
        auto movesMade = 0;
        for (const auto &move: this->moves()) {
            this->handleMove(this->transformMove(move), movesMade);
        }
    }

    void GMPOneToOneGame::resetBoards() {
        this->_firstBoard = GMPBoard::emptyBoard(this->_size);
        this->_secondBoard = GMPBoard::emptyBoard(this->_size);
        this->_neutralBoard = GMPBoard::neutralBoard(this->_size);
    }

    void GMPOneToOneGame::flipVertical() {
        this->mirrored();
        this->rotated(2);
        this->_firstBoard = this->_firstBoard.flipVertical();
        this->_secondBoard = this->_secondBoard.flipVertical();
    }

    void GMPOneToOneGame::mirrorHorizontal() {
        this->mirrored();
        this->_firstBoard = this->_firstBoard.mirrorHorizontal();
        this->_secondBoard = this->_secondBoard.mirrorHorizontal();
    }

    void GMPOneToOneGame::flipDiagonal() {
        this->mirrored();
        this->rotated(1);
        this->_firstBoard = this->_firstBoard.flipDiagonal();
        this->_secondBoard = this->_secondBoard.flipDiagonal();
    }

    void GMPOneToOneGame::rotate90() {
        this->rotated(1);
        this->_firstBoard = this->_firstBoard.rotate90();
        this->_secondBoard = this->_secondBoard.rotate90();
    }

    void GMPOneToOneGame::rotate180() {
        this->rotated(2);
        this->_firstBoard = this->_firstBoard.rotate180();
        this->_secondBoard = this->_secondBoard.rotate180();
    }

    void GMPOneToOneGame::rotate270() {
        this->rotated(3);
        this->_firstBoard = this->_firstBoard.rotate270();
        this->_secondBoard = this->_secondBoard.rotate270();
    }

    void GMPOneToOneGame::transform() {
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

    void GMPOneToOneGame::resetTransformation() {
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

    void GMPOneToOneGame::mirrored() {
        this->_mirrored = !this->_mirrored;
        this->_rotations = -this->_rotations;
    }

    void GMPOneToOneGame::rotated(int rotations) {
        this->_rotations = (this->_rotations + rotations) % 4;
    }

    GMPMove GMPOneToOneGame::normalizeMove(const GMPMove &move) const {
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
        return GMPMove::fromBoard(board).front();
    }

    GMPMove GMPOneToOneGame::transformMove(const GMPMove &move) const {
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
        return GMPMove::fromBoard(board).front();
    }
}