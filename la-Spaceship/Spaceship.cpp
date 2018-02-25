#include "Spaceship.h"
#include "MatrixHelper.h"
#include "Models.h"

Spaceship::Spaceship(double x, double y, double z)
	: local_origin_point({ { x },{ y },{ z },{ 1 } })
{
	Init();
}

void Spaceship::Shoot()
{
	MatrixFactory factory;
	MatrixHelper helper;
	MatrixHelper::Vector3D target{ head.GetCenterPoint() };

	const auto direction = helper.Normalize(target);
	Vector3d<double> bullet_direction{ direction.GetVal(0, 0), direction.GetVal(1, 0), direction.GetVal(2, 0) };
	
	const auto translate = factory.CreateTranslationMatrix(
		local_origin_point.GetVal(0, 0),
		local_origin_point.GetVal(1, 0),
		local_origin_point.GetVal(2, 0)
	);
	
	const auto spawn = (translate * Object::ToMatrix<5>(head.GetPoints())).GetCol(0);

	Bullet bullet{ spawn[0], spawn[1], spawn[2], bullet_direction, GetVelocity() };
	const auto scale_matrix = factory.CreateScaleMatrix(10, 10, 10);
	bullet.SetTransform(scale_matrix * Models::Cube::matrix);

	bullet.SetLines(Models::Cube::lines);

	bullets.push_back(bullet);
}

void Spaceship::Draw(Camera& camera)
{	
	MatrixFactory factory;

	for (Bullet& bullet : bullets)
	{
		bullet.Draw(camera);
	}

	// Transform
	const auto translate = factory.CreateTranslationMatrix(
		local_origin_point.GetVal(0, 0),
		local_origin_point.GetVal(1, 0),
		local_origin_point.GetVal(2, 0)
	);

	const auto engine_transform = translate * Object::ToMatrix<8>(engine.GetPoints());
	const auto body_transform = translate * Object::ToMatrix<8>(body.GetPoints());
	const auto head_transform = translate * Object::ToMatrix<5>(head.GetPoints());
	const auto left_wing_transform = translate * Object::ToMatrix<3>(left_wing.GetPoints());
	const auto right_wing_transform = translate * Object::ToMatrix<3>(right_wing.GetPoints());

	// Create Projection
	const auto projected_engine = camera.ProjectMatrix(engine_transform);
	const auto projected_body = camera.ProjectMatrix(body_transform);
	const auto projected_head = camera.ProjectMatrix(head_transform);
	const auto projected_left_wing = camera.ProjectMatrix(left_wing_transform);
	const auto projected_right_wing = camera.ProjectMatrix(right_wing_transform);

	// Draw objects
	RenderManager& render_manager = RenderManager::GetInstance();
	render_manager.DrawPoints(Object::ToPoints(projected_engine), engine.GetLines());
	render_manager.DrawPoints(Object::ToPoints(projected_body), body.GetLines());
	render_manager.DrawPoints(Object::ToPoints(projected_head), head.GetLines());
	render_manager.DrawPoints(Object::ToPoints(projected_right_wing), right_wing.GetLines());
	render_manager.DrawPoints(Object::ToPoints(projected_left_wing), left_wing.GetLines());

	if (show_help_lines)
	{
		const auto help_lines_transform = translate * Object::ToMatrix<4>(help_lines.GetPoints());
		const auto projected_help_lines = camera.ProjectMatrix(help_lines_transform);
		render_manager.DrawPoints(Object::ToPoints(projected_help_lines), help_lines.GetLines());
	}
}

void Spaceship::Rotate(double rotate_percentage, Axis axis)
{
	MatrixHelper helper;
	MatrixFactory factory;

	const auto engine_matrix = Object::ToMatrix<8>(engine.GetPoints());
	const auto body_matrix = Object::ToMatrix<8>(body.GetPoints());
	const auto head_matrix = Object::ToMatrix<5>(head.GetPoints());
	const auto left_wing_matrix = Object::ToMatrix<3>(left_wing.GetPoints());
	const auto right_wing_matrix = Object::ToMatrix<3>(right_wing.GetPoints());
	const auto help_lines_matrix = Object::ToMatrix<4>(help_lines.GetPoints());

	const auto center = body.GetCenterPoint();

	const auto translate = factory.CreateTranslationMatrix(-center.GetVal(0, 0), -center.GetVal(1, 0), -center.GetVal(2, 0));
	const auto revert = factory.CreateTranslationMatrix(center.GetVal(0, 0), center.GetVal(1, 0), center.GetVal(2, 0));

	const auto rotate_matrix = helper.Rotate(rotate_percentage, body_matrix,
	{
		center.GetVal(0, 0), center.GetVal(1, 0), center.GetVal(2, 0)
	},
	{
		static_cast<double>(axis == Y), 
		static_cast<double>(axis == X),
		static_cast<double>(axis == Z)
	});

	const auto transformation = translate * rotate_matrix * revert;

	body.SetTransform(transformation * body_matrix);
	head.SetTransform(transformation * head_matrix);
	engine.SetTransform(transformation * engine_matrix);
	left_wing.SetTransform(transformation * left_wing_matrix);
	right_wing.SetTransform(transformation * right_wing_matrix);
	help_lines.SetTransform(transformation * help_lines_matrix);
}

void Spaceship::Accelerate(double amount)
{
	SetVelocity(GetVelocity() + amount);
}

void Spaceship::Update()
{
	for (Bullet& bullet : bullets)
	{
		bullet.Update();
	}

	MatrixHelper helper;
	MatrixHelper::Vector3D target{ head.GetCenterPoint() };

	const auto direction = helper.Normalize(target);

	SetDirection({ direction.GetVal(0, 0), direction.GetVal(1, 0), direction.GetVal(2, 0) });
	local_origin_point = GetMovementTransform() * local_origin_point;
}

void Spaceship::ToggleHelpLines()
{
	show_help_lines = !show_help_lines;
}


void Spaceship::Init()
{
	ConstructEngine();
	ConstructBody();
	ConstructHead();
	ConstructLeftWing();
	ConstructRightWing();
	ConstructHelpLines();
}

void Spaceship::ConstructEngine()
{

	Matrix<double, 4, 8> points(
	{
		{ -90  , -90  , -90  , -90  , -50 , -50 , -50 , -50 },
		{ -50  , -50  , 50, 50, -40 , -40 , 40 , 40 },
		{ -40 , 40, 40, -40 , -40 , 40, 40, -40 },
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
		{ -50 , -50 , 50, -50 , 50, -50 , 50, 50 },
		{ -40 , -40 , -40 , 40 , 40 , 40 , 40 , -40 },
		{ -40 , 40, 40, 40, 40, -40 , -40 , -40 },
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
		{ 110, 50, 50, 50, 50 },
		{ 0 , -40 , 40 , 40 , -40 },
		{ 0 , -40 , 40, -40 , 40 },
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
		{ -50 , -50 , 50 },
		{ -40 , -40 , -40 },
		{ -30 , -70  ,-30 },
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
		{ -50 , -50 , 50 },
		{ -40 , -40 , -40 },
		{ 30, 70, 30 },
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

void Spaceship::ConstructHelpLines()
{
	Matrix<double,4,4> points(
	{
		{0, 500, 0, 0},
		{0, 0, 500, 0},
		{0, 0, 0, 500},
		{1, 1, 1, 1}
	});

	help_lines.SetTransform(points);

	help_lines.SetLines(
	{
		{0, 1},
		{0, 2},
		{0, 3}
	});
}


