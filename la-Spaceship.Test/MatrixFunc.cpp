#include "stdafx.h"
#include "CppUnitTest.h"
#include "../la-Spaceship/Object.h"
#include "../la-Spaceship/Models.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace laSpaceshipTest
{
	TEST_CLASS(MatrixFuncTests)
	{
	public:
		TEST_METHOD(transpose)
		{
			// Arrange
			const auto matrix = CreateTestMatrix();

			// Act
			const auto transposed = matrix.Transpose();

			// Assert
			Assert().AreEqual(static_cast<int>(transposed.GetCol(0).size()), 4);
			Assert().AreEqual(static_cast<int>(transposed.GetRow(0).size()), 4);

			Assert().AreEqual(transposed.GetVal(0, 0), 100.0);
			Assert().AreEqual(transposed.GetVal(0, 1), 500.0);
			Assert().AreEqual(transposed.GetVal(0, 2), 900.0);
			Assert().AreEqual(transposed.GetVal(0, 3), 1.0);
							  
			Assert().AreEqual(transposed.GetVal(1, 0), 200.0);
			Assert().AreEqual(transposed.GetVal(1, 1), 600.0);
			Assert().AreEqual(transposed.GetVal(1, 2), 1000.0);
			Assert().AreEqual(transposed.GetVal(1, 3), 1.0);
							  
			Assert().AreEqual(transposed.GetVal(2, 0), 300.0);
			Assert().AreEqual(transposed.GetVal(2, 1), 700.0);
			Assert().AreEqual(transposed.GetVal(2, 2), 1100.0);
			Assert().AreEqual(transposed.GetVal(2, 3), 1.0);
							  
			Assert().AreEqual(transposed.GetVal(3, 0), 400.0);
			Assert().AreEqual(transposed.GetVal(3, 1), 800.0);
			Assert().AreEqual(transposed.GetVal(3, 2), 1200.0);
			Assert().AreEqual(transposed.GetVal(3, 3), 1.0);
		}

		TEST_METHOD(get_center_point_of_cube_5x5)
		{
			// Arrange
			const Matrix<double, 4, 8> cube{
				/*x*/{0, 5, 5, 0, 5, 5, 0, 0},
				/*y*/{0, 0, 5, 5, 0, 5, 5, 0},
				/*z*/{0, 0, 0, 0, 5, 5, 5, 5},

				/*w*/{5, 5, 5, 5, 5, 5, 5, 5}
			};
			Object object ({0, 0, 0}, {1, 1, 1}, cube);

			// Act
			const auto center = object.GetCenterPoint();

			// Assert
			Assert().AreEqual(static_cast<int>(center.GetCol(0).size()), 4);
			Assert().AreEqual(static_cast<int>(center.GetRow(0).size()), 1);

			Assert().AreEqual(center.GetVal(0, 0), 2.5);
			Assert().AreEqual(center.GetVal(1, 0), 2.5);
			Assert().AreEqual(center.GetVal(2, 0), 2.5);
			Assert().AreEqual(center.GetVal(3, 0), 1.0);
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