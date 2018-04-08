#pragma once

#include "InputHandler.h"
#include "NodeLayout.h"
#include "Tile.h"
#include "Player.h"
#include "AStar.h"

// these need to be global, due to SDL threads taking C style functions as arguments, as opposed to C++ member functions

extern int playerWallCollisions(void* data);
extern SDL_sem *lock;
extern int data;
extern Player* player;
extern std::vector<Tile*>* tiles;

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