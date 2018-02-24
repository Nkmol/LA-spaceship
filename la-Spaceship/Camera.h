#pragma once
#include "Config.h"
#include "Matrix.h"
#include "MatrixFactory.h"

class Camera
{
private:
	Matrix<double, 4, 1> _eye, _lookat, _up;

	template <unsigned int cols>
	Matrix<double, 4, cols> FixCalculation(Matrix<double, 4, cols> projectedMatrix);
public:
	Camera(const Matrix<double, 4, 1>& eye, const Matrix<double, 4, 1>& lookat, const Matrix<double, 4, 1>& up);

#pragma region getters/setters
	void SetLookAt(const Matrix<double, 4, 1>& lookAt);
	const Matrix<double, 4, 1>& GetLookAt() const;
	void SetEye(const Matrix<double, 4, 1>& eye);
	const Matrix<double, 4, 1>& GetEye() const;
#pragma endregion

	Matrix<double, 4, 4> CalculateMatrix() const;

	template <unsigned int cols>
	Matrix<double, 4, cols> ProjectMatrix(Matrix<double, 4, cols> obj);
};

template <unsigned int cols>
Matrix<double, 4, cols> Camera::FixCalculation(Matrix<double, 4, cols> projectedMatrix)
{
	// Naberekening (aangezien hulprij w niet meer 1 is)
	Matrix<double, 4, cols> adjustedProjectedMatrix{};

	for (unsigned int i = 0; i < cols; i++)
	{
		const double screenSize = 420;
		const double x = projectedMatrix.GetVal(0, i);
		const double w = projectedMatrix.GetVal(3, i);
		const double newX = screenSize / 2 + (x + 1) / w * screenSize * 0.5;

		const double y = projectedMatrix.GetVal(1, i);
		const double newY = screenSize / 2 + (y + 1) / w * screenSize * 0.5;

		adjustedProjectedMatrix.SetVal(0, i, newX);
		adjustedProjectedMatrix.SetVal(1, i, newY);
		adjustedProjectedMatrix.SetVal(2, i, -projectedMatrix.GetVal(2, i));
	}

	return adjustedProjectedMatrix;
}

template <unsigned int cols>
Matrix<double, 4, cols> Camera::ProjectMatrix(Matrix<double, 4, cols> obj)
{
	MatrixFactory factory;

	// Projectionmatrix
	const auto near = 1; // Afstand van het camera-object tot het begin van je camerabeeld.
	const auto far = 249; // Het limiet van je camerabeeld.
	const auto fieldOfView = factory.AngleToRadian(90); // De hoek van het camerabeeld (meestal standaard 90 graden)
	const double scale = near * tan(fieldOfView * 0.5); // TODO(Sander Mol): check op afronding naar 0??
	const double helpCalculationA = -far / (far - near);
	const double helpCalculationB = -far * near / (far - near);

	// Create the projection matrix
	const Matrix<double, 4, 4> projectionMatrix
	{
		{scale, 0, 0, 0},
		{0, scale, 0, 0},
		{0, 0, helpCalculationA, -1},
		{0, 0, helpCalculationB, 0}
	};

	Matrix<double, 4, 1> project_matrix{
		{static_cast<double>(Config::SCREEN_WIDTH)},
		{static_cast<double>(Config::SCREEN_HEIGHT)},
		{0},
		{1}
	};

	return FixCalculation(projectionMatrix * CalculateMatrix() * obj);
}
