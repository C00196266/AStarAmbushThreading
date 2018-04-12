#include "InputHandler.h"

InputHandler::InputHandler(EventListener *e) {
	m_eventListener = e;
}

void InputHandler::handleInput(SDL_Event *e) {
	while (SDL_PollEvent(e)) {
		switch (e->type) {
		case SDL_KEYDOWN:
			if (!e->key.repeat) {
				switch (e->key.keysym.sym) {
				case SDLK_w:
					m_eventListener->pressedW = true;
					break;

				case SDLK_a:
					m_eventListener->pressedA = true;
					break;

				case SDLK_s:
					m_eventListener->pressedS = true;
					break;

				case SDLK_d:
					m_eventListener->pressedD = true;
					break;

				case SDLK_LEFT:
					m_eventListener->pressedLeft = true;
					break;

				case SDLK_RIGHT:
					m_eventListener->pressedRight = true;
					break;

				case SDLK_UP:
					m_eventListener->pressedUp = true;
					break;

				case SDLK_DOWN:
					m_eventListener->pressedDown = true;
					break;

				case SDLK_SPACE:
					m_eventListener->pressedSpace = true;
					break;
				}
				break;
			}

		case SDL_KEYUP:
			if (!e->key.repeat) {
				switch (e->key.keysym.sym) {
				case SDLK_w:
					m_eventListener->pressedW = false;
					break;

				case SDLK_a:
					m_eventListener->pressedA = false;
					break;

				case SDLK_s:
					m_eventListener->pressedS = false;
					break;

				case SDLK_d:
					m_eventListener->pressedD = false;
					break;

				case SDLK_LEFT:
					m_eventListener->pressedLeft = false;
					break;

				case SDLK_RIGHT:
					m_eventListener->pressedRight = false;
					break;

				case SDLK_UP:
					m_eventListener->pressedUp = false;
					break;

				case SDLK_DOWN:
					m_eventListener->pressedDown = false;
					break;

				case SDLK_SPACE:
					m_eventListener->pressedSpace = false;
					break;
				}
				break;
			}
		}
	}
}