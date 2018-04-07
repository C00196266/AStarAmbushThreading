#include "Tile.h"

Tile::Tile(Vector pos, int width, int height, SDL_Color colour, std::string id) {
	m_pos = pos;

	m_rect.x = (int)pos.x;
	m_rect.y = (int)pos.y;
	m_rect.w = width;
	m_rect.h = height;

	m_colour = colour;

	m_node = new Node(pos, id);
}

std::string Tile::getID() {
	return m_id;
}

Node* Tile::getNode() {
	return m_node;
}