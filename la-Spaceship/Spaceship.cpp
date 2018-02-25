#include "Spaceship.h"
#include "MatrixHelper.h"

Spaceship::Spaceship(double x, double y, double z)
	: local_origin_point({ { x },{ y },{ z },{ 1 } })
{
	Init();
}

void Spaceship::Draw(Camera& camera)
{
	// Create Projection
	const auto projected_engine = camera.ProjectMatrix(Object::ToMatrix<8>(engine.GetPoints()));
	const auto projected_body = camera.ProjectMatrix(Object::ToMatrix<8>(body.GetPoints()));
	const auto projected_head = camera.ProjectMatrix(Object::ToMatrix<5>(head.GetPoints()));
	const auto projected_left_wing = camera.ProjectMatrix(Object::ToMatrix<3>(left_wing.GetPoints()));
	const auto projected_right_wing = camera.ProjectMatrix(Object::ToMatrix<3>(right_wing.GetPoints()));

	// Draw objects
	//RenderManager::GetInstance().DrawPoints(Object::ToPoints(projected_engine), engine.GetLines());
	RenderManager::GetInstance().DrawPoints(Object::ToPoints(projected_body), body.GetLines());
	//RenderManager::GetInstance().DrawPoints(Object::ToPoints(projected_head), head.GetLines());
	//RenderManager::GetInstance().DrawPoints(Object::ToPoints(projected_right_wing), right_wing.GetLines());
	//RenderManager::GetInstance().DrawPoints(Object::ToPoints(projected_left_wing), left_wing.GetLines());

}

void Spaceship::Rotate(double rotate_percentage, Axis axis)
{

	const auto engine_matrix = Object::ToMatrix<8>(engine.GetPoints());
	const auto body_matrix = Object::ToMatrix<8>(body.GetPoints());
	const auto head_matrix = Object::ToMatrix<5>(head.GetPoints());
	const auto left_wing_matrix = Object::ToMatrix<3>(left_wing.GetPoints());
	const auto right_wing_matrix = Object::ToMatrix<3>(right_wing.GetPoints());

	const auto center = body.GetCenterPoint();

	double lowest_x = body_matrix.GetVal(0, 0);
	double lowest_y = body_matrix.GetVal(1, 0);
	double lowest_z = body_matrix.GetVal(2, 0);
	double highest_y = lowest_y;

	try
	{
		double current_x, current_y, current_z;

		for (int i = 0; i < body_matrix.GetRow(0).size(); i++)
		{
			current_x = body_matrix.GetVal(0, i);
			current_y = body_matrix.GetVal(1, i);
			current_z = body_matrix.GetVal(2, 1);

			if (current_x < lowest_x)
			{
				lowest_x = current_x;
			}

			if (current_y < lowest_y)
			{
				lowest_y = current_y;
			}

			if (current_z < lowest_z)
			{
				lowest_z = current_z;
			}

			if (current_y > highest_y)
			{
				highest_y = current_y;
			}
		}
	}
	catch (...)
	{

	}

	MatrixHelper helper;


	MatrixFactory factory;

	const auto translate = factory.CreateTranslationMatrix(-center.GetVal(0, 0), -center.GetVal(1, 0), -center.GetVal(2, 0));
	const auto revert = factory.CreateTranslationMatrix(center.GetVal(0, 0), center.GetVal(1, 0), center.GetVal(2, 0));

	const auto rotate_matrix = helper.Rotate(rotate_percentage, body_matrix,
	{
		center.GetVal(0, 0), center.GetVal(1, 0), center.GetVal(2, 0)
	},
	{
		0, 1, 0
	});

	const auto transformation = translate * rotate_matrix * revert;


	body.SetTransform(transformation * body_matrix);


	head.SetTransform(helper.Rotate(rotate_percentage, head_matrix,
	{
		center.GetVal(0, 0), center.GetVal(1, 0), center.GetVal(2, 0)
	},
	{
		center.GetVal(0, 0), center.GetVal(1, 0), center.GetVal(2, 0)
	}));


	engine.SetTransform(helper.Rotate(rotate_percentage, engine_matrix,
	{
		center.GetVal(0, 0), center.GetVal(1, 0), center.GetVal(2, 0)
	},
	{
		center.GetVal(0, 0), center.GetVal(1, 0), center.GetVal(2, 0)
	}));


	left_wing.SetTransform(helper.Rotate(rotate_percentage, left_wing_matrix,
	{
		center.GetVal(0, 0), center.GetVal(1, 0), center.GetVal(2, 0)
	},
	{
		center.GetVal(0, 0), center.GetVal(1, 0), center.GetVal(2, 0)
	}));

	right_wing.SetTransform(helper.Rotate(rotate_percentage, right_wing_matrix,
	{
		center.GetVal(0, 0), center.GetVal(1, 0), center.GetVal(2, 0)
	},
	{
		center.GetVal(0, 0), center.GetVal(1, 0), center.GetVal(2, 0)
	}));
}

