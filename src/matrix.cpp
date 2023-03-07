#include <iostream>
#include <cmath>
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
	cout << multiplicationByNum(sourceMat) << endl;
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

int determ(const Matrix& sourceMat) // Function for calculating the determinant of a matrix 
{
	if (sourceMat.getCol() == 2) // Calculate the determinant for a 2x2 matrix
	{
		return sourceMat.getElement(0, 0) * sourceMat.getElement(1, 1) - sourceMat.getElement(0, 1) * sourceMat.getElement(1, 0);
	}
	else if (sourceMat.getCol() == 1) return sourceMat.getElement(0, 0); //  Calculate the determinant for a 1x1 matrix
	else // The large matrices I'll be laying out on the first row 
	{
		Matrix mat(sourceMat.getRow() - 1, sourceMat.getCol() - 1); //For a 3x3 or larger matrix, create a new smaller matrix 
		int result{ 0 };
		int matRow, matCol;

		for (int rowFirstLine{ 0 }; rowFirstLine < sourceMat.getRow(); rowFirstLine++) // Calculate the determinant by the first row
		{
			matRow = 0;
			for (int row{ 1 }; row < sourceMat.getRow(); row++) // Count the determinants of smaller matrices, starting from the second row
			{
				matCol = 0;
				for (int col{ 0 }; col < sourceMat.getCol(); col++) // Going through the elements in each row 
					if (col != rowFirstLine) // If the element number of the row does not match the number of the element of the first row (which I use to calculate the determinant)
					{
						mat.setElement(matRow, matCol, sourceMat.getElement(row, col)); // then I write this element in a new table
						matCol++;
					}
				matRow++;
			}
			result += pow(-1, rowFirstLine + 2) * sourceMat.getElement(0, rowFirstLine) * determ(mat); // Recursively count det
		}
		return result;
	}
}

void printDeterm(const Matrix& sourceMat)
{
	if (sourceMat.getCol() == sourceMat.getRow())
		cout << "Det = " << determ(sourceMat);
	else
		cout << "This operation is only possible with a square matrix\n";
}

Matrix minor(const Matrix& sourceMat) // Function for calculating a matrix of minors 
{
	Matrix minorMat(sourceMat.getRow(), sourceMat.getCol()); // Create a new matrix (minority matrix)

	for (int rowMinorMat{ 0 }; rowMinorMat < sourceMat.getRow(); rowMinorMat++)
	{
		for (int colMinorMat{ 0 }; colMinorMat < sourceMat.getCol(); colMinorMat++) // Go through it and set each element 
		{
			Matrix smalMat(sourceMat.getRow() - 1, sourceMat.getCol() - 1); // To calculate the determinant, create a smaller matrix 
			int rowSmalMat, colSmalMat;
			rowSmalMat = 0;
			for (int rowSourceMat{ 0 }; rowSourceMat < sourceMat.getRow(); rowSourceMat++) // Iterate over the source matrix 
			{
				colSmalMat = 0;
				for (int colSourceMat{ 0 }; colSourceMat < sourceMat.getCol(); colSourceMat++)
				{
					if (rowSourceMat != rowMinorMat && colSourceMat != colMinorMat) // If the row and column number of this element does not match the row and column number of the element we are counting, we write this element in a matrix(mat)
					{
						smalMat.setElement(rowSmalMat, colSmalMat, sourceMat.getElement(rowSourceMat, colSourceMat));
						colSmalMat++;
						if (colSmalMat == smalMat.getCol()) // If you have filled in a line, move to a new line 
							rowSmalMat++;
					}
				}
			}
			minorMat.setElement(rowMinorMat, colMinorMat, determ(smalMat)); // Write the determinant of the smaller matrix into the matrix of minors
		}
	}
	return minorMat;
}

void printMatrixMinor(const Matrix& sourceMat)
{
	cout << minor(sourceMat) << endl;
}

