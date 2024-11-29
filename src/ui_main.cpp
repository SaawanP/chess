#include <SFML/Graphics.hpp>

#include "chessboard.hpp"

int main() {

    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(600, 600)), "Chess Window", sf::Style::Close);
    ChessUI::ChessBoard board;
    
    while (window.isOpen())
    {
        std::optional<ChessUI::Piece> piece_grabbed;
        std::vector<ChessUI::Move> moves;
        bool piece_dropped = false;

        // check all the window's events 
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Right) {
                    piece_grabbed = board.getGrabbedPiece(event.mouseButton.x, event.mouseButton.y);
                    moves = board.calculateValidMovesForSinglePiece(&piece_grabbed.value());
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Right) {
                    piece_dropped = true;
                }
            }
            if (event.type == sf::Event::MouseMoved) {
                if (piece_grabbed.has_value()) {
                    piece_grabbed.value().sprite.setPosition(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
                }
            }
        }

        window.clear(sf::Color::Black);
        sf::Vector2u window_size = window.getSize();

        // check if grabbed piece was dropped in available square
        if (piece_dropped) {
            board.dropPieceIfPossible(piece_grabbed.value(), window_size);
            piece_grabbed = std::nullopt;
            moves = {};
        } 

        // draw current elements
        window.draw(board.getBackground(window_size));
        for (sf::Sprite sprite : board.getPieceSprites(window_size)) {
            window.draw(sprite);
        }

        // // draw possible position for the last piece clicked or grabbed
        // for (ChessUI::Move move : moves) {
        //     int new_position = piece_grabbed.value().position + move.movement + move.distance;
        //     int x = new_position % 8;
        //     int y = new_position / 8;
        //     sf::CircleShape circle(ChessUI::Piece::PICTURE_WIDTH / 4);
        //     circle.setFillColor(sf::Color(127, 127, 127, 127));
        //     circle.setPosition(sf::Vector2f((x + 0.5) * ChessUI::Piece::PICTURE_WIDTH, (y + 0.5) * ChessUI::Piece::PICTURE_WIDTH));
        //     window.draw(circle);
        // }

        window.display();
        piece_dropped = false;
    }

    return 0;
}
