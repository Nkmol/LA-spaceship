#include "RenderManager.h"
#include <iostream>
#include "Vector3d.h"
#include <vector>

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

void RenderManager::Draw(const Vector2d<double>& begin, const Vector2d<double>& end)
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(this->_renderer, begin.GetX(), begin.GetY(), end.GetX(), end.GetY());
}

void RenderManager::DrawPoints(const std::vector<Vector3d<double>>& points, const std::vector<std::pair<unsigned int, unsigned int>>& lines)
{
	for (auto& line : lines)
	{
		auto& point1 = points[line.first];
		auto& point2 = points[line.second];

		Draw(
			{ point1.GetX(), point1.GetY() }, 
			{ point2.GetX(), point2.GetY() }
		);
	}
}

void RenderManager::Refresh()
{
	SDL_RenderPresent(_renderer);
}


void RenderManager::Clear()
{
	SDL_SetRenderDrawColor(_renderer, 0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(_renderer);
}
