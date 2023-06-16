#include "AbstractMatrixFunctions.h"
#include <cmath>

void SwapRows(std::vector<std::vector<double>>& matrix, int row1, int row2)
{
	int rowLength = matrix.size();
	int columnLength = matrix.at(0).size();
	std::vector<double> temp = matrix.at(row1);
	matrix.at(row1) = matrix.at(row2);
	matrix.at(row2) = temp;
}

void ScaleRow(std::vector<std::vector<double>>& matrix, int row, double scalar)
{
	int length = matrix.at(row).size();
	for (int i = 0; i < length; i++)
	{
		matrix.at(row).at(i) *= scalar;
	}
}

void AddRowValue(std::vector<std::vector<double>>& matrix, int row, int rowToAdd, double rowToAddScalar)
{
	int length = matrix.at(row).size();
	for (int i = 0; i < length; i++)
	{
		matrix.at(row).at(i) += (matrix.at(rowToAdd).at(i) * rowToAddScalar);
	}
}

bool isRowZero(std::vector<std::vector<double>>& matrix, int row)
{
	int rowLength = matrix.at(row).size();

	for (int i = 0; i < rowLength; i++)
	{
		if (matrix.at(row).at(i) != 0)
			return false;
	}

	return true;
}

void MoveZeroRowsToBottom(std::vector<std::vector<double>>& matrix)
{
	int rowLength = matrix.size();
	int row = 0;
	int iteration = 0;
	while (row < rowLength - 1 && iteration < rowLength - 1)
	{
		if (isRowZero(matrix, row))
		{
			SwapRows(matrix, row, row + 1);
			SwapRows(matrix, row + 1, rowLength - 1);
		}
		else
		{
			row++;
		}

		iteration++;
	}
	for (int row = 0; row < rowLength - 1; row++)
	{
		if (isRowZero(matrix, row))
		{
			SwapRows(matrix, row, row + 1);
			SwapRows(matrix, row + 1, rowLength - 1);
		}
	}
}

void StairifySqure(std::vector<std::vector<double>>& matrix, int length)
{
	int OpeningElementIndex = 0;
	int InsertFoundRowIndex = -1;
	int iteration = 0;
	bool nonZeroNotFound = true;
	int prevRowFound = 0;
	int row = 0;
	while (iteration < length)
	{
		int row = InsertFoundRowIndex + 1;
		int chosenRow = 0;
		while (row < length && nonZeroNotFound)
		{
			if (matrix.at(row).at(OpeningElementIndex) != 0)
			{
				nonZeroNotFound = false;
				chosenRow = row;
				prevRowFound = row + 1;
				InsertFoundRowIndex++;
			}

			if (nonZeroNotFound)
				row++;
		}
		if (!nonZeroNotFound)
		{
			double reverseScalar = 1/(matrix.at(chosenRow).at(OpeningElementIndex));
			ScaleRow(matrix, chosenRow, reverseScalar);
			SwapRows(matrix, InsertFoundRowIndex, chosenRow);

			for (int i = InsertFoundRowIndex + 1; i < length; i++)
			{
				double zeroScalar = (-1) * matrix.at(i).at(OpeningElementIndex);
				AddRowValue(matrix, i, InsertFoundRowIndex, zeroScalar);
			}
		}

		OpeningElementIndex++;
		iteration++;
		nonZeroNotFound = true;
	}
}

void StairifyWideMatrix(std::vector<std::vector<double>>& matrix, int length)
{
	int colLength = matrix.at(0).size();
	int OpeningElementIndex = 0;
	int InsertFoundRowIndex = -1;
	int iteration = 0;
	bool nonZeroNotFound = true;
	int prevRowFound = 0;
	int row = 0;
	while (iteration < colLength)
	{
		int row = InsertFoundRowIndex + 1;
		int chosenRow = 0;
		while (row < length && nonZeroNotFound)
		{
			if (matrix.at(row).at(OpeningElementIndex) != 0)
			{
				nonZeroNotFound = false;
				chosenRow = row;
				prevRowFound = row + 1;
				InsertFoundRowIndex++;
			}

			if (nonZeroNotFound)
				row++;
		}
		if (!nonZeroNotFound)
		{
			double reverseScalar = 1 / (matrix.at(chosenRow).at(OpeningElementIndex));
			ScaleRow(matrix, chosenRow, reverseScalar);
			SwapRows(matrix, InsertFoundRowIndex, chosenRow);

			for (int i = InsertFoundRowIndex + 1; i < length; i++)
			{
				double zeroScalar = (-1) * matrix.at(i).at(OpeningElementIndex);
				AddRowValue(matrix, i, InsertFoundRowIndex, zeroScalar);
			}
		}

		OpeningElementIndex++;
		iteration++;
		nonZeroNotFound = true;
	}
}

void StairifyTallMatrix(std::vector<std::vector<double>>& matrix, int length)
{
	int rowLength = matrix.size();
	int OpeningElementIndex = 0;
	int InsertFoundRowIndex = -1;
	int iteration = 0;
	bool nonZeroNotFound = true;
	int prevRowFound = 0;
	int row = 0;
	while (iteration < length)
	{
		int row = InsertFoundRowIndex + 1;
		int chosenRow = 0;
		while (row < rowLength && nonZeroNotFound)
		{
			if (matrix.at(row).at(OpeningElementIndex) != 0)
			{
				nonZeroNotFound = false;
				chosenRow = row;
				prevRowFound = row + 1;
				InsertFoundRowIndex++;
			}

			if (nonZeroNotFound)
				row++;
		}
		if (!nonZeroNotFound)
		{
			double reverseScalar = 1 / (matrix.at(chosenRow).at(OpeningElementIndex));
			ScaleRow(matrix, chosenRow, reverseScalar);
			SwapRows(matrix, InsertFoundRowIndex, chosenRow);

			for (int i = InsertFoundRowIndex + 1; i < rowLength; i++)
			{
				double zeroScalar = (-1) * matrix.at(i).at(OpeningElementIndex);
				AddRowValue(matrix, i, InsertFoundRowIndex, zeroScalar);
			}
		}

		OpeningElementIndex++;
		iteration++;
		nonZeroNotFound = true;
	}
}

void Stairify(std::vector<std::vector<double>>& matrix)
{
	int rowLength = matrix.size();
	int colLength = matrix.at(0).size();
	if (rowLength == colLength)
		StairifySqure(matrix, rowLength);
	else
		if (rowLength < colLength)
			StairifyWideMatrix(matrix, rowLength);
		else
			StairifyTallMatrix(matrix, colLength);
}