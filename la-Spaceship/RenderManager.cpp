#include "RenderManager.h"
#include <iostream>

void RenderManager::CreateWindow(const std::string& title, bool fullscreen, const int width, const int height)
{
	//auto flags = SDL_RENDERER_ACCELERATED;
	if(fullscreen)
	{
		//flags = SDL_WINDOW_FULLSCREEN | SDL_RENDERER_ACCELERATED;
	}

	const auto resp = SDL_CreateWindowAndRenderer(width, height, 0,&this->_window, &this->_renderer);
	if (resp != 0) {
		std::cout << SDL_GetError() << std::endl;
	}
	SDL_SetWindowTitle(this->_window, title.c_str());
}
