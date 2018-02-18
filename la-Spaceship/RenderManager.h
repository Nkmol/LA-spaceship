#pragma once
#include "Singleton.h"
#include <string>
#include <SDL.h>

class RenderManager : public Singleton<RenderManager>
{
public:
	void CreateWindow(const std::string& title, bool fullscreen, const int width, const int height);
private:
	SDL_Window* _window = nullptr;
	SDL_Renderer* _renderer = nullptr;
	static RenderManager* _instance;
};

