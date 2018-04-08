#pragma once

#include "BaseObject.h"
#include "EventListener.h"

class Player : public BaseObject {
public:
	Player() {}
	Player(Vector pos, int width, int height, SDL_Color colour, EventListener *listener);

	Vector getVel();
	void setVel(float x, float y);

	void update(float deltaTime);
private:
	EventListener *m_listener;

	Vector m_vel;
};