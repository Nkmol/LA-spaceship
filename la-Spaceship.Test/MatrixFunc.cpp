#include "stdafx.h"
#include "CppUnitTest.h"
#include "../la-Spaceship/Object.h"
#include "../la-Spaceship/Models.h"
#include "../la-Spaceship/MatrixHelper.h"

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

				/*w*/{1, 1, 1, 1, 1, 1, 1, 1}
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

		TEST_METHOD(dot_2x2)
		{
			// Arrange
			MatrixHelper helper;
			const Matrix<double, 4, 1> vec1{
				/*x*/{2},
				/*y*/{2},
				/*z*/{2},

				/*w*/{1}
			};
			
			const Matrix<double, 4, 1> vec2{
				/*x*/{2},
				/*y*/{2},
				/*z*/{2},

				/*w*/{1}
			};

			// Act
			const auto result = helper.Dot(vec1, vec2);

			auto a = vec1.Transpose() * vec2;
			//const auto result2 = (vec1.Transpose() * vec2).GetVal(0, 0) - 1; // Minus W

			// Assert
			Assert().AreEqual(result, 12.0);
			//Assert().AreEqual(result2, 12.0);
		}

		TEST_METHOD(cross_a_b_should_give_2x1_differnce)
		{
			// Arrange
			MatrixHelper helper;
			const Matrix<double, 4, 1> vec1{
				/*x*/{-1},
				/*y*/{2},
				/*z*/{1},

				/*w*/{1}
			};
			
			const Matrix<double, 4, 1> vec2{
				/*x*/{-1},
				/*y*/{4},
				/*z*/{0},

				/*w*/{1}
			};

			// Act
			const auto result = helper.Cross(vec1, vec2);

			// Assert
			Assert().AreEqual(static_cast<int>(result.GetCol(0).size()), 4);
			Assert().AreEqual(static_cast<int>(result.GetRow(0).size()), 1);

			Assert().AreEqual(result.GetVal(0, 0), -4.0);
			Assert().AreEqual(result.GetVal(1, 0), -1.0);
			Assert().AreEqual(result.GetVal(2, 0), -2.0);
			Assert().AreEqual(result.GetVal(3, 0), 1.0);
		}

		// dependent
		TEST_METHOD(cross_a_b_should_give_zero_vector)
		{
			// Arrange
			MatrixHelper helper;
			const Matrix<double, 4, 1> vec1{
				/*x*/{3},
				/*y*/{1},
				/*z*/{1},

				/*w*/{1}
			};
			
			const Matrix<double, 4, 1> vec2{
				/*x*/{6},
				/*y*/{2},
				/*z*/{2},

				/*w*/{1}
			};

			// Act
			const auto result = helper.Cross(vec1, vec2);

			// Assert
			Assert().AreEqual(static_cast<int>(result.GetCol(0).size()), 4);
			Assert().AreEqual(static_cast<int>(result.GetRow(0).size()), 1);

			Assert().AreEqual(result.GetVal(0, 0), 0.0);
			Assert().AreEqual(result.GetVal(1, 0), 0.0);
			Assert().AreEqual(result.GetVal(2, 0), 0.0);
			Assert().AreEqual(result.GetVal(3, 0), 1.0);
		}

		TEST_METHOD(length_a_to_3)
		{
			// Arrange
			MatrixHelper helper;
			const Matrix<double, 4, 1> vec1{
				/*x*/{3},
				/*y*/{3},
				/*z*/{3},

				/*w*/{1}
			};
			
			// Act
			const auto result = helper.Length(vec1);

			// Assert
			Assert().AreEqual(result, sqrt(27));
		}

		TEST_METHOD(normalize_a)
		{
			// Arrange
			MatrixHelper helper;
			const Matrix<double, 4, 1> vec1{
				/*x*/{3},
				/*y*/{3},
				/*z*/{3},

				/*w*/{1}
			};
			
			// Act
			const auto result = helper.Normalize(vec1);

			// Assert
			Assert().AreEqual(static_cast<int>(result.GetCol(0).size()), 4);
			Assert().AreEqual(static_cast<int>(result.GetRow(0).size()), 1);

			Assert().AreEqual(result.GetVal(0, 0), 3/(sqrt(27)));
			Assert().AreEqual(result.GetVal(1, 0), 3/(sqrt(27)));
			Assert().AreEqual(result.GetVal(2, 0), 3/(sqrt(27)));
			Assert().AreEqual(result.GetVal(3, 0), 0.0);
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