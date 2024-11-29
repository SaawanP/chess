#include "chessboard.hpp"

#include <iostream>
#include <SFML/Graphics/Image.hpp>
#include <boost/filesystem.hpp>

namespace ChessUI
{

bool find_file(const boost::filesystem::path& dir_path, const boost::filesystem::path& file_name,
        const boost::filesystem::path& parent_name, boost::filesystem::path& path_found) {
    const boost::filesystem::recursive_directory_iterator end;
    const auto it = std::find_if(boost::filesystem::recursive_directory_iterator(dir_path), end,
            [&file_name, &parent_name](const boost::filesystem::directory_entry& e) {
                return e.path().filename() == file_name && e.path().parent_path().filename() == parent_name;
            });
    if (it == end) {
        return false;
    } else {
        path_found = it->path();
        return true;
    }
}

ChessBoard::ChessBoard() : _current_board() {
    const boost::filesystem::path home_dir = L"/home";
    const boost::filesystem::path folder_name = L"images";
    const boost::filesystem::path parent_name = L"Chess";
    boost::filesystem::path map_dir;
    if (!find_file(home_dir, folder_name, parent_name, map_dir)) {
        throw std::filesystem::filesystem_error("Folder does not exist", std::error_code(2, std::generic_category()));
    }
    std::string dir = map_dir.string() + "/";
    
    // create pawns 
    for (int i = 8; i < 16; i++) {
        Pawn pawn(PieceColor::BLACK, sf::Texture());
        pawn.sprite_texture.loadFromFile(dir + "BlackPawn.png");
        pawn.sprite.setTexture(pawn.sprite_texture);
        _pieces.push_back(pawn);
        pawn.position = i;
    }
    for (int i = 48; i < 56; i++){
        Pawn pawn(PieceColor::WHITE, sf::Texture());
        pawn.sprite_texture.loadFromFile(dir + "WhitePawn.png");
        _pieces.push_back(pawn);
        pawn.sprite.setTexture(pawn.sprite_texture);
        pawn.position = i;
    }

    // create rooks
    {
        Rook rook(PieceColor::BLACK, sf::Texture());
        rook.sprite_texture.loadFromFile(dir + "BlackRook.png");
        rook.sprite.setTexture(rook.sprite_texture);
        rook.position = 0;
        _pieces.push_back(rook);
    }
    {
        Rook rook(PieceColor::BLACK, sf::Texture());
        rook.sprite_texture.loadFromFile(dir + "BlackRook.png");
        rook.sprite.setTexture(rook.sprite_texture);
        rook.position = 7;
        _pieces.push_back(rook);
        
    }
    {
        Rook rook(PieceColor::WHITE, sf::Texture());
        rook.sprite_texture.loadFromFile(dir + "WhiteRook.png");
        rook.sprite.setTexture(rook.sprite_texture);
        rook.position = 56;
        _pieces.push_back(rook);
    }
    {
        Rook rook(PieceColor::WHITE, sf::Texture());
        rook.sprite_texture.loadFromFile(dir + "WhiteRook.png");
        rook.sprite.setTexture(rook.sprite_texture);
        rook.position = 63;
        _pieces.push_back(rook);
    }

    // create knights
    {
        Knight knight(PieceColor::BLACK, sf::Texture());
        knight.sprite_texture.loadFromFile(dir + "BlackKnight.png");
        knight.sprite.setTexture(knight.sprite_texture);
        knight.position = 1;
        _pieces.push_back(knight);
    }
    {
        Knight knight(PieceColor::BLACK, sf::Texture());
        knight.sprite_texture.loadFromFile(dir + "BlackKnight.png");  
        knight.sprite.setTexture(knight.sprite_texture);
        knight.position = 6;
        _pieces.push_back(knight);
    }
    {
        Knight knight(PieceColor::WHITE, sf::Texture());
        knight.sprite_texture.loadFromFile(dir + "WhiteKnight.png");
        knight.sprite.setTexture(knight.sprite_texture);
        knight.position = 57;
        _pieces.push_back(knight);
    }
    {
        Knight knight(PieceColor::WHITE, sf::Texture());
        knight.sprite_texture.loadFromFile(dir + "WhiteKnight.png");
        knight.sprite.setTexture(knight.sprite_texture);
        knight.position = 62;
        _pieces.push_back(knight);
    }

    // create bishops
    {
        Bishop bishop(PieceColor::BLACK, sf::Texture());
        bishop.sprite_texture.loadFromFile(dir + "BlackBishop.png");
        bishop.sprite.setTexture(bishop.sprite_texture);
        bishop.position = 2;
        _pieces.push_back(bishop);
    }
    {
        Bishop bishop(PieceColor::BLACK, sf::Texture());
        bishop.sprite_texture.loadFromFile(dir + "BlackBishop.png");
        bishop.sprite.setTexture(bishop.sprite_texture);
        bishop.position = 5;
        _pieces.push_back(bishop);
    }
    {
        Bishop bishop(PieceColor::WHITE, sf::Texture());
        bishop.sprite_texture.loadFromFile(dir + "WhiteBishop.png");
        bishop.sprite.setTexture(bishop.sprite_texture);
        bishop.position = 58;
        _pieces.push_back(bishop);
    }
    {
        Bishop bishop(PieceColor::WHITE, sf::Texture());
        bishop.sprite_texture.loadFromFile(dir + "WhiteBishop.png");
        bishop.sprite.setTexture(bishop.sprite_texture);
        bishop.position = 61;
        _pieces.push_back(bishop);
    }


    // create queens
    {
        Queen queen(PieceColor::BLACK, sf::Texture());
        queen.sprite_texture.loadFromFile(dir + "BlackQueen.png");
        queen.sprite.setTexture(queen.sprite_texture);
        queen.position = 3;
        _pieces.push_back(queen);
    }
    {
        Queen queen(PieceColor::WHITE, sf::Texture());
        queen.sprite_texture.loadFromFile(dir + "WhiteQueen.png");
        queen.sprite.setTexture(queen.sprite_texture);
        queen.position = 59;
        _pieces.push_back(queen);
    }

    // create kings
    {
        King king(PieceColor::BLACK, sf::Texture());
        king.sprite_texture.loadFromFile(dir + "BlackKing.png");
        king.sprite.setTexture(king.sprite_texture);
        king.position = 4;
        _pieces.push_back(king);
    }
    {
        King king(PieceColor::WHITE, sf::Texture());
        king.sprite_texture.loadFromFile(dir + "WhiteKing.png");
        king.sprite.setTexture(king.sprite_texture);
        king.position = 60;
        _pieces.push_back(king);
    }

    std::cout << "Setting position";
    for (Piece piece : _pieces) {
        _current_board[piece.position] = &piece;
        // piece.sprite.setOrigin(sf::Vector2f(piece.sprite.getTextureRect().width / 2, piece.sprite.getTextureRect().height / 2));
        int x = piece.position % 8;
        int y = piece.position / 8;
        piece.sprite.setPosition(sf::Vector2f((x + 0.5) * Piece::PICTURE_WIDTH, (y + 0.5) * Piece::PICTURE_WIDTH));
        std::cout << piece.sprite.getPosition().x << piece.sprite.getPosition().y;
    }

    _turn = PieceColor::WHITE;
}
ChessBoard::~ChessBoard() {}

sf::Sprite ChessBoard::getBackground(sf::Vector2u window_size) {
    sf::Image image;
    image.create(window_size, sf::Color(225, 190, 150));
    for(uint i = 0; i < window_size.x; i++) {
        for(uint j = 0; j < window_size.y; j++) {
            int section_x = i / (window_size.x / 8);
            int section_y = j / (window_size.y / 8);
            if ((section_x + section_y) % 2 == 0) {
                image.setPixel(sf::Vector2u(i, j), sf::Color(160, 129, 108));
            }
        }
    }

    static sf::Texture texture; 
    texture.loadFromImage(image);
    sf::Sprite sprite(texture); 
    return sprite;
}

std::vector<sf::Sprite> ChessBoard::getPieceSprites(sf::Vector2u window_size) {
    std::vector<sf::Sprite> sprites;
    for (Piece piece : _pieces) {

        // sf::Image image;
        // image.create(sf::Vector2u(10,10), sf::Color::Black);
        // static sf::Texture texture; 
        // texture.loadFromImage(image);
        // sf::Sprite piece_sprite(texture);
        // std::cout << piece.sprite.getPosition().x << " " << piece.sprite.getPosition().y;
        // sf::Sprite piece_sprite(piece.sprite);
        // piece.sprite.setPosition(sf::Vector2f(100,100));
        // // piece_sprite.setScale(sf::Vector2f(window_size.x / (Piece::PICTURE_WIDTH * 8), window_size.y / (Piece::PICTURE_WIDTH * 8)));
        piece.sprite.setScale(sf::Vector2f(100, 100));
        // std::cout << piece.sprite.getPosition().x << " " << piece.sprite.getPosition().y << std::endl;

        sprites.push_back(piece.sprite);
    }
    return sprites;
}

std::optional<Piece> ChessBoard::getGrabbedPiece(int x, int y) {
    for (Piece piece : _pieces) {
        if (!piece.sprite.getTextureRect().contains(sf::Vector2i(x, y))) {
            return std::nullopt;
        }
        if (piece.color != _turn) {
            return std::nullopt;
        }
        return piece;
    }
    return std::nullopt;
}

bool ChessBoard::dropPieceIfPossible(Piece piece, sf::Vector2u window_size) {
    // convert pixel position to 0-63
    sf::Vector2f position = piece.sprite.getPosition();
    sf::Vector2u cell_size = window_size / 8U;
    int x = position.x / cell_size.x;
    int y = position.y / cell_size.y;
    int possible_position = x + 8 * y;

    // check if dropped position is valid
    std::vector<Move> valid_moves = calculateValidMovesForSinglePiece(&piece);
    for (Move move : valid_moves) {
        int new_position = piece.position + move.movement * move.distance;
        if (new_position == possible_position) {
            piece.position = new_position;
            piece.sprite.setPosition(sf::Vector2f(Piece::PICTURE_WIDTH * (x + 0.5), Piece::PICTURE_WIDTH * (y + 0.5)));
            if (_turn == PieceColor::WHITE) {
                _turn = PieceColor::BLACK;
            } else {
                _turn = PieceColor::WHITE;
            }
            return true;
        }
    }
    x = piece.position % 8;
    y = piece.position / 8;
    piece.sprite.setPosition(sf::Vector2f(Piece::PICTURE_WIDTH * (x + 0.5), Piece::PICTURE_WIDTH * (y + 0.5)));
    return false;
}

std::vector<Move> ChessBoard::calculateValidMoves() {
    std::vector<Move> valid_moves;
    for (auto piece : _pieces) {
        std::vector<Move> piece_valid_moves = calculateValidMovesForSinglePiece(&piece);

        int moves_size = valid_moves.size();
        valid_moves.resize(moves_size + piece_valid_moves.size());
        std::move(piece_valid_moves.begin(), piece_valid_moves.end(), valid_moves.begin() + moves_size);
    }
    return valid_moves;
}

std::vector<Move> ChessBoard::calculateValidMovesForSinglePiece(Piece* piece) {
    std::vector<Move> valid_moves;
    MovableDirections directions = piece->getMoveDirection();

    for (Movement movement : directions.movements) {
        for (int i = 1; i <= directions.move_limit || directions.move_limit == -1; i++) {
            if (piece->position + movement * i < 0 || piece->position + movement * i > 63)
                break;
            if (_current_board[piece->position + movement * i] != nullptr)
                break;

            Move move;
            move.movement = movement;
            move.distance = i;
            move.piece = piece;
            valid_moves.push_back(move);
        }
    }

    // check for en passante
    if (piece->type == PieceType::PAWN && piece->can_en_passante.has_value()) {
        Move move;
        Movement movement = directions.movements[0];
        move.movement = Movement(movement + piece->can_en_passante.value()); // this will result in a diagonal movement
        move.distance = 1;
        move.piece = piece;
        valid_moves.push_back(move);
    }

    // check for castling
    if (piece->type == PieceType::KING && piece->first_move) {
        std::vector<Piece> rooks = _findPieces(piece->color, PieceType::ROOK);
        for (Piece rook : rooks) {
            if (rook.first_move) {
                Move move;
                move.piece = &rook;
                move.distance = 1;
                move.movement = Movement::CASTLE;
                valid_moves.push_back(move);
            }
        }
    }
    // TODO check for king walking through checks
    return valid_moves;
}

std::vector<Piece> ChessBoard::_findPieces(PieceColor color, PieceType type) {
    std::vector<Piece> found_pieces;
    for (Piece piece : _pieces) {
        if (piece.type == type && piece.color == color) {
            found_pieces.push_back(piece);
        }
    }
    return found_pieces;
}
} // namespace ChessUI
