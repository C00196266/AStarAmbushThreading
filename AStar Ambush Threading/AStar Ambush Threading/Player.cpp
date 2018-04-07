#include "Player.h"

#include <iostream>

Player::Player(Vector pos, int width, int height, SDL_Color colour, EventListener *listener) {
	m_pos = pos;

	m_rect.x = (int)pos.x;
	m_rect.y = (int)pos.y;
	m_rect.w = width;
	m_rect.h = height;

	m_colour = colour;

	m_listener = listener;
}

void Player::update(float deltaTime) {
	if (m_listener->pressedA || m_listener->pressedLeft) {
		m_pos.x -= 50 * deltaTime;
	}
	if (m_listener->pressedD || m_listener->pressedRight) {
		m_pos.x += 50 * deltaTime;
	}
	if (m_listener->pressedW || m_listener->pressedUp) {
		m_pos.y -= 50 * deltaTime;
	}
	if (m_listener->pressedS || m_listener->pressedDown) {
		m_pos.y += 50 * deltaTime;
	}

	m_rect.x = (int)m_pos.x;
	m_rect.y = (int)m_pos.y;
}