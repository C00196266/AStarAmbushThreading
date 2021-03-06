#include "BaseObject.h"

BaseObject::BaseObject(Vector pos, int width, int height, SDL_Color colour) {
	m_pos = pos;

	m_rect.x = (int)pos.x;
	m_rect.y = (int)pos.y;
	m_rect.w = width;
	m_rect.h = height;

	m_colour = colour;
}

void BaseObject::draw(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, m_colour.r, m_colour.g, m_colour.b, m_colour.a);
	SDL_RenderFillRect(renderer, &m_rect);
}

void BaseObject::setPos(float x, float y) {
	m_pos.x = x;
	m_pos.y = y;

	m_rect.x = x;
	m_rect.y = y;
}

void BaseObject::setPos(Vector pos) {
	m_pos = pos;

	m_rect.x = pos.x;
	m_rect.y = pos.y;
}

Vector BaseObject::getPos() {
	return m_pos;
}

SDL_Rect BaseObject::getRect() {
	return m_rect;
}