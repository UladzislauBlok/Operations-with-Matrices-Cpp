#include <iostream>
#include "matrix.h"

int main()
{
	Matrix mat(2, 2);
	mat.setMatrix();
	printMultiplicationByMat(mat);

	return 0;
}