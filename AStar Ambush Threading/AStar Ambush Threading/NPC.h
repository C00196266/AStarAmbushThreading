#pragma once

#include "BaseObject.h"
#include "AStar.h"

class NPC : public BaseObject {
public:
	NPC() {}
	NPC(Vector pos, int width, int height, SDL_Color colour, AStar *astar);

	Vector getVel();
	void setVel(float x, float y);

	void update(float deltaTime);

	void calculatePath();

	bool getPathChangeNeeded();
	void setPathChangeNeeded(bool needed);

private:
	Vector m_vel;

	AStar* m_aStar;

	void normalise(Vector &v);
	float magnitude(Vector v);
	float magnitude(Vector v1, Vector v2);

	std::vector<Node*> m_path;
	bool m_pathChangedNeeded;
};