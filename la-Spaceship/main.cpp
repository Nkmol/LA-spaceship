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


	//Matrix<double, 4, 16> engine(
	//	{
	//		{0, 0, 0, 0, 0, 40, 40, 0, 40, 40, 0, 40, 40, 0, 40, 40},
	//		{0, 0, 100, 100, 0, 10, 10, 0, 10, 90, 100, 90, 90, 100, 90, 10},
	//		{30, 110, 110, 30, 30, 30, 110, 110, 110, 110, 110, 110, 30, 30, 30, 30},
	//		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	//	}
	//);

	
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
				if (inputHandler.is_event(InputHandler::events::EVENT_QUIT))
				{
					running = false;
				}
			}


			const auto projectedMatrix = camera.ProjectMatrix(cube);
			const auto projected_source_edges = camera.ProjectMatrix(source_edges);

			/*const auto projected_engine = camera.ProjectMatrix(engine);*/
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

		/*	engine_object.SetTransform(
				projected_engine
			);*/

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
			//engine_object.Draw();
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