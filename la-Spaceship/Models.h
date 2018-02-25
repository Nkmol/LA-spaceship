#pragma once
#include "Matrix.h"

namespace Model
{
	const Matrix<double, 4, 8> Cube{
		/*x*/{0, 1, 1, 0, 1, 1, 0, 0},
		/*y*/{0, 0, 1, 1, 0, 1, 1, 0},
		/*z*/{0, 0, 0, 0, 1, 1, 1, 1},

		/*w*/{1, 1, 1, 1, 1, 1, 1, 1}
	};
}
