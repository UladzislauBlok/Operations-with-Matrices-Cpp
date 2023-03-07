#include <iostream>
#include "matrix.h"

int main()
{
	Matrix mat(3, 3);
	mat.setMatrix();
	printInversMat(mat);

	return 0;
}