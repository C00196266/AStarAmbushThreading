#pragma once

#include <SDL.h>
#include <SDL_thread.h>
#include <random>

class Threadpool {
public:
	Threadpool();
	Threadpool(int noOfThreads);

	void worker(void* data);
private:
	int m_noOfThreads;
	SDL_sem* m_lock;
};