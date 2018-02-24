#include "stdafx.h"
#include "CppUnitTest.h"
#include "MatrixFactory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace laSpaceshipTest
{
	TEST_CLASS(MatrixMutationTest)
	{
	public:


		TEST_METHOD(scale_matrix_should_multiply_by_two)
		{
			// Arrange
			MatrixFactory factory;
			const auto test_matrix = CreateTestMatrix();
			const auto scale_matrix = factory.CreateScaleMatrix(2, 2, 2);

			// Act
			const auto result = scale_matrix * test_matrix;

			// Assert
			Assert().AreEqual(result.GetVal(0, 1), test_matrix.GetVal(0, 1) * 2);
			Assert().AreEqual(result.GetVal(1, 0), test_matrix.GetVal(1, 0) * 2);
			Assert().AreEqual(result.GetVal(2, 2), test_matrix.GetVal(2, 2) * 2);
		}

	private:
		Matrix<double, 4, 4> CreateTestMatrix()
		{
			return 
			{
				{ 100, 150, 150, 150 },
				{ 100, 100, 200, 200 },
				{ 100, 200, 200, 200 },
				{ 1	 , 1  , 1  , 1 }
			};
		}
	};
}