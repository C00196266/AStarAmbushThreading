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
		if (m_path.size() < 500) {
			Vector vecToNextPoint = Vector{ m_path.at(0)->getPos().x - m_pos.x, m_path.at(0)->getPos().y - m_pos.y };

			float dist = magnitude(vecToNextPoint);
			float speed = 0;

			if (dist < 15) {
				for (std::list<Arc>::iterator i = m_path.at(0)->getArcs().begin(); i != m_path.at(0)->getArcs().end(); i++) {
					(*i).getCorrespondingArc()->decrementWeight();
				}
				m_path.erase(m_path.begin());
			}
			else if (dist > 40) {
				speed = 0.2;
			}
			else {
				speed = 0.2 * (dist / 20);
			}

			normalise(vecToNextPoint);

			vecToNextPoint.x *= speed;
			vecToNextPoint.y *= speed;

			m_accel.x = vecToNextPoint.x - (m_vel.x / 2);
			m_accel.y = vecToNextPoint.y - (m_vel.y / 2);

			if (magnitude(m_accel) > 2) {
				normalise(m_accel);
				m_accel.x *= 2;
				m_accel.y *= 2;
			}

			m_vel.x += m_accel.x * deltaTime;
			m_vel.y += m_accel.y * deltaTime;

			if (magnitude(m_vel) > 0.2) {
				normalise(m_vel);
				m_vel.x *= 0.2;
				m_vel.y *= 0.2;
			}

			m_pos.x += m_vel.x;
			m_pos.y += m_vel.y;

			m_rect.x = m_pos.x;
			m_rect.y = m_pos.y;
		}
		else {
			calculatePath();
		}
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

	if (m_path.size() < 500) {
		while (!m_path.empty()) {
			for (std::list<Arc>::iterator i = m_path.at(0)->getArcs().begin(); i != m_path.at(0)->getArcs().end(); i++) {
				(*i).decrementWeight();
			}
			m_path.erase(m_path.begin());
		}
	}
	else {
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