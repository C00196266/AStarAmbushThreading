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

				case SDLK_a:
					m_eventListener->pressedA = true;

				case SDLK_s:
					m_eventListener->pressedS = true;

				case SDLK_d:
					m_eventListener->pressedD = true;

				case SDLK_LEFT:
					m_eventListener->pressedLeft = true;

				case SDLK_RIGHT:
					m_eventListener->pressedRight = true;

				case SDLK_UP:
					m_eventListener->pressedUp = true;

				case SDLK_DOWN:
					m_eventListener->pressedDown = true;
				}
			}

		case SDL_KEYUP:
			if (!e->key.repeat) {
				switch (e->key.keysym.sym) {
				case SDLK_w:
					m_eventListener->pressedW = false;

				case SDLK_a:
					m_eventListener->pressedA = false;

				case SDLK_s:
					m_eventListener->pressedS = false;

				case SDLK_d:
					m_eventListener->pressedD = false;

				case SDLK_LEFT:
					m_eventListener->pressedLeft = false;

				case SDLK_RIGHT:
					m_eventListener->pressedRight = false;

				case SDLK_UP:
					m_eventListener->pressedUp = false;

				case SDLK_DOWN:
					m_eventListener->pressedDown = false;
				}
			}
		}
	}
}