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
	m_vel = { 0, 0 };

	if (m_listener->pressedA || m_listener->pressedLeft) {
		m_vel.x = -10 * deltaTime;
	}
	if (m_listener->pressedD || m_listener->pressedRight) {
		m_vel.x = 10 * deltaTime;
	}
	if (m_listener->pressedW || m_listener->pressedUp) {
		m_vel.y = -10 * deltaTime;
	}
	if (m_listener->pressedS || m_listener->pressedDown) {
		m_vel.y = 10 * deltaTime;
	}

	m_pos.x += m_vel.x;
	m_pos.y += m_vel.y;

	m_rect.x = (int)m_pos.x;
	m_rect.y = (int)m_pos.y;
}

Vector Player::getVel() {
	return m_vel;
}

void Player::setVel(float x, float y) {
	m_vel.x = x;
	m_vel.y = y;
}