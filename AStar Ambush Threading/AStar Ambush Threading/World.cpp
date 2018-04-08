#include "World.h"

SDL_sem *lock;
int data;
Player* player;
std::vector<Tile*>* tiles;

World::World(EventListener *listener) {
	setupWorld();
	m_layout.setNodesPerLine(144 / 4);
	m_layout.addArcs();

	//m_player = Player{ Vector{20, 20},  5, 5, SDL_Color{ 100, 100, 200, 255 }, listener};
	m_player = Player{ Vector{ 20, 20 },  20, 20, SDL_Color{ 100, 100, 200, 255 }, listener };

	lock = SDL_CreateSemaphore(1);
	data = -1;
	player = &m_player;
	tiles = &m_tiles;
}

void World::update(float deltaTime) {
	m_player.update(deltaTime);
}

void World::draw(SDL_Renderer *renderer) {
	for (int i = 0; i < m_tiles.size(); i++) {
		m_tiles.at(i)->draw(renderer);
	}

	m_layout.draw(renderer);

	m_player.draw(renderer);
}

void World::setupWorld() {
	for (int i = 0; i < 256 / 4; i++) {
		for (int j = 0; j < 144 / 4; j++) {
			if (i == 0) {
				m_tiles.push_back(new Tile(Vector{ i * 20.0f, j * 20.0f }, 20, 20, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
				m_layout.addNode(Vector{ i * 20.0f, j * 20.0f }, "Wall");
			}
			else if (i == 255 / 4) {
				m_tiles.push_back(new Tile(Vector{ i * 20.0f, j * 20.0f }, 20, 20, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
				m_layout.addNode(Vector{ i * 20.0f, j * 20.0f }, "Wall");
			}
			else if (j == 0) {
				m_tiles.push_back(new Tile(Vector{ i * 20.0f, j * 20.0f }, 20, 20, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
				m_layout.addNode(Vector{ i * 20.0f, j * 20.0f }, "Wall");
			}
			else if (j == 143 / 4) {
				m_tiles.push_back(new Tile(Vector{ i * 20.0f, j * 20.0f }, 20, 20, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
				m_layout.addNode(Vector{ i * 20.0f, j * 20.0f }, "Wall");
			}
			else if (i > 40 / 4 && i <= 55 / 4 && j > 0 / 4 && j <= 125 / 4) {
				m_tiles.push_back(new Tile(Vector{ i * 20.0f, j * 20.0f }, 20, 20, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
				m_layout.addNode(Vector{ i * 20.0f, j * 20.0f }, "Wall");
			}
			else if (i > 110 / 4 && i <= 125 / 4 && j > 10 / 4 && j <= 135 / 4) {
				m_tiles.push_back(new Tile(Vector{ i * 20.0f, j * 20.0f }, 20, 20, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
				m_layout.addNode(Vector{ i * 20.0f, j * 20.0f }, "Wall");
			}
			else if (i > 180 / 4 && i <= 195 / 4 && j >= 5 / 4 && j <= 110 / 4) {
				m_tiles.push_back(new Tile(Vector{ i * 20.0f, j * 20.0f }, 20, 20, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
				m_layout.addNode(Vector{ i * 20.0f, j * 20.0f }, "Wall");
			}
			else {
				m_layout.addNode(Vector{i * 20.0f, j * 20.0f}, "Floor");
			}
		}
	}
	//for (int i = 0; i < 256; i++) {
	//	for (int j = 0; j < 144; j++) {
	//		if (i == 0) {
	//			m_tiles.push_back(new Tile(Vector{ i * 5.0f, j * 5.0f }, 5, 5, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
	//			m_layout.addNode(Vector{ i * 5.0f, j * 5.0f }, "Wall");
	//		}
	//		else if (i == 255) {
	//			m_tiles.push_back(new Tile(Vector{ i * 5.0f, j * 5.0f }, 5, 5, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
	//			m_layout.addNode(Vector{ i * 5.0f, j * 5.0f }, "Wall");
	//		}
	//		else if (j == 0) {
	//			m_tiles.push_back(new Tile(Vector{ i * 5.0f, j * 5.0f }, 5, 5, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
	//			m_layout.addNode(Vector{ i * 5.0f, j * 5.0f }, "Wall");
	//		}
	//		else if (j == 143) {
	//			m_tiles.push_back(new Tile(Vector{ i * 5.0f, j * 5.0f }, 5, 5, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
	//			m_layout.addNode(Vector{ i * 5.0f, j * 5.0f }, "Wall");
	//		}
	//		else if (i > 40 && i <= 55 && j > 0 && j <= 125) {
	//			m_tiles.push_back(new Tile(Vector{ i * 5.0f, j * 5.0f }, 5, 5, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
	//			m_layout.addNode(Vector{ i * 5.0f, j * 5.0f }, "Wall");
	//		}
	//		else if (i > 110 && i <= 125 && j > 10 && j <= 135) {
	//			m_tiles.push_back(new Tile(Vector{ i * 5.0f, j * 5.0f }, 5, 5, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
	//			m_layout.addNode(Vector{ i * 5.0f, j * 5.0f }, "Wall");
	//		}
	//		else if (i > 180 && i <= 195 && j >= 5 && j <= 110) {
	//			m_tiles.push_back(new Tile(Vector{ i * 5.0f, j * 5.0f }, 5, 5, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
	//			m_layout.addNode(Vector{ i * 5.0f, j * 5.0f }, "Wall");
	//		}
	//		else {
	//			m_layout.addNode(Vector{ i * 5.0f, j * 5.0f }, "Floor");
	//		}
	//	}
	//}
}

int playerWallCollisions(void*) {
	int index = -1;

	while (true) {
		//Lock
		SDL_SemWait(lock);
		
		data++;
		
		if (data >= tiles->size()) {
			data = 0;
		}
		
		index = data;
		
		if (index >= tiles->size()) {
			index = 0;
		}
		
		//Unlock
		SDL_SemPost(lock);
		
		// collision
		SDL_Rect holder = { 0, 0, 0, 0 };

		if (SDL_IntersectRect(&player->getRect(), &tiles->at(index)->getRect(), &holder)) {
			if (holder.w > holder.h) {
				if (player->getPos().y > tiles->at(index)->getPos().y) {
					player->setPos(player->getPos().x, player->getRect().y + holder.h);
				}
				else {
					player->setPos(player->getPos().x, player->getRect().y - holder.h);
				}
				player->setVel(player->getVel().x, 0);
			}
			else {
				if (player->getPos().x > tiles->at(index)->getPos().x) {
					player->setPos(player->getRect().x + holder.w, player->getPos().y);
				}
				else {
					player->setPos(player->getRect().x - holder.w, player->getPos().y);
				}
				player->setVel(0, player->getVel().y);
			}
		}
	}

	return 0;
}