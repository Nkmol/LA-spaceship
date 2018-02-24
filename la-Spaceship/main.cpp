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
	Matrix<double, 4, 16> cube(
        {
            {100, 150, 150, 150, 150, 100, 100, 100, 100, 100, 150, 150, 150, 150, 100, 100},
            {100, 100, 100, 100, 150, 150, 150, 150, 100, 100, 100, 150, 150, 150, 150, 100},
            {100, 100, 150, 100, 100, 100, 150, 100, 100, 150, 150, 150, 100, 150, 150, 150},
            {1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  }
        }
    );


	Matrix<double, 4, 16> engine(
		{
			{0, 0, 0, 0, 0, 40, 40, 0, 40, 40, 0, 40, 40, 0, 40, 40},
			{0, 0, 100, 100, 0, 10, 10, 0, 10, 90, 100, 90, 90, 100, 90, 10},
			{30, 110, 110, 30, 30, 30, 110, 110, 110, 110, 110, 110, 30, 30, 30, 30},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
		}
	);

	Matrix<double, 4, 16> body(
		{
			{40, 40, 140, 40, 40, 140, 40, 40, 140, 40, 40, 140, 140, 140, 140, 140},
			{10, 10, 10, 10, 90, 90, 90, 90, 90, 90, 10, 10, 10, 90, 90, 10},
			{30, 110, 110, 110, 110, 110, 110, 30, 30, 30, 30, 30, 110, 110, 30, 30},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
		}
	);

	Matrix<double, 4, 8> head(
		{
			{200, 140, 200, 140, 200, 140, 200, 140},
			{50, 10, 50, 90, 50, 90, 50, 10},
			{70, 30, 70, 110, 70, 30, 70, 110},
			{1, 1, 1, 1, 1, 1, 1, 1}
		}
	);

	Matrix<double, 4, 3> left_wing(
		{
			{40, 40, 140},
			{10, 10, 10},
			{40, 0, 40},
			{1,  1, 1 }
		}
	);
	Matrix<double, 4, 3> right_wing(
	{
		{ 40, 40, 140 },
		{ 10, 10, 10 },
		{ 100, 140, 100 },
		{ 1,  1, 1 }
	}
	);

	Matrix<double, 4, 6> source_edges(
		{
			{0, 1000, 0, 0, 0, 0},
			{0, 0, 0, 1000, 0, 0},
			{0, 0, 0, 0, 0, 1000},
			{1 ,1, 1, 1, 1, 1   }
		}
	);


	Object test_object;
	Object source_object;

	Object engine_object;
	Object body_object;
	Object head_object;
	Object left_wing_object;
	Object right_wing_object;

	MatrixFactory factory;
	MatrixHelper helper;
	

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
			{1},
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

					double center_x;
					double center_y;
					double center_z;

					try
					{
						double collective_x = 0;
						double collective_y = 0;
						double collective_z = 0;

						for (int i = 0; i < body.GetRow(0).size(); i++)
						{
							collective_x += body.GetVal(0, i);
							collective_y += body.GetVal(1, i);
							collective_z += body.GetVal(2, 1);
						}

						center_x = collective_x / body.GetRow(0).size();
						center_y = collective_y / body.GetRow(1).size();
						center_z = collective_z / body.GetRow(2).size();
					}
					catch(...)
					{
						
					}

					body = helper.Rotate(10, body, { 90, 50, 70 }, { 90, 51, 70 });

					//cube = factory.CreateTranslationMatrix(1, 0, 0) * cube;
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

			const auto projectedMatrix = camera.ProjectMatrix(cube);
			const auto projected_source_edges = camera.ProjectMatrix(source_edges);

			const auto projected_engine = camera.ProjectMatrix(engine);
			const auto projected_body = camera.ProjectMatrix(body);
			const auto projected_head = camera.ProjectMatrix(head);
			const auto projected_left_wing = camera.ProjectMatrix(left_wing);
			const auto projected_right_wing = camera.ProjectMatrix(right_wing);


			test_object.SetTransform(
				projectedMatrix
			);

			source_object.SetTransform(
				projected_source_edges
			);

			engine_object.SetTransform(
				projected_engine
			);

			body_object.SetTransform(
				projected_body
			);

			head_object.SetTransform(
				projected_head
			);

			left_wing_object.SetTransform(
				projected_left_wing
			);

			right_wing_object.SetTransform(
				projected_right_wing
			);

			RenderManager::GetInstance().Clear();
			//test_object.Draw();

			// Spaceship
			engine_object.Draw();
			body_object.Draw();
			head_object.Draw();
			left_wing_object.Draw();
			right_wing_object.Draw();

		//	source_object.Draw();
			RenderManager::GetInstance().Refresh();
		}
	}

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}