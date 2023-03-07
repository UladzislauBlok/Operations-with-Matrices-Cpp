#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
private:
	int rowsNum;
	int columnsNum;
	int** matrix;

public:
	Matrix(int rowsNum = 1, int columnsNum = 1);

	Matrix(const Matrix& source);

	~Matrix();

	void setElement(int row, int col, int value)
	{
		matrix[row][col] = value;
	}

	void setMatrix();

	int getRow() const
	{
		return rowsNum;
	}

	int getCol() const
	{
		return columnsNum;
	}

	int getElement(int row, int col) const
	{
		return matrix[row][col];
	}

	friend std::ostream& operator<<(std::ostream& out, const Matrix& sourceMat);
};

Matrix minusMat(const Matrix& sourceMat); // function to take the minus out of the matrix

void printMinusMat(const Matrix& sourceMat); 

Matrix multiplicationByNum(const Matrix& sourceMat); // function for multiplying a matrix by a number

void printMultiplicationByNum(const Matrix& sourceMat);

Matrix transpose(const Matrix& sourceMat); // function for transposing a matrix 

void printTranspose(const Matrix& sourceMat);

int determ(const Matrix& sourceMat); // Function for calculating the determinant of a matrix 

void printDeterm(const Matrix& sourceMat);

Matrix minor(const Matrix& sourceMat); // Function for calculating the matrix of minors

void printMatrixMinor(const Matrix& sourceMat);

Matrix algebrComplement(const Matrix& sourceMat); // Function for finding an algebraic addition matrix

void printInversMat(const Matrix& sourceMat); // Function for calculating the inverse matrix
#endif MATRIX_H