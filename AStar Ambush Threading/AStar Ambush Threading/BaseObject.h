#pragma once

#include "Vector.h"
#include <SDL.h>

class BaseObject {
public:
	BaseObject() {}
	BaseObject(Vector pos, int width, int height, SDL_Color colour);

	void setPos(float x, float y);
	void setPos(Vector pos);
	Vector getPos();

	void update(float deltaTime);

	void draw(SDL_Renderer *renderer);

protected:
	Vector m_pos;
	SDL_Rect m_rect;

	SDL_Color m_colour;
};