#pragma once

#include "BaseObject.h"
#include "AStar.h"

class NPC : public BaseObject {
public:
	NPC() {}
	NPC(Vector pos, int width, int height, SDL_Color colour, NodeLayout &layout, Vector* playerPos);

	Vector getVel();
	void setVel(float x, float y);

	void update(float deltaTime);

private:
	void calculatePath();

	Vector m_vel;

	AStar* m_aStar;
	std::vector<Node*> m_path;

	void normalise(Vector &v);
	float magnitude(Vector v);
	float magnitude(Vector v1, Vector v2);

	Vector* m_playerPos;
};