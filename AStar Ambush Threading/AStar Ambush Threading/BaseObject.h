#pragma once

#include "Vector2f.h"
#include <SDL.h>

class BaseObject {
public:
	BaseObject() {}
	BaseObject(Vector2f pos, int width, int height, SDL_Color colour);

	void setPos(float x, float y);
	void setPos(Vector2f pos);
	Vector2f getPos();

	void update(float deltaTime);

	void draw(SDL_Renderer *renderer);

private:
	Vector2f m_pos;
	SDL_Rect m_rect;

	SDL_Color m_colour;
};