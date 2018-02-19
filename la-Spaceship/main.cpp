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

	//std::vector<Vector3d> rectangle_points_3d;

	//rectangle_points_3d.emplace_back(Vector3d{ 100, 100, 100 });
	//rectangle_points_3d.emplace_back(Vector3d{ 150 ,100, 200 });
	//rectangle_points_3d.emplace_back(Vector3d{ 150, 200, 200 });
	//rectangle_points_3d.emplace_back(Vector3d{ 150, 200, 200 });

	//Matrix3d rectangle{ rectangle_points_3d, false };

	//std::vector<Vector3d> collection;

	//collection.push_back(Vector3d{ 2, 0, 0 });
	//collection.push_back(Vector3d{ 0, 3, 0 });
	//collection.push_back(Vector3d{ 0, 0, 4 });

	//Matrix3d scaling_matrix{ collection, true };

	//Matrix3d a = rectangle.dot(scaling_matrix); // TODO normale notatie = scaling . rectangle      (niet rectangle . scaling)

	//std::cout << rectangle << std::endl;
	//std::cout << scaling_matrix << std::endl;
	//std::cout << a << std::endl;

	Matrix<int, 4, 4> rectangle;
	rectangle.SetRow(0, {100, 150, 150, 150});
	rectangle.SetRow(1, {100, 100, 200, 200});
	rectangle.SetRow(2, {100, 200, 200, 200});
	rectangle.SetRow(3, {1	 , 1  , 1  , 1});

	Matrix<int, 4, 4> scalar;
	scalar.SetRow(0, {2, 0, 0, 0});
	scalar.SetRow(1, {0, 1, 0, 0});
	scalar.SetRow(2, {0, 0, 1, 0});
	scalar.SetRow(3, {0, 0, 0, 1});

	auto result = rectangle * scalar;

	std::cout << rectangle << std::endl << std::endl;
	std::cout << scalar << std::endl << std::endl;
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