void Spaceship::Init()
{
	ConstructEngine();
	ConstructBody();
	ConstructHead();
	ConstructLeftWing();
	ConstructRightWing();
}

void Spaceship::ConstructEngine()
{

	Matrix<double, 4, 8> points(
	{
		{ 0  , 0  , 0  , 0  , 40 , 40 , 40 , 40 },
		{ 0  , 0  , 100, 100, 10 , 10 , 90 , 90 },
		{ 30 , 110, 110, 30 , 30 , 110, 110, 30 },
		{ 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1 }
	}
	);

	engine.SetTransform(points);
	engine.SetLines(
	{
		{ 0, 1 },
		{ 1, 2 },
		{ 2, 3 },
		{ 3, 0 },
		{ 0, 4 },
		{ 4, 5 },
		{ 5, 1 },
		{ 5, 6 },
		{ 6, 2 },
		{ 6, 7 },
		{ 7, 3 },
		{ 7, 4 }
	}
	);
}

void Spaceship::ConstructBody()
{

	Matrix<double, 4, 8> points(
	{
		{ 40 , 40 , 140, 40 , 140, 40 , 140, 140 },
		{ 10 , 10 , 10 , 90 , 90 , 90 , 90 , 10 },
		{ 30 , 110, 110, 110, 110, 30 , 30 , 30 },
		{ 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1 }
	}
	);

	body.SetTransform(points);
	body.SetLines(
	{
		{ 0, 1 },
		{ 1, 2 },
		{ 1, 3 },
		{ 3, 4 },
		{ 3, 5 },
		{ 5, 6 },
		{ 5, 0 },
		{ 0, 7 },
		{ 7, 2 },
		{ 2, 4 },
		{ 4, 6 },
		{ 6, 7 },
	}
	);
}

void Spaceship::ConstructHead()
{
	Matrix<double, 4, 5> points(
	{
		{ 200, 140, 140, 140, 140 },
		{ 50 , 10 , 90 , 90 , 10 },
		{ 70 , 30 , 110, 30 , 110 },
		{ 1  , 1  , 1  , 1  , 1 }
	}
	);

	head.SetTransform(points);
	head.SetLines(
	{
		{ 0, 1 },
		{ 0, 2 },
		{ 0, 3 },
		{ 0, 4 }
	}
	);
}

void Spaceship::ConstructLeftWing()
{
	Matrix<double, 4, 3> points(
	{
		{ 40 , 40 , 140 },
		{ 10 , 10 , 10 },
		{ 40 , 0  , 40 },
		{ 1  , 1  , 1 }
	}
	);

	left_wing.SetTransform(points);

	left_wing.SetLines(
	{
		{ 0, 1 },
		{ 1, 2 },
	}
	);
}

void Spaceship::ConstructRightWing()
{

	Matrix<double, 4, 3> points(
	{
		{ 40 , 40 , 140 },
		{ 10 , 10 , 10 },
		{ 100, 140, 100 },
		{ 1  , 1  , 1 }
	}
	);

	right_wing.SetTransform(points);

	right_wing.SetLines(
	{
		{ 0, 1 },
		{ 1, 2 }
	}
	);

}


