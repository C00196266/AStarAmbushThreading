#include "World.h"

World::World(EventListener *listener, float *deltaTime, SDL_Renderer *renderer) {
	m_aStar = new AStar;

	m_size = 7;
	setupWorld();
	
	m_aStar->getLayout()->setNodesPerLine(100);
	m_aStar->getLayout()->addArcs();

	m_player = Player{ Vector{ 50, 420 },  m_size, m_size, SDL_Color{ 100, 100, 200, 255 }, listener };
	m_aStar->addPlayer(&m_player);

	for (int i = 0; i < 1; i++) {
		m_NPCs.push_back(new NPC(Vector{ 600, 400 }, m_size, m_size, SDL_Color{ 200, 100, 100, 255 }, m_aStar));
	}

	m_deltaTime = deltaTime;
	m_renderer = renderer;
}

void World::updatePlayer() {
	m_player.update(*m_deltaTime);
}

void World::updateAStar() {
	m_aStar->update();
}

void World::updateNPC(int index) {
	m_NPCs.at(index)->update(*m_deltaTime);
}

void World::collisions(int index) {
	SDL_Rect holder = { 0, 0, 0, 0 };

	if (SDL_IntersectRect(&m_player.getRect(), &m_tiles.at(index)->getRect(), &holder)) {
		if (holder.w > holder.h) {
			if (m_player.getPos().y > m_tiles.at(index)->getPos().y) {
				m_player.setPos(m_player.getPos().x, m_player.getRect().y + holder.h);
			}
			else {
				m_player.setPos(m_player.getPos().x, m_player.getRect().y - holder.h);
			}
			m_player.setVel(m_player.getVel().x, 0);
		}
		else {
			if (m_player.getPos().x > m_tiles.at(index)->getPos().x) {
				m_player.setPos(m_player.getRect().x + holder.w, m_player.getPos().y);
			}
			else {
				m_player.setPos(m_player.getRect().x - holder.w, m_player.getPos().y);
			}
			m_player.setVel(0, m_player.getVel().y);
		}
	}

	for (int i = 0; i < m_NPCs.size(); i++) {
		if (SDL_IntersectRect(&m_NPCs.at(i)->getRect(), &m_tiles.at(index)->getRect(), &holder)) {
			if (holder.w > holder.h) {
				if (m_NPCs.at(i)->getPos().y > m_tiles.at(index)->getPos().y) {
					m_NPCs.at(i)->setPos(m_NPCs.at(i)->getPos().x, m_NPCs.at(i)->getRect().y + holder.h);
				}
				else {
					m_NPCs.at(i)->setPos(m_NPCs.at(i)->getPos().x, m_NPCs.at(i)->getRect().y - holder.h);
				}
				m_NPCs.at(i)->setVel(m_NPCs.at(i)->getVel().x, 0);
			}
			else {
				if (m_NPCs.at(i)->getPos().x > m_tiles.at(index)->getPos().x) {
					m_NPCs.at(i)->setPos(m_NPCs.at(i)->getRect().x + holder.w, m_NPCs.at(i)->getPos().y);
				}
				else {
					m_NPCs.at(i)->setPos(m_NPCs.at(i)->getRect().x - holder.w, m_NPCs.at(i)->getPos().y);
				}
				m_NPCs.at(i)->setVel(0, m_NPCs.at(i)->getVel().y);
			}
		}
	}
}

std::vector<Tile*> World::getTiles() {
	return m_tiles;
}

std::vector<NPC*> World::getNPCs() {
	return m_NPCs;
}

void World::draw(SDL_Renderer *renderer) {
	for (int i = 0; i < m_tiles.size(); i++) {
		m_tiles.at(i)->draw(renderer);
	}
	
	for (int i = 0; i < m_NPCs.size(); i++) {
		m_NPCs.at(i)->draw(renderer);
	}

	m_player.draw(renderer);
}

void World::setupWorld() {
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (i == 0) {
				m_tiles.push_back(new Tile(Vector{ (float)i * (float)m_size, (float)j * (float)m_size }, m_size, m_size, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
				m_aStar->getLayout()->addNode(Vector{ (float)i * m_size, (float)j * m_size }, "Wall");
			}
			else if (i == 99) {
				m_tiles.push_back(new Tile(Vector{ (float)i * (float)m_size, (float)j * (float)m_size }, m_size, m_size, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
				m_aStar->getLayout()->addNode(Vector{ (float)i * m_size, (float)j * m_size }, "Wall");
			}
			else if (j == 0) {
				m_tiles.push_back(new Tile(Vector{ (float)i * (float)m_size, (float)j * (float)m_size }, m_size, m_size, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
				m_aStar->getLayout()->addNode(Vector{ (float)i * m_size, (float)j * m_size }, "Wall");
			}
			else if (j == 99) {
				m_tiles.push_back(new Tile(Vector{ (float)i * m_size, (float)j * m_size }, m_size, m_size, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
				m_aStar->getLayout()->addNode(Vector{ (float)i * m_size, (float)j * m_size }, "Wall");
			}
			else if (i > 15 && i <= 19 && j > 0 && j <= 92) {
				m_tiles.push_back(new Tile(Vector{ (float)i * m_size, (float)j * m_size }, m_size, m_size, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
				m_aStar->getLayout()->addNode(Vector{ (float)i * m_size, (float)j * m_size }, "Wall");
			}
			else if (i > 46 && i <= 50 && j > 10 && j <= 95) {
				m_tiles.push_back(new Tile(Vector{ (float)i * m_size, (float)j * m_size }, m_size, m_size, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
				m_aStar->getLayout()->addNode(Vector{ (float)i * m_size, (float)j * m_size }, "Wall");
			}
			else if (i > 74 && i <= 78 && j > 7 && j <= 89) {
				m_tiles.push_back(new Tile(Vector{ (float)i * m_size, (float)j * m_size }, m_size, m_size, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
				m_aStar->getLayout()->addNode(Vector{ (float)i * m_size, (float)j * m_size }, "Wall");
			}
			else {
				m_aStar->getLayout()->addNode(Vector{ (float)i * m_size, (float)j * m_size }, "Floor");
			}
		}
	}
}