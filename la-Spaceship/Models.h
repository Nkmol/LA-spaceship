#pragma once
#include "Matrix.h"

namespace Models
{
	namespace Cube {
		const Matrix<double, 4, 8> matrix{
			/*x*/{ -0.5,  0.5,  0.5, -0.5,  0.5, 0.5, -0.5, -0.5 },
			/*y*/{ -0.5, -0.5,  0.5,  0.5, -0.5, 0.5,  0.5, -0.5 },
			/*z*/{ -0.5, -0.5, -0.5, -0.5,  0.5, 0.5,  0.5,  0.5 },
			/*w*/{    1,    1,    1,    1,    1,   1,    1,    1 }
		};

		const std::vector<std::pair<unsigned int, unsigned int>> lines {
			{0, 1},
			{1, 2},
			{2, 3},
			{3, 0},
			{1, 4},
			{4, 5},
			{5, 2},
			{5, 6},
			{6, 7},
			{6, 3},
			{7, 4},
			{7, 0}
		};
	};
}
