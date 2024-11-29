#include "pieces.hpp"

namespace ChessUI
{
    sf::Texture Piece::sprite_texture = sf::Texture();
    
    Piece::Piece(sf::Texture texture) : sprite(sprite_texture) {
        // sprite_texture = texture;
    }
} // namespace ChessUI
