#include "NPC.h"

NPC::NPC(Vector pos, int width, int height, SDL_Color colour, NodeLayout &layout, Vector* playerPos) {
	m_pos = pos;

	m_rect.x = (int)pos.x;
	m_rect.y = (int)pos.y;
	m_rect.w = width;
	m_rect.h = height;

	m_colour = colour;

	m_aStar = new AStar(layout);

	m_playerPos = playerPos;

	calculatePath();
}

void NPC::update(float deltaTime) {
	if (!m_path.empty()) {
		Vector vecToNextPoint = Vector{ m_path.at(0)->getPos().x - m_pos.x, m_path.at(0)->getPos().y - m_pos.y };
	
		normalise(vecToNextPoint);
	
		m_vel.x += vecToNextPoint.x * deltaTime;
		m_vel.y += vecToNextPoint.y * deltaTime;
	}
	else {
		calculatePath();
	}
}

void NPC::calculatePath() {
	int indexClosestToPlayer;
	int indexClosestToNPC;

	float closestDistPlayer = 99999;
	float closestDistNPC = 99999;

	for (int i = 0; i < m_aStar->getLayout().getNoOfNodes() - 1; i++) {
		float distPlayer = magnitude(m_aStar->getLayout().getNodes().at(i)->getPos(), (*m_playerPos));

		if (distPlayer < closestDistPlayer) {
			closestDistPlayer = distPlayer;
			indexClosestToPlayer = i;
		}

		float distNPC = magnitude(m_aStar->getLayout().getNodes().at(i)->getPos(), m_pos);

		if (distNPC < closestDistNPC) {
			closestDistNPC = distNPC;
			indexClosestToNPC = i;
		}
	}

	m_aStar->calculatePath(m_aStar->getLayout().getNodes().at(indexClosestToPlayer), m_aStar->getLayout().getNodes().at(indexClosestToNPC), m_path);
}

Vector NPC::getVel() {
	return m_vel;
}

void NPC::setVel(float x, float y) {
	m_vel.x = x;
	m_vel.y = y;
}

void NPC::normalise(Vector &v) {
	float m = magnitude(v);

	if (m > 0)
	{
		v.x = v.x / m;
		v.y = v.y / m;
	}
}

float NPC::magnitude(Vector v) {
	return sqrt((v.x * v.x) + (v.y * v.y));
}

float NPC::magnitude(Vector v1, Vector v2) {
	return sqrt(((v2.x - v1.x) * (v2.x - v1.x)) + ((v2.y - v1.y) * (v2.y - v1.y)));
}