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

void ReducedRowEchelon(std::vector<std::vector<double>>& matrix)
{
	int rowLength = matrix.size(); 
	int columnLength = matrix.at(0).size(); 
	
	int k = rowLength - 1;
	int i = columnLength - 1; 
	while (i > 0 && k > 0)
	{
		for (int j = rowLength - 2; j >= 0; j--) 
		{
			AddRowValue(matrix, j, k, -matrix.at(j).at(i));
		}
		i--;
		k--;
	}

	
	for (int i = 0; i < (rowLength < columnLength ? rowLength : columnLength); i++)
	{
		matrix.at(i).at(i) = abs(matrix.at(i).at(i));
	}
	
}

int GetRank(std::vector<std::vector<double>>& matrix)
{
	RowEchelon(matrix);
	ReducedRowEchelon(matrix);
	bool found = false;
	int rank = 0;
	

	for (int i = 0; i < matrix.size(); i++)
	{
		int j = 0;

		while (j < matrix.at(0).size() && !found)
		{
			if (matrix.at(i).at(j) != 0)
			{
				found = true;
				rank++;
			}
			j++;
		}
		found = false;
	}

	return rank;
}