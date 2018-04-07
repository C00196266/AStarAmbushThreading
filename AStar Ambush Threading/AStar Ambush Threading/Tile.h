#pragma once

#include "BaseObject.h"
#include "Node.h"

class Tile : public BaseObject {
public:
	Tile() {}
	Tile(Vector pos, int width, int height, SDL_Color colour, std::string id);

	std::string getID();

private:
	std::string m_id;
};