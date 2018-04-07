#include "World.h"

World::World() {
	setupWorld();
}

void World::update(float deltaTime) {

}

void World::draw(SDL_Renderer *renderer) {
	for (int i = 0; i < m_tiles.size(); i++) {
		m_tiles.at(i)->draw(renderer);
	}
}

void World::setupWorld() {
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 144; j++) {
			if (i == 0) {
				m_tiles.push_back(new Tile(Vector{ i * 5.0f, j * 5.0f }, 5, 5, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
			}
			else if (i == 255) {
				m_tiles.push_back(new Tile(Vector{ i * 5.0f, j * 5.0f }, 5, 5, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
			}
			else if (j == 0) {
				m_tiles.push_back(new Tile(Vector{ i * 5.0f, j * 5.0f }, 5, 5, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
			}
			else if (j == 143) {
				m_tiles.push_back(new Tile(Vector{ i * 5.0f, j * 5.0f }, 5, 5, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
			}
			else if (i > 40 && i <= 55) {
				if (j > 0 && j <= 125) {
					m_tiles.push_back(new Tile(Vector{ i * 5.0f, j * 5.0f }, 5, 5, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
				}
			}
			else if (i > 110 && i <= 125) {
				if (j > 10 && j <= 135) {
					m_tiles.push_back(new Tile(Vector{ i * 5.0f, j * 5.0f }, 5, 5, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
				}
			}
			else if (i > 180 && i <= 195) {
				if (j >= 5 && j <= 110) {
					m_tiles.push_back(new Tile(Vector{ i * 5.0f, j * 5.0f }, 5, 5, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
				}
			}
			else {
				m_tiles.push_back(new Tile(Vector{ i * 5.0f, j * 5.0f }, 5, 5, SDL_Color{ 255, 255, 255, 255 }, "Floor"));
			}
		}
	}
}