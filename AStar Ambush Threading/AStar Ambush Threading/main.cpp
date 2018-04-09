#include "World.h"

int main(int argc, char* argv[]) {
	SDL_Window* window = SDL_CreateWindow("TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_Event *e = new SDL_Event();

	EventListener *eventListener = new EventListener;

	InputHandler input(eventListener);
	World world(eventListener);

	SDL_Thread* threadA = SDL_CreateThread(collisions, "Thread A", (void*)"Thread A");
	SDL_Thread* threadB = SDL_CreateThread(collisions, "Thread B", (void*)"Thread B");
	SDL_Thread* threadC = SDL_CreateThread(pathing, "Thread C", (void*)"Thread C");
	SDL_Thread* threadD = SDL_CreateThread(pathing, "Thread D", (void*)"Thread D");

	bool running = true;

	const float FPS = 60;
	const float timePerFrame = 1.0f / FPS;
	float currentTime = 0;
	float lastTime = 0;
	float deltaTime = 0;

	while (running) {
		currentTime = SDL_GetTicks();

		deltaTime = (currentTime - lastTime) / 1000;

		if (deltaTime > timePerFrame) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderClear(renderer);

			input.handleInput(e);

			world.draw(renderer);
			world.update(deltaTime);

			lastTime = currentTime;
		}

		SDL_RenderPresent(renderer);
	}

	return 0;
}