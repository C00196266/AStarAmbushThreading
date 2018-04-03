#include "World.h"

World::World() {
	test = BaseObject{ Vector2f{0, 0}, 10, 10, SDL_Color{100, 100, 0, 255} };
}

void World::update(float deltaTime) {

}

void World::draw(SDL_Renderer *renderer) {
	test.draw(renderer);
}