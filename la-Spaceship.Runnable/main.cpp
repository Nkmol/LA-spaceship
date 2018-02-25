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
#include "MoveableObject.h"
#include "Models.h"
#include "Spaceship.h"

#undef main
int main(int argc, char *argv[]) {
	

	MatrixFactory factory;
	MatrixHelper helper;

	PulsingObject pulsingObject({100, 100, 100}, {50, 50, 50}, Model::Cube);
	pulsingObject.SetLines({
		{0, 1},
		{1, 2},
		{2, 3},
		{3, 0},

		{1, 4},
		{4, 5},
		{5, 2},
		{5, 6},
		{6, 7},
		{6, 3},
		{7, 4},
		{7, 0},
	});

	MoveableObject bullet({100, 100, 100}, {5, 5, 15}, Model::Cube);
	bullet.SetLines(pulsingObject.GetLines());

	// Create spaceship
	Spaceship spaceship{ 0,0,0 };


	Matrix<double, 4, 6> source_edges(
	{
		{ 0, 1000, 0, 0, 0, 0 },
		{ 0, 0, 0, 1000, 0, 0 },
		{ 0, 0, 0, 0, 0, 1000 },
		{ 1 ,1, 1, 1, 1, 1 }
	}
	);

	// Ship camera settings
		Camera camera { 
		 {
            {100},
            {150},
            {250},
            {1}
        },
        {
            {100},
            {0},
            {0},
            {1}
        },
		{
			{0},
			{-1},
			{0},
			{1}
		}
	};

	auto cube = Model::Cube;
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
				if (inputHandler.is_event(InputHandler::events::EVENT_QUIT))
				{
					running = false;
				}

				// TODO use the current camera angel to calculate the movement?
				if (inputHandler.is_key_pressed(InputHandler::keys::KEY_UP_MOVE))
				{
					std::cout << "Moving up" << std::endl;
					spaceship.Rotate(-10, X);
				}
				else if (inputHandler.is_key_pressed(InputHandler::keys::KEY_DOWN_MOVE))
				{
					std::cout << "Moving down" << std::endl;
					spaceship.Rotate(10, X);
				}
				else if (inputHandler.is_key_pressed(InputHandler::keys::KEY_LEFT_MOVE))
				{
					std::cout << "Moving left" << std::endl;
					spaceship.Rotate(-10, Y);
				}
				else if (inputHandler.is_key_pressed(InputHandler::keys::KEY_RIGHT_MOVE))
				{
					std::cout << "Moving right" << std::endl;
					spaceship.Rotate(10, Y);
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

			pulsingObject.Update();
			pulsingObject.Draw(camera);
			
			bullet.Update();
			bullet.Draw(camera);
			/*Matrix<double, 4, 2> rotate_test
			{
				{90, 90},
				{10, 90},
				{70, 70},
				{1 , 1 }
			};*/

			/*Object rotate_line;

			rotate_line.SetTransform(rotate_test);

			rotate_line.SetLines({ { 0, 1 } });

			const auto projected_rotate_line = camera.ProjectMatrix(Object::ToMatrix<2>(rotate_line.GetPoints()));*/


			//spaceship.Draw(camera);
			//pulsingObject.Draw(camera);

			RenderManager::GetInstance().Refresh();

			// Quick fix FPS lock
			SDL_Delay(16.67);
		}
	}

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}