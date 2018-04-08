#pragma once

#include "InputHandler.h"
#include "NodeLayout.h"
#include "Tile.h"
#include "Player.h"
#include "AStar.h"
#include "NPC.h"

// these need to be global, due to SDL threads taking C style functions as arguments, as opposed to C++ member functions

extern int collisions(void*);
extern SDL_sem* lock;
extern int wallData;
extern int npcData;
extern Player* player;
extern std::vector<Tile*>* tiles;
extern std::vector<NPC*>* npcs;

class World {
public:
	World() {}
	World(EventListener *listener);

	void update(float deltaTime);
	void draw(SDL_Renderer *renderer);

private:
	std::vector<Tile*> m_tiles;
	std::vector<NPC*> m_NPCs;

	Player m_player;

	NodeLayout m_layout;

	void setupWorld();
};