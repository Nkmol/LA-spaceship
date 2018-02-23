//Using SDL and standard IO
#include <SDL.h>
#include <ostream>
#include <iostream>

#include "InputHandler.h"
#include "RenderManager.h"
#include "MatrixFactory.h"
#include "MatrixHelper.h"
#include "Matrix3D.h"
#include "Object.h"
#include "Camera.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const std::string TITLE = "Liniair Algebra - Spaceship";

#undef main
int main(int argc, char *argv[]) {
	// init through a initalizer_list
	const Matrix<double, 4, 4> rectangle(
		{
			{0,  50, 50,  0},
			{50, 50, 50, 50},
			{0,  0,  50, 50},
			{1 , 1 , 1 , 1 }
		}
	);

	Object test_object;

	test_object.SetTransform({ 
		{100, 100, 0}, 
		{100, 150, 0}, 
		{150, 150, 0}, 
		{150, 100, 0} 
	});

	auto m = test_object.ToMatrix<4>();
	test_object.FromMatrix(m);


	MatrixFactory factory;
	MatrixHelper helper;

	const auto scalarMultiply = factory.CreateScaleMatrix(2, 1, 1);
	const auto scalarTranslate = factory.CreateTranslationMatrix(10);

	// First multiply x then translate x
	const auto result = scalarTranslate * scalarMultiply * rectangle;
	
	const auto rotated_rectangle = helper.Rotate(180, rectangle, {0, 0, 0}, {50, 0, 0}); // TODO WIP, Test after projection matrix is done

	//std::cout << rectangle << std::endl << std::endl;
	//std::cout << scalarMultiply << std::endl << std::endl;
	//std::cout << scalarTranslate << std::endl << std::endl;
	//std::cout << result << std::endl;
	//std::cout << rotated_rectangle << std::endl; //TODO WIP

	//Inproduct
	const Matrix3D<double, 1> point1(
		{
			{5},
			{5},
			{5},
			{1}
		}
	);
	const Matrix3D<double, 1> point2(
		{
			{7},
			{7},
			{7},
			{1}
		}
	);

	std::cout << point1 << std::endl;
	std::cout << point2 << std::endl;

	std::cout << "Dot of the 2 points = " << point1.Dot(point2) << std::endl;
	std::cout << "Cross of the 2 points = " << std::endl << point1.Cross(point2) << std::endl;
	std::cout << "Normalized point 1 = " << std::endl << point1.Normalize() << std::endl;

	Camera camera { 
		{
			{50},
			{50},
			{50},
			{1}
		},
		{
			{0},
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
		RenderManager::GetInstance().CreateWindow(TITLE, false, SCREEN_WIDTH, SCREEN_HEIGHT);

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
				r
			);
		}
	}

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}