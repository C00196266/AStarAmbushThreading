#pragma once

#include "InputHandler.h"
#include "NodeLayout.h"
#include "Tile.h"
#include "Player.h"

class World {
public:
	World() {}
	World(EventListener *listener);

	void update(float deltaTime);
	void draw(SDL_Renderer *renderer);

private:
	std::vector<Tile*> m_tiles;

	Player m_player;

	NodeLayout m_layout;

	void setupWorld();
};