#pragma once
#include <vector>

void SwapRows(std::vector<std::vector<double>>& matrix, int row1, int row2);
void ScaleRow(std::vector<std::vector<double>>& matrix, int row, double scalar);
void AddRowValue(std::vector<std::vector<double>>& matrix, int row, int rowToAdd, double rowToAddScalar);
void RowEchelon(std::vector<std::vector<double>>& matrix);
void ReducedRowEchelon(std::vector<std::vector<double>>& matrix);