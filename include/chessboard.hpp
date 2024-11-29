#pragma once

#include <vector>
#include <optional>

#include "pieces.hpp"

namespace ChessUI
{
struct Move {
    Piece* piece;
    Movement movement;
    int distance;
};

class ChessBoard {
public:
    ChessBoard();
    ~ChessBoard();

    // UI stuff
    sf::Sprite getBackground(sf::Vector2u size);
    std::vector<sf::Sprite> getPieceSprites(sf::Vector2u size);
    std::optional<Piece> getGrabbedPiece(int x, int y);
    bool dropPieceIfPossible(Piece piece, sf::Vector2u window_size);

    std::vector<Move> calculateValidMoves(); // return list of valid moves from current board state
    void makeMove(Move move);
    std::array<Piece*, 64> getNewBoardState(Move move);
    std::vector<Move> calculateValidMovesForSinglePiece(Piece* piece);

private:
    std::vector<Piece> _pieces;
    Piece* _current_board[64];
    PieceColor _turn; 

    std::vector<Piece> _findPieces(PieceColor color, PieceType type);

};    
} // namespace ChessUI
