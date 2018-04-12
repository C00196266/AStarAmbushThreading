#include "World.h"

// these need to be global, due to SDL threads taking C style functions as arguments, as opposed to C++ member functions

int worker(void*);
int aStarWorker(void*);
World* theWorld;
int numberOfWorkerThreads;
int numberOfAStarThreads;
SDL_Renderer* theRenderer;
SDL_sem* lock;

int main(int argc, char* argv[]) {
	SDL_Window* window = SDL_CreateWindow("TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 700, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_Event *e = new SDL_Event();

	numberOfWorkerThreads = 0;
	numberOfAStarThreads = 0;
	theRenderer = renderer;
	lock = SDL_CreateSemaphore(1);

	EventListener *eventListener = new EventListener;

	bool running = true;

	const float FPS = 60;
	const float timePerFrame = 1.0f / FPS;
	float currentTime = 0;
	float lastTime = 0;
	float deltaTime = 0;

	InputHandler input(eventListener);
	World world(eventListener, &deltaTime, renderer);

	theWorld = &world;

	SDL_Thread* threadA = SDL_CreateThread(worker, "Thread A", (void*)"Thread A");
	SDL_Thread* threadB = SDL_CreateThread(worker, "Thread B", (void*)"Thread B");
	SDL_Thread* threadC = SDL_CreateThread(worker, "Thread C", (void*)"Thread C");
	SDL_Thread* threadD = SDL_CreateThread(aStarWorker, "Thread D", (void*)"Thread D");

	while (running) {
		currentTime = SDL_GetTicks();

		deltaTime = (currentTime - lastTime) / 1000;

		if (deltaTime >= timePerFrame) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderClear(renderer);

			input.handleInput(e);

			world.draw(renderer);

			lastTime = currentTime;
		}

		SDL_RenderPresent(renderer);
	}

	return 0;
}

int worker(void*) {
	SDL_Delay(1000);

	//Lock
	SDL_SemWait(lock);

	// makes sure to correctly set ID
	int threadID = numberOfWorkerThreads;
	numberOfWorkerThreads++;

	//Unlock
	SDL_SemPost(lock);

	while (true) {
		// only one thread updates the player
		if (threadID == 0) {
			theWorld->updatePlayer();
		}
		else if (threadID == 1) {
			theWorld->updateAStar();
		}

		for (int i = threadID; i < theWorld->getNPCs().size(); i += numberOfWorkerThreads) {
			theWorld->updateNPC(i);
		}
	
		for (int i = threadID; i < theWorld->getTiles().size(); i += numberOfWorkerThreads) {
			// locked because if not, it may detect colliding with multiple tiles at the same time and end up pushing itself away from the wall
			SDL_SemWait(lock);

			theWorld->collisions(i);

			SDL_SemPost(lock);
		}
	}

	return 0;
}

int aStarWorker(void*) {
	//Lock
	SDL_SemWait(lock);

	// makes sure to correctly set ID
	int threadID = numberOfAStarThreads;
	numberOfAStarThreads++;

	//Unlock
	SDL_SemPost(lock);

	while (true) {
		for (int i = threadID; i < theWorld->getNPCs().size(); i += numberOfAStarThreads) {
			// locked because if not, it may detect colliding with multiple tiles at the same time and end up pushing itself away from the wall
			theWorld->getNPCs().at(i)->calculatePath();
		}
	}

	return 0;
}