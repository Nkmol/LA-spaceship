#include "stdafx.h"
#include "CppUnitTest.h"
#include "../la-Spaceship/MatrixFactory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace laSpaceshipTest
{
	TEST_CLASS(MatrixCreationTests)
	{
	public:
		TEST_METHOD(scale_create)
		{
			// Arrange
			MatrixFactory factory;
			const double inputA = 2, inputB = 2, inputC = 2;
			const auto scaleMatrix = factory.CreateScaleMatrix(2, 2, 2);

			// Act

			// Assert
			Assert().AreEqual(static_cast<int>(scaleMatrix.GetCol(0).size()), 4);
			Assert().AreEqual(static_cast<int>(scaleMatrix.GetRow(0).size()), 4);

			Assert().AreEqual(scaleMatrix.GetVal(0, 0), inputA);
			Assert().AreEqual(scaleMatrix.GetVal(0, 1), 0.0);
			Assert().AreEqual(scaleMatrix.GetVal(0, 2), 0.0);
			Assert().AreEqual(scaleMatrix.GetVal(0, 3), 0.0);

			Assert().AreEqual(scaleMatrix.GetVal(1, 0), 0.0);
			Assert().AreEqual(scaleMatrix.GetVal(1, 1), inputB);
			Assert().AreEqual(scaleMatrix.GetVal(1, 2), 0.0);
			Assert().AreEqual(scaleMatrix.GetVal(1, 3), 0.0);

			Assert().AreEqual(scaleMatrix.GetVal(2, 0), 0.0);
			Assert().AreEqual(scaleMatrix.GetVal(2, 1), 0.0);
			Assert().AreEqual(scaleMatrix.GetVal(2, 2), inputC);
			Assert().AreEqual(scaleMatrix.GetVal(2, 3), 0.0);

			Assert().AreEqual(scaleMatrix.GetVal(3, 0), 0.0);
			Assert().AreEqual(scaleMatrix.GetVal(3, 1), 0.0);
			Assert().AreEqual(scaleMatrix.GetVal(3, 2), 0.0);
			Assert().AreEqual(scaleMatrix.GetVal(3, 3), 1.0);
		}

		TEST_METHOD(translate_create)
		{
			// Arrange
			MatrixFactory factory;
			const double inputA = 2, inputB = 2, inputC = 2;

			// Act
			const auto translateMatrix = factory.CreateTranslationMatrix(2, 2, 2);

			// Assert
			Assert().AreEqual(static_cast<int>(translateMatrix.GetCol(0).size()), 4);
			Assert().AreEqual(static_cast<int>(translateMatrix.GetRow(0).size()), 4);

			Assert().AreEqual(translateMatrix.GetVal(0, 0), 1.0);
			Assert().AreEqual(translateMatrix.GetVal(0, 1), 0.0);
			Assert().AreEqual(translateMatrix.GetVal(0, 2), 0.0);
			Assert().AreEqual(translateMatrix.GetVal(0, 3), inputA);

			Assert().AreEqual(translateMatrix.GetVal(1, 0), 0.0);
			Assert().AreEqual(translateMatrix.GetVal(1, 1), 1.0);
			Assert().AreEqual(translateMatrix.GetVal(1, 2), 0.0);
			Assert().AreEqual(translateMatrix.GetVal(1, 3), inputB);

			Assert().AreEqual(translateMatrix.GetVal(2, 0), 0.0);
			Assert().AreEqual(translateMatrix.GetVal(2, 1), 0.0);
			Assert().AreEqual(translateMatrix.GetVal(2, 2), 1.0);
			Assert().AreEqual(translateMatrix.GetVal(2, 3), inputC);

			Assert().AreEqual(translateMatrix.GetVal(3, 0), 0.0);
			Assert().AreEqual(translateMatrix.GetVal(3, 1), 0.0);
			Assert().AreEqual(translateMatrix.GetVal(3, 2), 0.0);
			Assert().AreEqual(translateMatrix.GetVal(3, 3), 1.0);
		}

		TEST_METHOD(rotation_create_90_X_positive)
		{
			// Arrange
			MatrixFactory factory;
			const double inputA = 90;
			const auto inputB = X;
			const auto inputC = true;

			// Act
			const auto scaleMatrix = factory.CreateRotationMatrix(inputA, inputB, inputC);

			// Assert
			Assert().AreEqual(static_cast<int>(scaleMatrix.GetCol(0).size()), 4);
			Assert().AreEqual(static_cast<int>(scaleMatrix.GetRow(0).size()), 4);

			Assert().AreEqual(scaleMatrix.GetVal(0, 0), 1.0);
			Assert().AreEqual(scaleMatrix.GetVal(0, 1), 0.0);
			Assert().AreEqual(scaleMatrix.GetVal(0, 2), 0.0);
			Assert().AreEqual(scaleMatrix.GetVal(0, 3), 0.0);

			Assert().AreEqual(scaleMatrix.GetVal(1, 0), 0.0);
			Assert().AreEqual(scaleMatrix.GetVal(1, 1), cos(inputA));
			Assert().AreEqual(scaleMatrix.GetVal(1, 2), -sin(inputA));
			Assert().AreEqual(scaleMatrix.GetVal(1, 3), 0.0);

			Assert().AreEqual(scaleMatrix.GetVal(2, 0), 0.0);
			Assert().AreEqual(scaleMatrix.GetVal(2, 1), sin(inputA));
			Assert().AreEqual(scaleMatrix.GetVal(2, 2), cos(inputA));
			Assert().AreEqual(scaleMatrix.GetVal(2, 3), 0.0);

			Assert().AreEqual(scaleMatrix.GetVal(3, 0), 0.0);
			Assert().AreEqual(scaleMatrix.GetVal(3, 1), 0.0);
			Assert().AreEqual(scaleMatrix.GetVal(3, 2), 0.0);
			Assert().AreEqual(scaleMatrix.GetVal(3, 3), 1.0);
		}


		TEST_METHOD(rotation_create_90_Y_positive)
		{
			// Arrange
			MatrixFactory factory;
			const double inputA = 90;
			const Axis inputB = Y;
			const auto inputC = true;

			// Act
			const auto scaleMatrix = factory.CreateRotationMatrix(inputA, inputB, inputC);

			// Assert
			Assert().AreEqual(static_cast<int>(scaleMatrix.GetCol(0).size()), 4);
			Assert().AreEqual(static_cast<int>(scaleMatrix.GetRow(0).size()), 4);

			Assert().AreEqual(scaleMatrix.GetVal(0, 0), cos(inputA));
			Assert().AreEqual(scaleMatrix.GetVal(0, 1), 0.0);
			Assert().AreEqual(scaleMatrix.GetVal(0, 2), -sin(inputA));
			Assert().AreEqual(scaleMatrix.GetVal(0, 3), 0.0);

			Assert().AreEqual(scaleMatrix.GetVal(1, 0), 0.0);
			Assert().AreEqual(scaleMatrix.GetVal(1, 1), 1.0);
			Assert().AreEqual(scaleMatrix.GetVal(1, 2), 0.0);
			Assert().AreEqual(scaleMatrix.GetVal(1, 3), 0.0);

			Assert().AreEqual(scaleMatrix.GetVal(2, 0), sin(inputA));
			Assert().AreEqual(scaleMatrix.GetVal(2, 1), 0.0);
			Assert().AreEqual(scaleMatrix.GetVal(2, 2), cos(inputA));
			Assert().AreEqual(scaleMatrix.GetVal(2, 3), 0.0);

			Assert().AreEqual(scaleMatrix.GetVal(3, 0), 0.0);
			Assert().AreEqual(scaleMatrix.GetVal(3, 1), 0.0);
			Assert().AreEqual(scaleMatrix.GetVal(3, 2), 0.0);
			Assert().AreEqual(scaleMatrix.GetVal(3, 3), 1.0);
		}

		TEST_METHOD(rotation_create_90_Z_positive)
		{
			// Arrange
			MatrixFactory factory;
			const double inputA = 90;
			const Axis inputB = Z;
			const auto inputC = true;

			// Act
			const auto scaleMatrix = factory.CreateRotationMatrix(inputA, inputB, inputC);

			// Assert
			Assert().AreEqual(static_cast<int>(scaleMatrix.GetCol(0).size()), 4);
			Assert().AreEqual(static_cast<int>(scaleMatrix.GetRow(0).size()), 4);

			Assert().AreEqual(scaleMatrix.GetVal(0, 0), cos(inputA));
			Assert().AreEqual(scaleMatrix.GetVal(0, 1), -sin(inputA));
			Assert().AreEqual(scaleMatrix.GetVal(0, 2), 0.0);
			Assert().AreEqual(scaleMatrix.GetVal(0, 3), 0.0);

			Assert().AreEqual(scaleMatrix.GetVal(1, 0), sin(inputA));
			Assert().AreEqual(scaleMatrix.GetVal(1, 1), cos(inputA));
			Assert().AreEqual(scaleMatrix.GetVal(1, 2), 0.0);
			Assert().AreEqual(scaleMatrix.GetVal(1, 3), 0.0);

			Assert().AreEqual(scaleMatrix.GetVal(2, 0), 0.0);
			Assert().AreEqual(scaleMatrix.GetVal(2, 1), 0.0);
			Assert().AreEqual(scaleMatrix.GetVal(2, 2), 1.0);
			Assert().AreEqual(scaleMatrix.GetVal(2, 3), 0.0);

			Assert().AreEqual(scaleMatrix.GetVal(3, 0), 0.0);
			Assert().AreEqual(scaleMatrix.GetVal(3, 1), 0.0);
			Assert().AreEqual(scaleMatrix.GetVal(3, 2), 0.0);
			Assert().AreEqual(scaleMatrix.GetVal(3, 3), 1.0);
		}
	private:
		static Matrix<double, 4, 4> CreateTestMatrix()
		{
			return 
			{
				{ 100, 200 , 300 , 400  },
				{ 500, 600 , 700 , 800  },
				{ 900, 1000, 1100, 1200 },
				{   1,    1,    1,    1 }
			};
		}
	};
}