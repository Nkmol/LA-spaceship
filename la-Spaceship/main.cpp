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

	auto projected_matrix = camera.ProjectMatrix(cube);

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
	//	printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		SDL_PumpEvents();
		RenderManager::GetInstance().CreateWindow(Config::TITLE, false, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);

		// TODO for testing
		double scale = 1.0001;

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

			RenderManager::GetInstance().Clear();
			test_object.Draw();
			RenderManager::GetInstance().Refresh();

			const auto scale_matrix = factory.CreateScaleMatrix(scale, scale, scale);
			const auto m = test_object.ToMatrix<4>();

			const auto r = scale_matrix * m; // TODO translation (it is still just a test though)

			test_object.FromMatrix(
				projected_matrix
			);
		}
	}

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}