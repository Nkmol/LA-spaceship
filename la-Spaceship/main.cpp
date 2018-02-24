//Using SDL and standard IO
#include <SDL.h>
#include <ostream>
#include <iostream>

#include "InputHandler.h"
#include "RenderManager.h"
#include "MatrixFactory.h"
#include "MatrixHelper.h"
#include "Matrix.h"
#include "Object.h"
#include "Camera.h"

#undef main
int main(int argc, char *argv[]) {
	// init through a initalizer_list
	const Matrix<double, 4, 16> cube(
        {
            {100, 150, 150, 150, 150, 100, 100, 100, 100, 100, 150, 150, 150, 150, 100, 100},
            {100, 100, 100, 100, 150, 150, 150, 150, 100, 100, 100, 150, 150, 150, 150, 100},
            {100, 100, 150, 100, 100, 100, 150, 100, 100, 150, 150, 150, 100, 150, 150, 150},
            {1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  }
        }
    );

	Object test_object;

	auto m = test_object.ToMatrix<4>();
	test_object.FromMatrix(m);

	MatrixFactory factory;
	MatrixHelper helper;

	Camera camera { 
		 {
            {0},
            {250},
            {0},
            {1}
        },
        {
            {250},
            {0},
            {250},
            {1}
        },
		{
			{0},
			{1},
			{0},
			{1}
		}
	};

	const auto projectedMatrix = camera.ProjectMatrix(cube);

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
	//	printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		SDL_PumpEvents();
		RenderManager::GetInstance().CreateWindow(Config::TITLE, false, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);

		auto running = true;
		while (running)
		{
			auto& inputHandler = InputHandler::instance();

			// Handle events
			while (inputHandler.poll())
			{
				if(inputHandler.is_event(InputHandler::events::EVENT_QUIT))
				{
					running = false;
				}

				if (inputHandler.is_key_pressed(InputHandler::keys::KEY_UP_MOVE))
				{
					std::cout << "Moving up" << std::endl;
				}
			}

			test_object.FromMatrix(
				projectedMatrix
			);

			RenderManager::GetInstance().Clear();
			test_object.Draw();
			RenderManager::GetInstance().Refresh();
		}
	}

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}