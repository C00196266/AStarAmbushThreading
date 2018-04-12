#pragma once

#include "InputHandler.h"
#include "NodeLayout.h"
#include "Tile.h"
#include "Player.h"
#include "AStar.h"
#include "NPC.h"

class World {
public:
	World() {}
	World(EventListener *listener, float *deltaTime, SDL_Renderer *renderer);

	void wallCollisions(int wallIndex);
	void npcCollisions(int npcIndex);
	void updatePlayer();
	void updateAStar();
	void updateNPC(int index);

	void draw(SDL_Renderer *renderer);

	std::vector<Tile*> getTiles();
	std::vector<NPC*> getNPCs();

private:
	std::vector<Tile*> m_tiles;
	std::vector<NPC*> m_NPCs;

	float* m_deltaTime;
	SDL_Renderer* m_renderer;

	Player m_player;

	AStar* m_aStar;
	NodeLayout m_layout;

	int m_size;

	EventListener* m_eventListener;

	void setupWorld();
};