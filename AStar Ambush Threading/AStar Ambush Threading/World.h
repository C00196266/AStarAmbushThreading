#pragma once

#include "InputHandler.h"
#include "NodeLayout.h"
#include "Tile.h"

class World {
public:
	World();

	void update(float deltaTime);
	void draw(SDL_Renderer *renderer);

private:
	std::vector<Tile*> m_tiles;

	NodeLayout m_layout;

	void setupWorld();
};