Matrix algebrComplement(const Matrix& sourceMat) // Function for finding an algebraic addition matrix
{
	Matrix mat(sourceMat.getRow(), sourceMat.getCol());
	for (int row{ 0 }; row < sourceMat.getRow(); row++)
	{
		for (int col{ 0 }; col < sourceMat.getCol(); col++)
			mat.setElement(row, col, sourceMat.getElement(row, col) * pow(-1, row + col));
	}

	return mat;
}

void printInversMat(const Matrix& sourceMat) // Function for calculating the inverse matrix
{
	if (sourceMat.getCol() == sourceMat.getRow())
	{
		int det = determ(sourceMat);

		Matrix minorMat(minor(sourceMat));
		Matrix algebrComplementMat(algebrComplement(minorMat));		// Find the transpose algebraic addition matrix

		Matrix mat(transpose(algebrComplementMat));

		if (det == 0)
			cout << "The determinant is zero. There is no inverse matrix";
		else
			cout << "1/" << det << " * M\n\n M =" << mat;
	}
	else
		cout << "This operation is only possible with a square matrix\n";
}

Matrix adding(const Matrix& sourceMat) // Function for adding matrices
{
	Matrix secondMat(sourceMat.getRow(), sourceMat.getCol());
	secondMat.setMatrix();

	for (int row{ 0 }; row < secondMat.getRow(); row++)
		for (int col{ 0 }; col < secondMat.getCol(); col++)
			secondMat.setElement(row, col, (sourceMat.getElement(row, col) + secondMat.getElement(row, col))); // Overwrite the matrix "mat" elements with the sums

	return secondMat;
}

void printAdding(const Matrix& sourceMat)
{
	cout << "This operation is only possible with matrices of the same size\n"
		    "Enter the elements of the second matrix \n";
	
	cout << adding(sourceMat) << endl;
}

Matrix subtracting(const Matrix& sourceMat) // Function for subtracting matrices
{
	cout << "This operation is only possible with matrices of the same size\n";

	Matrix secondMat(sourceMat.getRow(), sourceMat.getCol());

	for (int row{ 0 }; row < secondMat.getRow(); row++)
		for (int col{ 0 }; col < secondMat.getCol(); col++)
			secondMat.setElement(row, col, (sourceMat.getElement(row, col) - secondMat.getElement(row, col))); // Overwrite the matrix "mat" elements with the subtract

	return secondMat;
}

void printSubtracting(const Matrix& sourceMat)
{
	cout << "This operation is only possible with matrices of the same size\n"
			"Enter the elements of the second matrix \n";

	cout << subtracting(sourceMat) << endl;
}

Matrix multiplicationByMat(const Matrix& sourceMat, int rowSecondMat, int colSecondMat) // function for multiplying a matrix by a matrix 
{
	Matrix secondMat(rowSecondMat, colSecondMat);
	secondMat.setMatrix();

	Matrix result(sourceMat.getRow(), secondMat.getCol()); // Create a matrix with the number of rows from the first matrix and the number of columns from the second matrix

	for (int row{ 0 }; row < result.getRow(); row++)
		for (int col{ 0 }; col < result.getCol(); col++)
		{
			int temp{ 0 }; //the value of each element will be read into "temp" and then transferred to the matrix 
			for (int count{ 0 }; count < sourceMat.getCol(); count++) // it makes no difference whether to take the number of columns of the first matrix or the number of rows of the second, because they are equal
			{
				temp += sourceMat.getElement(row, count) * secondMat.getElement(count, col);
			}
			result.setElement(row, col, temp);
		}
	return result;
}

void printMultiplicationByMat(const Matrix& sourceMat)
{
	cout << "The operation is only possible if the number of columns of the first matrix equals the number of rows of the second matrix\n";
	int rowSecondMat, colSecondMat;
	cout << "Enter the dimensions of the second matrix(ROWxCOL) \n";
	cin >> rowSecondMat >> colSecondMat;
	if (sourceMat.getCol() != rowSecondMat)
	{
		cout << "The number of columns of the first matrix does not equal the number of rows of the second matrix.\n"
			"The operation is not possible\n";
		return ;
	}
	else
	{
		cout << "Enter the elements of the second matrix" << endl;
		cout << multiplicationByMat(sourceMat, rowSecondMat, colSecondMat);
	}
}

