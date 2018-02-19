//Using SDL and standard IO
#include <SDL.h>
#include <ostream>
#include <iostream>

#include "InputHandler.h"
#include "RenderManager.h"
#include "Matrix.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const std::string TITLE = "Liniair Algebra - Spaceship";

#undef main
int main(int argc, char *argv[]) {
	// init through a initalizer_list
	const Matrix<int, 4, 4> rectangle(
		{
			{100, 150, 150, 150},
			{100, 100, 200, 200},
			{100, 200, 200, 200},
			{1	 , 1  , 1  , 1}
		}
	);

	const Matrix<int, 4, 4> scalarMultiply(
		{
			{2, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1}
		}
	);

	const Matrix<int, 4, 4> scalarTranslate(
		{
			{1, 0, 0, 10},
			{0, 1, 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1}
		}
	);

	// First multiply x then translate x
	const auto result = scalarTranslate * scalarMultiply * rectangle;

	std::cout << rectangle << std::endl << std::endl;
	std::cout << scalarMultiply << std::endl << std::endl;
	std::cout << scalarTranslate << std::endl << std::endl;
	std::cout << result << std::endl;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
	//	printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		SDL_PumpEvents();
		RenderManager::GetInstance().CreateWindow(TITLE, false, SCREEN_WIDTH, SCREEN_HEIGHT);

		auto running = true;
		while (running)
		{
			auto& input_h = InputHandler::instance();

			// Handle events
			while (input_h.poll())
			{
				if(input_h.is_event(InputHandler::events::EVENT_QUIT))
				{
					running = false;
				}

				if (input_h.is_key_pressed(InputHandler::keys::KEY_UP_MOVE))
				{
					std::cout << "Moving up" << std::endl;
				}
			}
		}
	}

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}