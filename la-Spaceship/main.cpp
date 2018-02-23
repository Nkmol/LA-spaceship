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

//Screen dimension constants
const int SCREEN_WIDTH = 480; // TODO vierkant scherm voor projectie
const int SCREEN_HEIGHT = 480;
const std::string TITLE = "Liniair Algebra - Spaceship";

#undef main
int main(int argc, char *argv[]) {
	// init through a initalizer_list
	const Matrix<double, 4, 4> rectangle(
		{
			{100,  150, 150,  100},
			{150, 150, 150, 150},
			{100,  100,  150, 150},
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
	const Matrix<double, 4, 1> point1(
		{
			{5},
			{5},
			{5},
			{1}
		}
	);
	const Matrix<double, 4, 1> point2(
		{
			{7},
			{7},
			{7},
			{1}
		}
	);

	std::cout << point1 << std::endl;
	std::cout << point2 << std::endl;

	std::cout << "Dot of the 2 points = " << helper.Dot(point1, point2) << std::endl;
	std::cout << "Cross of the 2 points = " << std::endl << helper.Cross(point1, point2) << std::endl;
	std::cout << "Normalized point 1 = " << std::endl << helper.Normalize(point1) << std::endl;

	Camera camera { 
		{
			{0},
			{0},
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


	// Projectionmatrix
	Vector3d<double> test_camera_position{ 0, 125, 0 };
	double near = 1; // Afstand van het camera-object tot het begin van je camerabeeld.
	double far = 249; // Het limiet van je camerabeeld.
	double field_of_view = factory.AngleToRadian(90); // De hoek van het camerabeeld (meestal standaard 90 graden)
	double scale = near * tan(field_of_view * 0.5); // TODO check op afronding naar 0??
	double help_calculation_a = -far / (far - near);
	double help_calculation_b = (-far * near) / (far - near);
	
	// Create the projection matrix
	Matrix<double, 4, 4> projection_matrix
	{
		{ scale, 0, 0, 0 },
		{ 0, scale, 0, 0 },
		{ 0, 0, help_calculation_a, -1 },
		{ 0, 0, help_calculation_b, 0 }
	};

	std::cout << projection_matrix << std::endl;

	Matrix<double, 4, 1> project_matrix{ {480}, {480}, {0}, {1} };
	const auto testing = project_matrix.Transpose() * projection_matrix;
	const double test = testing.Getval(0, 0);

	// Berekening
	const auto target_object = test_object.ToMatrix<4>();
	const auto projected_matrix = projection_matrix * camera.ToMatrix() * rectangle;

	std::cout << target_object << std::endl << projected_matrix << std::endl;
	std::cout << test << std::endl;

	// Naberekening (aangezien hulprij w niet meer 1 is)

	Matrix<double, 4, 4> adjusted_projected_matrix;

	for (int i = 0; i < 4; i++)
	{
		const double screen_size = 420;
		const double x = projected_matrix.Getval(0, i);
		const double w = projected_matrix.Getval(3, i);
		const double new_x = (screen_size / 2) + (((x + 1) / w) * screen_size * 0.5);

		const double y = projected_matrix.Getval(1, i);
		const double new_y = (screen_size / 2) + (((y + 1) / w) * screen_size * 0.5);

		adjusted_projected_matrix.Setval(0, i, new_x);
		adjusted_projected_matrix.Setval(1, i, new_y);
		adjusted_projected_matrix.Setval(2, i, -projected_matrix.Getval(2, i));
	}

	std::cout << adjusted_projected_matrix << std::endl;
	

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
				adjusted_projected_matrix
			);
		}
	}

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}