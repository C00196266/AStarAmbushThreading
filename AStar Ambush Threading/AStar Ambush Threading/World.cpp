#include "World.h"

SDL_sem *lock;
int data;
Player* player;
std::vector<Tile*>* tiles;

World::World(EventListener *listener) {
	setupWorld();
	m_player = Player{ Vector{20, 20},  5, 5, SDL_Color{ 100, 100, 200, 255 }, listener};

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

	m_player.draw(renderer);
}

void World::setupWorld() {
	//for (int i = 0; i < 256 / 2; i++) {
	//	for (int j = 0; j < 144 / 2; j++) {
	//		if (i == 0) {
	//			m_tiles.push_back(new Tile(Vector{ i * 10.0f, j * 10.0f }, 10, 10, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
	//			m_layout.addNode(Vector{ i * 10.0f, j * 10.0f }, "Wall");
	//		}
	//		else if (i == 255 / 2) {
	//			m_tiles.push_back(new Tile(Vector{ i * 10.0f, j * 10.0f }, 10, 10, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
	//			m_layout.addNode(Vector{ i * 10.0f, j * 10.0f }, "Wall");
	//		}
	//		else if (j == 0) {
	//			m_tiles.push_back(new Tile(Vector{ i * 10.0f, j * 10.0f }, 10, 10, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
	//			m_layout.addNode(Vector{ i * 10.0f, j * 10.0f }, "Wall");
	//		}
	//		else if (j == 143 / 2) {
	//			m_tiles.push_back(new Tile(Vector{ i * 10.0f, j * 10.0f }, 10, 10, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
	//			m_layout.addNode(Vector{ i * 10.0f, j * 10.0f }, "Wall");
	//		}
	//		else if (i > 40 / 2 && i <= 55 / 2) {
	//			if (j > 0 / 2 && j <= 125 / 2) {
	//				m_tiles.push_back(new Tile(Vector{ i * 10.0f, j * 10.0f }, 10, 10, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
	//				m_layout.addNode(Vector{ i * 10.0f, j * 10.0f }, "Wall");
	//			}
	//		}
	//		else if (i > 110 / 2 && i <= 125 / 2) {
	//			if (j > 10 / 2 && j <= 135 / 2) {
	//				m_tiles.push_back(new Tile(Vector{ i * 10.0f, j * 10.0f }, 10, 10, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
	//				m_layout.addNode(Vector{ i * 10.0f, j * 10.0f }, "Wall");
	//			}
	//		}
	//		else if (i > 180 && i <= 195) {
	//			if (j >= 5 / 2 && j <= 110 / 2) {
	//				m_tiles.push_back(new Tile(Vector{ i * 10.0f, j * 10.0f }, 10, 10, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
	//				m_layout.addNode(Vector{ i * 10.0f, j * 10.0f }, "Wall");
	//			}
	//		}
	//		else {
	//			m_layout.addNode(Vector{i * 10.0f, j * 10.0f}, "Floor");
	//		}
	//	}
	//}
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 144; j++) {
			if (i == 0) {
				m_tiles.push_back(new Tile(Vector{ i * 5.0f, j * 5.0f }, 5, 5, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
				m_layout.addNode(Vector{ i * 5.0f, j * 5.0f }, "Wall");
			}
			else if (i == 255) {
				m_tiles.push_back(new Tile(Vector{ i * 5.0f, j * 5.0f }, 5, 5, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
				m_layout.addNode(Vector{ i * 5.0f, j * 5.0f }, "Wall");
			}
			else if (j == 0) {
				m_tiles.push_back(new Tile(Vector{ i * 5.0f, j * 5.0f }, 5, 5, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
				m_layout.addNode(Vector{ i * 5.0f, j * 5.0f }, "Wall");
			}
			else if (j == 143) {
				m_tiles.push_back(new Tile(Vector{ i * 5.0f, j * 5.0f }, 5, 5, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
				m_layout.addNode(Vector{ i * 5.0f, j * 5.0f }, "Wall");
			}
			else if (i > 40 && i <= 55 && j > 0 && j <= 125) {
				m_tiles.push_back(new Tile(Vector{ i * 5.0f, j * 5.0f }, 5, 5, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
				m_layout.addNode(Vector{ i * 5.0f, j * 5.0f }, "Wall");
			}
			else if (i > 110 && i <= 125 && j > 10 && j <= 135) {
				m_tiles.push_back(new Tile(Vector{ i * 5.0f, j * 5.0f }, 5, 5, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
				m_layout.addNode(Vector{ i * 5.0f, j * 5.0f }, "Wall");
			}
			else if (i > 180 && i <= 195 && j >= 5 && j <= 110) {
				m_tiles.push_back(new Tile(Vector{ i * 5.0f, j * 5.0f }, 5, 5, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
				m_layout.addNode(Vector{ i * 5.0f, j * 5.0f }, "Wall");
			}
			else {
				m_layout.addNode(Vector{ i * 5.0f, j * 5.0f }, "Floor");
			}
		}
	}
}

int playerWallCollisions(void* temp) {
	int index = -1;

	while (true) {
		srand(SDL_GetTicks());
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
		
		////Unlock
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