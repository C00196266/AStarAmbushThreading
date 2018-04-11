#include "NPC.h"

NPC::NPC(Vector pos, int width, int height, SDL_Color colour, AStar *aStar) {
	m_pos = pos;

	m_rect.x = (int)pos.x;
	m_rect.y = (int)pos.y;
	m_rect.w = width;
	m_rect.h = height;

	m_colour = colour;

	m_aStar = aStar;

	m_pathChangedNeeded = true;
}

void NPC::update(float deltaTime) {
	if (!m_path.empty()) {
		Vector vecToNextPoint = Vector{ m_path.at(0)->getPos().x - m_pos.x, m_path.at(0)->getPos().y - m_pos.y };

		if (magnitude(vecToNextPoint) < 10) {
			m_path.erase(m_path.begin());
			vecToNextPoint = Vector{ m_path.at(0)->getPos().x - m_pos.x, m_path.at(0)->getPos().y - m_pos.y };
		}
	
		normalise(vecToNextPoint);
	
		m_vel.x += vecToNextPoint.x * deltaTime;
		m_vel.y += vecToNextPoint.y * deltaTime;

		//m_pos.x += m_vel.y;
		//m_pos.y += m_vel.y;
		m_pos.x -= 0.1;
		m_pos.y -= 0.1;

		m_rect.x = m_pos.x;
		m_rect.y = m_pos.y;
	}
}

void NPC::calculatePath() {
	int indexClosestToNPC = 0;
	float closestDistNPC = 99999;

	for (int i = 0; i < m_aStar->getLayout()->getNoOfNodes(); i++) {
		float distNPC = magnitude(m_aStar->getLayout()->getNodes().at(i)->getPos(), m_pos);

		if (distNPC < closestDistNPC) {
			closestDistNPC = distNPC;
			indexClosestToNPC = i;
		}
	}

	if (!m_path.empty()) {
		m_path.clear();
	}

	m_aStar->calculatePath(m_aStar->getLayout()->getNodes().at(indexClosestToNPC), m_path);

	m_pathChangedNeeded = false;
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

bool NPC::getPathChangeNeeded() {
	return m_pathChangedNeeded;
}

void NPC::setPathChangeNeeded(bool needed) {
	m_pathChangedNeeded = needed;
}