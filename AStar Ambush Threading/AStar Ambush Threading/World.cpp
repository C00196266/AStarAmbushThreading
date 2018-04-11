#include "World.h"

SDL_sem* collisionLock;
SDL_sem* pathingLock;
int wallCollisionIndex;
int npcCollisionIndex;
int npcPathingIndex;
Player* player;
std::vector<Tile*>* tiles;
std::vector<NPC*>* npcs;
//float* delta_time;

World::World(EventListener *listener, float *deltaTime) {
	m_aStar = new AStar;

	m_size = 7;
	setupWorld();
	
	m_aStar->getLayout()->setNodesPerLine(100);
	m_aStar->getLayout()->addArcs();

	m_player = Player{ Vector{ 120, 420 },  m_size, m_size, SDL_Color{ 100, 100, 200, 255 }, listener };
	m_aStar->addPlayer(&m_player);

	for (int i = 0; i < 500; i++) {
		m_NPCs.push_back(new NPC(Vector{ 1200, 600 }, m_size, m_size, SDL_Color{ 200, 100, 100, 255 }, m_aStar));
	}

	collisionLock = SDL_CreateSemaphore(1);
	pathingLock = SDL_CreateSemaphore(1);
	wallCollisionIndex = -1;
	npcCollisionIndex = -1;
	npcPathingIndex = -1;
	player = &m_player;
	tiles = &m_tiles;
	npcs = &m_NPCs;

	m_deltaTime = deltaTime;
}

void World::updatePlayer() {
	m_player.update(*m_deltaTime);
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
}







void World::update(float deltaTime) {
	m_player.update(deltaTime);

	m_aStar->update();

	//for (int i = 0; i < m_NPCs.size(); i++) {
	//	m_NPCs.at(i)->update(deltaTime);
	//	
	//	if (m_aStar->getChangedNode() == true) {
	//		m_NPCs.at(i)->setPathChangeNeeded(true);
	//	}
	//}
}

void World::draw(SDL_Renderer *renderer) {
	for (int i = 0; i < m_tiles.size(); i++) {
		m_tiles.at(i)->draw(renderer);
	}
	
	//for (int i = 0; i < m_NPCs.size(); i++) {
	//	m_NPCs.at(i)->draw(renderer);
	//}

	//m_aStar->getLayout()->draw(renderer);

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
			//	m_tiles.push_back(new Tile(Vector{ (float)i * m_size, (float)j * m_size }, 2, 2, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
			//	m_aStar->getLayout()->addNode(Vector{ (float)i * m_size, (float)j * m_size }, "Wall");
			//}
			//else if (i > 110 / 4 && i <= 125 / 4 && j > 10 / 4 && j <= 135 / 4) {
			//	m_tiles.push_back(new Tile(Vector{ (float)i * m_size, (float)j * m_size }, 2, 2, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
			//	m_aStar->getLayout()->addNode(Vector{ (float)i * m_size, (float)j * m_size }, "Wall");
			//}
			//else if (i > 180 / 4 && i <= 195 / 4 && j > 20 / 4 && j <= 110 / 4) {
			//	m_tiles.push_back(new Tile(Vector{ (float)i * m_size, (float)j * m_size }, 2, 2, SDL_Color{ 0, 0, 0, 255 }, "Wall"));
			//	m_aStar->getLayout()->addNode(Vector{ (float)i * m_size, (float)j * m_size }, "Wall");
			//}
			else {
				m_aStar->getLayout()->addNode(Vector{ (float)i * m_size, (float)j * m_size }, "Floor");
			}
		}
	}
}

