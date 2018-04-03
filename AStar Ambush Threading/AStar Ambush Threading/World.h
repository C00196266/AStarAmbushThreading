#pragma once

#include "InputHandler.h"
#include "NodeLayout.h"
#include "BaseObject.h"

class World {
public:
	World();

	void update(float deltaTime);
	void draw(SDL_Renderer *renderer);

private:
	BaseObject test;

	NodeLayout m_layout;
};