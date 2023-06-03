#include "AbstractMatrixFunctions.h"

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

void RowEchelon(std::vector<std::vector<double>>& matrix)
{
	
	int iteration = 0;
	int rowLength = matrix.size();
	int columnLength = matrix.at(0).size();
	int maxIteration = rowLength >= columnLength ? columnLength : rowLength;
	int columnPicker = 0;
	bool rowNotFound = true;
	while (iteration < maxIteration)
	{
		int i = iteration;
		while (i < rowLength && rowNotFound)
		{
			if (columnPicker < columnLength && matrix.at(i).at(columnPicker) != 0)
			{
				rowNotFound = false;
			}
			i++;
		}

		if (!rowNotFound)
		{
			ScaleRow(matrix, i - 1, 1 / matrix.at(i - 1).at(columnPicker));
			SwapRows(matrix, iteration, i - 1);

			for (int j = iteration + 1; j < rowLength; j++)
			{
				if (matrix.at(j).at(i - 1) != 0)
					AddRowValue(matrix, j, i - 1, -(matrix.at(j).at(i - 1)));
			}
		}
		iteration++;
		columnPicker++;
		rowNotFound = true;
	}
}