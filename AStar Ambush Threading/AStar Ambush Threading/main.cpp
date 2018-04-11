#include "World.h"

int worker(void*);
World* theWorld;

int main(int argc, char* argv[]) {
	SDL_Window* window = SDL_CreateWindow("TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 700, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_Event *e = new SDL_Event();

	EventListener *eventListener = new EventListener;

	bool running = true;

	const float FPS = 120;
	const float timePerFrame = 1.0f / FPS;
	float currentTime = 0;
	float lastTime = 0;
	float deltaTime = 0;

	//delta_time = &deltaTime;

	InputHandler input(eventListener);
	World world(eventListener, &deltaTime);

	theWorld = &world;

	SDL_Thread* threadA = SDL_CreateThread(worker, "Thread A", (void*)"Thread A");
	SDL_Thread* threadB = SDL_CreateThread(worker, "Thread B", (void*)"Thread B");
	//SDL_Thread* threadC = SDL_CreateThread(pathing, "Thread C", (void*)"Thread C");
	//SDL_Thread* threadD = SDL_CreateThread(pathing, "Thread D", (void*)"Thread D");
	//SDL_Thread* threadE = SDL_CreateThread(collisions, "Thread E", (void*)"Thread E");
	//SDL_Thread* threadF = SDL_CreateThread(collisions, "Thread F", (void*)"Thread F");
	//SDL_Thread* threadG = SDL_CreateThread(collisions, "Thread G", (void*)"Thread G");
	//SDL_Thread* threadH = SDL_CreateThread(collisions, "Thread H", (void*)"Thread H");

	while (running) {
		currentTime = SDL_GetTicks();

		deltaTime = (currentTime - lastTime) / 1000;

		if (deltaTime >= timePerFrame) {
			std::cout << deltaTime << std::endl;
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderClear(renderer);

			input.handleInput(e);

			world.draw(renderer);
			//world.update(deltaTime);
			world.updatePlayer();

			lastTime = currentTime;
		}

		SDL_RenderPresent(renderer);
	}

	return 0;
}

int worker(void*) {
	//Lock
	SDL_SemWait(collisionLock);

	wallCollisionIndex++;

	int wallIndex = wallCollisionIndex;

	//Unlock
	SDL_SemPost(collisionLock);

	while (true) {
		if (wallCollisionIndex == 1) {
			for (int i = wallIndex; i < tiles->size(); i += wallCollisionIndex + 1) {
				//// locked because if not, it may detect colliding with multiple tiles at the same time and end up pushing itself away from the wall
				SDL_SemWait(collisionLock);

				theWorld->collisions(i);

				SDL_SemPost(collisionLock);
			}
		}
	}

	return 0;
}