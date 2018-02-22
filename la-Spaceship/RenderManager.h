#pragma once
#include "Singleton.h"
#include <string>
#include <SDL.h>
#include "Matrix.h"
#include "Vector2d.h"

class RenderManager : public Singleton<RenderManager>
{
public:
	void CreateWindow(const std::string& title, bool fullscreen, const int width, const int height);

	template<int size>
	void Draw(Matrix<double, size, 4> m)
	{
		
	}

	void Draw(const Vector2d<double>& begin, const Vector2d<double>& end);
	void Refresh();
	void Clear();

private:
	SDL_Window* _window = nullptr;
	SDL_Renderer* _renderer = nullptr;
	static RenderManager* _instance;
};



