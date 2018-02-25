//Using SDL and standard IO
#include <SDL.h>
#include <iostream>
#include <ostream>
#include "Camera.h"
#include "InputHandler.h"
#include "Matrix.h"
#include "MatrixFactory.h"
#include "MatrixHelper.h"
#include "Models.h"
#include "MoveableObject.h"
#include "Object.h"
#include "PulsingObject.h"
#include "RenderManager.h"
#include "Spaceship.h"

#undef main
int main(int /*argc*/, char* /*argv*/[])
{
	MatrixFactory factory;
	MatrixHelper helper;

	// Create spaceship
	Spaceship spaceship{ 200, 200, 200 };

	PulsingObject pulsingObject({100, 100, 100}, {50, 50, 50}, Models::Cube::matrix);
	pulsingObject.SetLines(Models::Cube::lines);

	// Ship camera settings
		Camera camera { 
		 {
            {0},
            {450},
            {0},
            {1}
        },
        {
            {300},
            {0},
            {300},
            {1}
        },
		{
			{0},
			{-1},
			{0},
			{1}
		}
	};

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
				if (inputHandler.is_event(InputHandler::events::EVENT_QUIT))
				{
					running = false;
				}

				// TODO(Sander Mol): use the current camera angel to calculate the movement?
				if (inputHandler.is_key_pressed(InputHandler::keys::KEY_UP_MOVE))
				{
					std::cout << "Moving up" << std::endl;
					spaceship.Rotate(10, Z);
				}
				else if (inputHandler.is_key_pressed(InputHandler::keys::KEY_DOWN_MOVE))
				{
					std::cout << "Moving down" << std::endl;
					spaceship.Rotate(-10, Z);
				}
				else if (inputHandler.is_key_pressed(InputHandler::keys::KEY_LEFT_MOVE))
				{
					std::cout << "Moving left" << std::endl;
					spaceship.Rotate(10, X);
				}
				else if (inputHandler.is_key_pressed(InputHandler::keys::KEY_RIGHT_MOVE))
				{
					std::cout << "Moving right" << std::endl;
					spaceship.Rotate(-10, X);
				}
				else if (inputHandler.is_key_pressed(InputHandler::keys::KEY_ROTATE_LEFT))
				{
					std::cout << "Rotate left" << std::endl;
					spaceship.Rotate(10, Y);
				}
				else if (inputHandler.is_key_pressed(InputHandler::keys::KEY_ROTATE_RIGHT))
				{
					std::cout << "Rotate right" << std::endl;
					spaceship.Rotate(-10, Y);
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

				if (inputHandler.is_key_pressed(InputHandler::keys::KEY_UP_LOOKAT_MOVE))
				{
					std::cout << "Lookat Moving up" << std::endl;
					camera.SetLookAt(factory.CreateTranslationMatrix(0, 1, 0) * camera.GetLookAt());
				}
				else if (inputHandler.is_key_pressed(InputHandler::keys::KEY_DOWN_LOOKAT_MOVE))
				{
					std::cout << "Lookat Moving up" << std::endl;
					camera.SetLookAt(factory.CreateTranslationMatrix(0, -1, 0) * camera.GetLookAt());

				}
				else if (inputHandler.is_key_pressed(InputHandler::keys::KEY_LEFT_LOOKAT_MOVE))
				{
					std::cout << "Lookat Moving up" << std::endl;
					camera.SetLookAt(factory.CreateTranslationMatrix(-1, 0, 0) * camera.GetLookAt());

				}
				else if (inputHandler.is_key_pressed(InputHandler::keys::KEY_RIGHT_LOOKAT_MOVE))
				{
					std::cout << "Lookat Moving up" << std::endl;
					camera.SetLookAt(factory.CreateTranslationMatrix(1, 0, 0) * camera.GetLookAt());
				}


				if (inputHandler.is_key_pressed(InputHandler::keys::KEY_SHOOT))
				{
 					spaceship.Shoot();
				}

				if (inputHandler.is_key_pressed(InputHandler::keys::KEY_ACCELERATE))
				{
					spaceship.Accelerate(1);
				}
				else if (inputHandler.is_key_pressed(InputHandler::keys::KEY_BRAKE))
				{
					spaceship.Accelerate(-1);
				}

				if (inputHandler.is_key_pressed(InputHandler::keys::KEY_HELP))
				{
					spaceship.ToggleHelpLines();
				}
			}

			RenderManager::GetInstance().Clear();

			spaceship.Update();
			spaceship.Draw(camera);
			pulsingObject.Update();
			pulsingObject.Draw(camera);

			RenderManager::GetInstance().Refresh();

			// Quick fix FPS lock
			SDL_Delay(16.67);
		}
	}

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}
