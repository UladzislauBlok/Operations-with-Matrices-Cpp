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

std::ostream& operator<<(std::ostream& out, const Matrix& sourceMat)
{
	{
		for (int row{ 0 }; row < sourceMat.rowsNum; row++)
		{
			out << "\t|";
			for (int col{ 0 }; col < sourceMat.columnsNum; col++)
				out << '\t' << sourceMat.matrix[row][col];
			out << "\t|\n";
		}
		return out;
	}
}

Matrix minusMat(const Matrix& sourceMat) // function to take the minus out of the matrix
{
	Matrix mat(sourceMat.getRow(), sourceMat.getCol());
	for (int row{ 0 }; row < sourceMat.getRow(); row++)
		for (int col{ 0 }; col < sourceMat.getCol(); col++)
			mat.setElement(row, col, -sourceMat.getElement(row, col));
	return mat;
}

void printMinusMat(const Matrix& sourceMat)
{
	cout << minusMat(sourceMat) << endl;;
}

Matrix multiplicationByNum(const Matrix& sourceMat) // function for multiplying a matrix by a number
{
	Matrix mat(sourceMat.getRow(), sourceMat.getCol());

	cout << "Enter the number by which you want to multiply the matrix: ";
	int num;

	while (1)
	{
		std::cin >> num;
		if (std::cin.fail()) // Check that the value is correct
		{
			std::cin.clear(); // return the cin to 'normal' mode of operation
			std::cin.ignore(32767, '\n'); // remove the previous input values from the input buffer
			std::cout << "Oops, that input is invalid.  Please try again.\n";
		}
		else break;
	}

	for (int row{ 0 }; row < sourceMat.getRow(); row++)
		for (int col{ 0 }; col < sourceMat.getCol(); col++)
			mat.setElement(row, col, sourceMat.getElement(row, col) * num);
	return mat;
}

void printMultiplicationByNum(const Matrix& sourceMat)
{
	cout << multiplicationByNum(sourceMat) << endl;;
}

Matrix transpose(const Matrix& sourceMat)
{
	Matrix mat(sourceMat.getCol(), sourceMat.getRow()); // Swap row and col to create a transpose matrix

	for (int row{ 0 }; row < sourceMat.getRow(); row++)
		for (int col{ 0 }; col < sourceMat.getCol(); col++)
			mat.setElement(col, row, sourceMat.getElement(row, col)); // Assign elements from rows to columns 
	return mat;
}

void printTranspose(const Matrix& sourceMat)
{
	cout << transpose(sourceMat) << endl;;
}
