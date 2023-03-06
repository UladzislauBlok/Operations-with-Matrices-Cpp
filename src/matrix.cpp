#include <iostream>
#include "matrix.h"

using namespace std;

Matrix::Matrix(int rowsNum, int columnsNum)
{
	this->rowsNum = rowsNum;
	this->columnsNum = columnsNum;

	matrix = new int* [rowsNum];

	for (int row{ 0 }; row < rowsNum; row++)
		matrix[row] = new int[columnsNum] {0};
}

Matrix::Matrix(const Matrix& source)
{
	rowsNum = source.rowsNum;
	columnsNum = source.columnsNum;

	if (source.matrix)
	{
		matrix = new int* [rowsNum];
		for (int row{ 0 }; row < rowsNum; row++)
			matrix[row] = new int[columnsNum];

		for (int row{ 0 }; row < rowsNum; row++)
			for (int col{ 0 }; col < columnsNum; col++)
				matrix[row][col] = source.matrix[row][col];
	}
}

Matrix::~Matrix()
{
	for (int row{ 0 }; row < rowsNum; row++)
		delete[] matrix[row];

	delete[] matrix;
}

void Matrix::setMatrix()
{
	for (int row{ 0 }; row < rowsNum; row++)
		for (int col{ 0 }; col < columnsNum; col++)
		{
			cout << "Enter a number a[" << row + 1 << "][" << col + 1 << "]\n";
			while (1)
			{
				cin >> matrix[row][col];
				if (std::cin.fail()) // Check that the value is correct
				{
					std::cin.clear(); // return the cin to 'normal' mode of operation
					std::cin.ignore(32767, '\n'); // remove the previous input values from the input buffer
					std::cout << "Oops, that input is invalid.  Please try again.\n";
				}
				else break;
			}
		}
}


