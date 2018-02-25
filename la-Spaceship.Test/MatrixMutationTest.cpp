#include "stdafx.h"
#include "CppUnitTest.h"
#include "MatrixFactory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace laSpaceshipTest
{
	TEST_CLASS(MatrixMutationTest)
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

		TEST_METHOD(scale_matrix_by_two_should_mult_all_values)
		{
			// Arrange
			MatrixFactory factory;
			const auto test_matrix = CreateTestMatrix();
			const auto scale_matrix = factory.CreateScaleMatrix(2, 2, 2);

			// Act
			const auto result = scale_matrix * test_matrix;

			// Assert
			Assert().AreEqual(result.GetVal(0, 0), 200.0);
			Assert().AreEqual(result.GetVal(0, 1), 400.0);
			Assert().AreEqual(result.GetVal(0, 2), 600.0);
			Assert().AreEqual(result.GetVal(0, 3), 800.0);
							  					   	  
			Assert().AreEqual(result.GetVal(1, 0), 1000.0);
			Assert().AreEqual(result.GetVal(1, 1), 1200.0);
			Assert().AreEqual(result.GetVal(1, 2), 1400.0);
			Assert().AreEqual(result.GetVal(1, 3), 1600.0);
							  					   	  
			Assert().AreEqual(result.GetVal(2, 0), 1800.0);
			Assert().AreEqual(result.GetVal(2, 1), 2000.0);
			Assert().AreEqual(result.GetVal(2, 2), 2200.0);
			Assert().AreEqual(result.GetVal(2, 3), 2400.0);

			Assert().AreEqual(result.GetVal(3, 0), 1.0);
			Assert().AreEqual(result.GetVal(3, 1), 1.0);
			Assert().AreEqual(result.GetVal(3, 2), 1.0);
			Assert().AreEqual(result.GetVal(3, 3), 1.0);
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

		TEST_METHOD(translate_matrix_all_two_should_plus_two_to_all)
		{
			// Arrange
			MatrixFactory factory;
			const double inputA = 2, inputB = 2, inputC = 2;
			const auto translateMatrix = factory.CreateTranslationMatrix(2, 2, 2);
			const auto testMatrix = CreateTestMatrix();

			// Act
			const auto result = translateMatrix * testMatrix;

			// Assert
			Assert().AreEqual(result.GetVal(0, 0), 102.0);
			Assert().AreEqual(result.GetVal(0, 1), 202.0);
			Assert().AreEqual(result.GetVal(0, 2), 302.0);
			Assert().AreEqual(result.GetVal(0, 3), 402.0);
							  					   	 
			Assert().AreEqual(result.GetVal(1, 0), 502.0);
			Assert().AreEqual(result.GetVal(1, 1), 602.0);
			Assert().AreEqual(result.GetVal(1, 2), 702.0);
			Assert().AreEqual(result.GetVal(1, 3), 802.0);
							  					   	 
			Assert().AreEqual(result.GetVal(2, 0), 902.0);
			Assert().AreEqual(result.GetVal(2, 1), 1002.0);
			Assert().AreEqual(result.GetVal(2, 2), 1102.0);
			Assert().AreEqual(result.GetVal(2, 3), 1202.0);

			Assert().AreEqual(result.GetVal(3, 0), 1.0);
			Assert().AreEqual(result.GetVal(3, 1), 1.0);
			Assert().AreEqual(result.GetVal(3, 2), 1.0);
			Assert().AreEqual(result.GetVal(3, 3), 1.0);
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

		TEST_METHOD(rotation_create_90_X_negative)
		{
			// Arrange
			MatrixFactory factory;
			const double inputA = 90;
			const Axis inputB = X;
			const auto inputC = false;

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
			Assert().AreEqual(scaleMatrix.GetVal(1, 2), sin(inputA));
			Assert().AreEqual(scaleMatrix.GetVal(1, 3), 0.0);

			Assert().AreEqual(scaleMatrix.GetVal(2, 0), 0.0);
			Assert().AreEqual(scaleMatrix.GetVal(2, 1), -sin(inputA));
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