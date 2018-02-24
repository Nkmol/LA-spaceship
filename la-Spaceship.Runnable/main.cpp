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

				// TODO use the current camera angel to calculate the movement?
				if (inputHandler.is_key_pressed(InputHandler::keys::KEY_UP_MOVE))
				{
					std::cout << "Moving up" << std::endl;
					cube = factory.CreateTranslationMatrix(0, 1, 0) * cube;
				}
				else if (inputHandler.is_key_pressed(InputHandler::keys::KEY_DOWN_MOVE))
				{
					std::cout << "Moving down" << std::endl;
					cube = factory.CreateTranslationMatrix(0, -1, 0) * cube;
				}
				else if (inputHandler.is_key_pressed(InputHandler::keys::KEY_LEFT_MOVE))
				{
					std::cout << "Moving left" << std::endl;
					cube = factory.CreateTranslationMatrix(-1, 0, 0) * cube;
				}
				else if (inputHandler.is_key_pressed(InputHandler::keys::KEY_RIGHT_MOVE))
				{
					std::cout << "Moving right" << std::endl;

				/*	try
					{
						double collective_x = 0;
						double collective_y = 0;
						double collective_z = 0;

						for (int i = 0; i < cube.GetRow(0).size(); i++)
						{
							collective_x += cube.GetVal(0, i);
							collective_y += cube.GetVal(1, i);
							collective_z += cube.GetVal(2, 1);
						}

						double center_x = collective_x / cube.GetRow(0).size();
						double center_y = collective_y / cube.GetRow(1).size();
						double center_z = collective_z / cube.GetRow(2).size();
					}
					catch(...)
					{
						
					}
*/
					cube = factory.CreateTranslationMatrix(1, 0, 0) * cube;
				}

				if (inputHandler.is_key_pressed(InputHandler::keys::KEY_UP_CAMERA_MOVE))
				{
					std::cout << "Camera Moving up" << std::endl;
					camera.SetEye(factory.CreateTranslationMatrix(0, 1, 0) * camera.GetEye());

				}
				else if (inputHandler.is_key_pressed(InputHandler::keys::KEY_DOWN_CAMERA_MOVE))
				{
					std::cout << "Camera Moving down" << std::endl;
					camera.SetEye(factory.CreateTranslationMatrix(0, -1, 0) * camera.GetEye());
				}
				else if (inputHandler.is_key_pressed(InputHandler::keys::KEY_LEFT_CAMERA_MOVE))
				{
					std::cout << "Camera Moving left" << std::endl;
					camera.SetEye(factory.CreateTranslationMatrix(-1, 0, 0) * camera.GetEye());
				}
				else if (inputHandler.is_key_pressed(InputHandler::keys::KEY_RIGHT_CAMERA_MOVE))
				{
					std::cout << "Camera Moving right" << std::endl;
					camera.SetEye(factory.CreateTranslationMatrix(1, 0, 0) * camera.GetEye());
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