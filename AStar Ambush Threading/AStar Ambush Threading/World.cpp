#include "World.h"

World::World(EventListener *listener) {
	setupWorld();
	m_player = Player{ Vector{20, 20},  5, 5, SDL_Color{ 100, 100, 200, 255 }, listener};
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
			else if (i > 40 && i <= 55) {
				if (j > 0 && j <= 125) {
					m_tiles.push_back(new Tile(Vector{ i * 5.0f, j * 5.0f }, 5, 5, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
					m_layout.addNode(Vector{ i * 5.0f, j * 5.0f }, "Wall");
				}
			}
			else if (i > 110 && i <= 125) {
				if (j > 10 && j <= 135) {
					m_tiles.push_back(new Tile(Vector{ i * 5.0f, j * 5.0f }, 5, 5, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
					m_layout.addNode(Vector{ i * 5.0f, j * 5.0f }, "Wall");
				}
			}
			else if (i > 180 && i <= 195) {
				if (j >= 5 && j <= 110) {
					m_tiles.push_back(new Tile(Vector{ i * 5.0f, j * 5.0f }, 5, 5, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
					m_layout.addNode(Vector{ i * 5.0f, j * 5.0f }, "Wall");
				}
			}
			else {
				m_layout.addNode(Vector{ i * 5.0f, j * 5.0f }, "Floor");
			}
		}
	}
}