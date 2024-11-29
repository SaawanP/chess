#pragma once

#include <vector>
#include <limits>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace ChessUI
{
enum class PieceType { // number represent the value of each piece
    PAWN = 1,
    ROOK = 5,
    KNIGHT = 3,
    BISHOP = 3,
    QUEEN = 8,
    KING = 1000 // king piece has no real value, so it gets an arbitrarily large number
};

enum class PieceColor {
    BLACK,
    WHITE
};

enum Movement { // direction is from white's perspective
    CASTLE,
    UP = -8,
    DOWN = 8,
    LEFT = -1,
    RIGHT = 1,
    UP_LEFT = UP + LEFT,
    UP_RIGHT = UP + RIGHT,
    DOWN_LEFT = DOWN + LEFT,
    DOWN_RIGHT = DOWN + RIGHT,
    KNIGHT_UP_RIGHT = UP * 2 + RIGHT,
    KNIGHT_UP_LEFT = UP * 2 + LEFT,
    KNIGHT_DOWN_RIGHT = DOWN * 2 + RIGHT,
    KNIGHT_DOWN_LEFT = DOWN * 2 + LEFT,
    KNIGHT_RIGHT_UP = UP + RIGHT * 2,
    KNIGHT_LEFT_UP= UP + LEFT * 2,
    KNIGHT_RIGHT_DOWN = DOWN + RIGHT * 2,
    KNIGHT_LEFT_DOWN = DOWN + LEFT * 2,
};

struct MovableDirections {
    std::vector<Movement> movements;
    int move_limit;
};

class Piece {
    public:
        static const uint16_t PICTURE_WIDTH = 320; // number of pixels in both x and y
        
        Piece(sf::Texture texture);
        virtual MovableDirections getMoveDirection() {
            return _directions;
        }

        static sf::Texture sprite_texture;
        sf::Sprite sprite;
        uint8_t position; // 0-63 for each postion starting at A8 going to H1

        PieceType type;
        PieceColor color;
        std::optional<Movement> can_en_passante;
        bool first_move = true;
    protected:
        MovableDirections _directions;
};

class Pawn : public Piece {
    public:
        Pawn(PieceColor _color, sf::Texture texture) : Piece(texture) {
            color = _color;
            type = PieceType::PAWN;
        }

        virtual MovableDirections getMoveDirection() override {
            MovableDirections directions;
            if (color == PieceColor::WHITE) {
                directions.movements.push_back(Movement::UP);
            } else {
                directions.movements.push_back(Movement::DOWN);
            }

            directions.move_limit = 1;
            if (first_move) {
                directions.move_limit = 2;
            }

            return directions;
        } 
};

class Rook : public Piece {
    public:
        Rook(PieceColor color, sf::Texture texture) :  Piece(texture) {
            color = color;
            type = PieceType::ROOK;

            _directions.movements.push_back(Movement::UP);
            _directions.movements.push_back(Movement::DOWN);
            _directions.movements.push_back(Movement::LEFT);
            _directions.movements.push_back(Movement::RIGHT);
            _directions.move_limit = -1;
        }
};

class Knight : public Piece {
    public:
        Knight(PieceColor color, sf::Texture texture) : Piece(texture) {
            color = color;
            type = PieceType::KNIGHT;

            _directions.movements.push_back(Movement::KNIGHT_UP_LEFT);
            _directions.movements.push_back(Movement::KNIGHT_UP_RIGHT);
            _directions.movements.push_back(Movement::KNIGHT_DOWN_LEFT);
            _directions.movements.push_back(Movement::KNIGHT_DOWN_RIGHT);
            _directions.movements.push_back(Movement::KNIGHT_LEFT_UP);
            _directions.movements.push_back(Movement::KNIGHT_LEFT_DOWN);
            _directions.movements.push_back(Movement::KNIGHT_RIGHT_UP);
            _directions.movements.push_back(Movement::KNIGHT_RIGHT_DOWN);
            _directions.move_limit = 1;
        }
};

class Bishop : public Piece {
    public:
        Bishop(PieceColor color, sf::Texture texture) : Piece(texture) {
            color = color;
            type = PieceType::BISHOP;

            _directions.movements.push_back(Movement::UP_LEFT);
            _directions.movements.push_back(Movement::UP_RIGHT);
            _directions.movements.push_back(Movement::DOWN_LEFT);
            _directions.movements.push_back(Movement::DOWN_RIGHT);
            _directions.move_limit = -1;
        }
};

class Queen : public Piece {
    public:
        Queen(PieceColor color, sf::Texture texture) : Piece(texture) {
            color = color;
            type = PieceType::QUEEN;

            _directions.movements.push_back(Movement::UP);
            _directions.movements.push_back(Movement::DOWN);
            _directions.movements.push_back(Movement::LEFT);
            _directions.movements.push_back(Movement::RIGHT);
            _directions.movements.push_back(Movement::UP_LEFT);
            _directions.movements.push_back(Movement::UP_RIGHT);
            _directions.movements.push_back(Movement::DOWN_LEFT);
            _directions.movements.push_back(Movement::DOWN_RIGHT);
            _directions.move_limit = -1;
        }
};

class King : public Piece {
    public:
        King(PieceColor color, sf::Texture texture) : Piece(texture) {
            color = color;
            type = PieceType::KING;

            _directions.movements.push_back(Movement::UP);
            _directions.movements.push_back(Movement::DOWN);
            _directions.movements.push_back(Movement::LEFT);
            _directions.movements.push_back(Movement::RIGHT);
            _directions.movements.push_back(Movement::UP_LEFT);
            _directions.movements.push_back(Movement::UP_RIGHT);
            _directions.movements.push_back(Movement::DOWN_LEFT);
            _directions.movements.push_back(Movement::DOWN_RIGHT);
            _directions.move_limit = 1;
        }
};

} // namespace ChessUI
