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
#include "PulsingObject.h"

#undef main
int main(int argc, char *argv[]) {
	
	MatrixFactory factory;
	MatrixHelper helper;

	// init through a initalizer_list
	Matrix<double, 4, 4> cube(
        {
			/*x*/{ 0, 1, 1, 0},
			/*y*/{ 0, 0, 1, 1},
			/*z*/{ 0, 0, 0, 0},

			/*w*/{ 1, 1, 1, 1}
        }
    );
	cube = factory.CreateTranslationMatrix(100, 100, 100) * factory.CreateScaleMatrix(50, 50, 50) * cube;

	PulsingObject testObject;
	testObject.SetTransform(cube);
	testObject.SetLines({
		{0, 1},
		{1, 2},
		{2, 3},
		{3, 0}
	});


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

	auto projectedMatrix = camera.ProjectMatrix(cube);

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
					std::cout << "UP" << std::endl;
				}
			}

			RenderManager::GetInstance().Clear();
			//testObject.Update();
			projectedMatrix = camera.ProjectMatrix(Object::ToMatrix<4>(testObject.GetPoints()));
			RenderManager::GetInstance().DrawPoints(Object::ToPoints(projectedMatrix), testObject.GetLines());
			//RenderManager::GetInstance().DrawPoints(testObject.GetPoints(), testObject._lines);
			RenderManager::GetInstance().Refresh();

			// Quick fix FPS lock
			SDL_Delay(16.67);
		}
	}

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}