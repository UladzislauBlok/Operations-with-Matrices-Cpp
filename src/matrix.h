#ifndef MATRIX_H
#define MATRIX_H

#include <memory>

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
		m_matrix[row][col] = value;
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
		return m_matrix[row][col];
	}
};
#endif MATRIX_H