int collisions(void*) {
	int wallIndex = -1;
	int npcIndex = -1;

	//Lock
	SDL_SemWait(collisionLock);

	wallCollisionIndex++;

	wallIndex = wallCollisionIndex;

	npcCollisionIndex++;

	npcIndex = npcCollisionIndex;

	//Unlock
	SDL_SemPost(collisionLock);

	while (true) {		
		// collision
		
		for (int i = wallIndex; i < tiles->size(); i += wallCollisionIndex + 1) {
			SDL_Rect holder = { 0, 0, 0, 0 };

			// locked because if not, it may detect colliding with multiple tiles at the same time and end up pushing itself away from the wall
			SDL_SemWait(collisionLock);

			if (SDL_IntersectRect(&player->getRect(), &tiles->at(i)->getRect(), &holder)) {
				if (holder.w > holder.h) {
					if (player->getPos().y > tiles->at(i)->getPos().y) {
						player->setPos(player->getPos().x, player->getRect().y + holder.h);
					}
					else {
						player->setPos(player->getPos().x, player->getRect().y - holder.h);
					}
					player->setVel(player->getVel().x, 0);
				} 
				else {
					if (player->getPos().x > tiles->at(i)->getPos().x) {
						player->setPos(player->getRect().x + holder.w, player->getPos().y);
					}
					else {
						player->setPos(player->getRect().x - holder.w, player->getPos().y);
					}
					player->setVel(0, player->getVel().y);
				}
			}

			SDL_SemPost(collisionLock);
		}

		//if (SDL_IntersectRect(&player->getRect(), &npcs->at(npcIndex)->getRect(), &holder)) {
		//	std::cout << "Collision" << std::endl;
		//}
	}

	return 0;
}

int pathing(void*) {
	int npcIndex = -1;

	SDL_SemWait(pathingLock);

	npcPathingIndex++;

	npcIndex = npcPathingIndex;

	//Unlock
	SDL_SemPost(pathingLock);

	while (true) {
		for (int i = npcIndex; i < npcs->size(); i += (npcPathingIndex + 1)) {
			std::cout << i << std::endl;
			npcs->at(i)->calculatePath();
			//npcs->at(i)->update(*delta_time);
		}
	}

	return 0;
}

//int collisions(void*) {
//	int wallIndex = -1;
//	int npcIndex = -1;
//
//	//Lock
//	SDL_SemWait(collisionLock);
//
//	wallCollisionIndex++;
//
//	wallIndex = wallCollisionIndex;
//
//	npcCollisionIndex++;
//
//	npcIndex = npcCollisionIndex;
//
//	//Unlock
//	SDL_SemPost(collisionLock);
//
//	while (true) {
//		// collision
//
//		for (int i = wallIndex; i < tiles->size(); i += wallCollisionIndex + 1) {
//			SDL_Rect holder = { 0, 0, 0, 0 };
//
//			// locked because if not, it may detect colliding with multiple tiles at the same time and end up pushing itself away from the wall
//			SDL_SemWait(collisionLock);
//
//			if (SDL_IntersectRect(&player->getRect(), &tiles->at(i)->getRect(), &holder)) {
//				if (holder.w > holder.h) {
//					if (player->getPos().y > tiles->at(i)->getPos().y) {
//						player->setPos(player->getPos().x, player->getRect().y + holder.h);
//					}
//					else {
//						player->setPos(player->getPos().x, player->getRect().y - holder.h);
//					}
//					player->setVel(player->getVel().x, 0);
//				}
//				else {
//					if (player->getPos().x > tiles->at(i)->getPos().x) {
//						player->setPos(player->getRect().x + holder.w, player->getPos().y);
//					}
//					else {
//						player->setPos(player->getRect().x - holder.w, player->getPos().y);
//					}
//					player->setVel(0, player->getVel().y);
//				}
//			}
//
//			SDL_SemPost(collisionLock);
//		}
//
//		//if (SDL_IntersectRect(&player->getRect(), &npcs->at(npcIndex)->getRect(), &holder)) {
//		//	std::cout << "Collision" << std::endl;
//		//}
//	}
//
//	return 0;
//}

//int pathing(void*) {
//	int npcIndex = -1;
//
//	while (true) {
//		//Lock
//		SDL_SemWait(pathingLock);
//
//		npcPathingIndex++;
//
//		if (npcPathingIndex >= npcs->size()) {
//			npcPathingIndex = 0;
//		}
//
//		npcIndex = npcPathingIndex;
//
//		if (npcIndex >= npcs->size()) {
//			npcIndex = 0;
//		}
//
//		//Unlock
//		SDL_SemPost(pathingLock);
//
//		npcs->at(npcIndex)->calculatePath();
//	}
//
//	return 0;
//}