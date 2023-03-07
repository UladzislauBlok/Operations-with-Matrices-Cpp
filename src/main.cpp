#include <iostream>
#include "matrix.h"

int main()
{
	std::cout << "\t\t\tHello" << std::endl;
	while (1)
	{
		std::cout << "\tEnter the size of the matrix and its elements(ROWxCOL): " << std::endl;
		int row, col;
		std::cin >> row >> col;
		Matrix mat(row, col);
		mat.setMatrix();

		while (1)
		{
			std::cout << "\tWhat operation do you want to perform?\n"
				"\tSingle matrix operations:\n"
				"1) Taking the minus out of the matrix\n"
				"2) Multiplying a matrix by a number\n"
				"3) Transpose the matrix \n"
				"4) Calculate the determinant of the matrix\n"
				"5) Finding the inverse matrix\n"
				"\tOperations with two matrices:\n"
				"6) Adding matrices\n"
				"7) Subtracting matrices\n"
				"8) Matrix multiplication\n"
				"Enter the operation number: ";

			char operationSymbol;

			while (1)
			{
				std::cin >> operationSymbol;
				if (operationSymbol == '1' || operationSymbol == '2' || operationSymbol == '3'
					|| operationSymbol == '4' || operationSymbol == '5' || operationSymbol == '6'
					|| operationSymbol == '7' || operationSymbol == '8')
					break;
				else
					std::cout << "Incorrect symbol. Repeat the entry: \n";
			}

			switch (operationSymbol)
			{
			case '1':
			{
				printMinusMat(mat);
				break;
			}
			case '2':
			{
				printMultiplicationByNum(mat);
				break;
			}
			case '3':
			{
				printTranspose(mat);
				break;
			}
			case '4':
			{
				printDeterm(mat);
				break;
			}
			case '5':
			{
				printInversMat(mat);
				break;
			}
			case '6':
			{
				printAdding(mat);
				break;
			}
			case '7':
			{
				printSubtracting(mat);
				break;
			}
			case '8':
			{
				printMultiplicationByMat(mat);
				break;
			}
			}
			std::cout << "\nIs there anything else you want to do with these numbers? \n"
				"(a) to another operation, or (c) to change the numbers, or (q) to quit \n";
			char choice;
			do
			{
				std::cin >> choice;
			} while (choice != 'a' && choice != 'c' && choice != 'q');

			if (choice == 'c') break;
			if (choice == 'q') return 0;
		}
	}
}