#pragma once
#include "Singleton.h"
#include <string>
#include <SDL.h>
#include "Matrix.h"
#include "Vector2d.h"
#include "Vector3d.h"
#include <vector>

class RenderManager : public Singleton<RenderManager>
{
public:
	void CreateWindow(const std::string& title, bool fullscreen, const int width, const int height);
	void Draw(const Vector2d<double>& begin, const Vector2d<double>& end);
	void DrawPoints(const std::vector<Vector3d<double>>& points, const std::vector<std::pair<unsigned, unsigned>>& lines);
	void Refresh();
	void Clear();

private:
	SDL_Window* _window = nullptr;
	SDL_Renderer* _renderer = nullptr;
	static RenderManager* _instance;
};



