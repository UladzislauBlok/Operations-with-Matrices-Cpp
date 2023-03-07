#include <iostream>
#include "matrix.h"

int main()
{
	Matrix mat(3, 3);
	mat.setMatrix();
	printMinusMat(mat);
	printMultiplicationByNum(mat);
	printTranspose(mat);

	return 0;
}