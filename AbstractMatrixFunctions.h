#pragma once
#include <vector>

void SwapRows(std::vector<std::vector<double>>& matrix, int row1, int row2);
void ScaleRow(std::vector<std::vector<double>>& matrix, int row, double scalar);
void AddRowValue(std::vector<std::vector<double>>& matrix, int row, int rowToAdd, double rowToAddScalar);
bool isRowZero(std::vector<std::vector<double>>& matrix, int row);
void Stairify(std::vector<std::vector<double>>& matrix);
void StairifySqureOrWidthMatrix(std::vector<std::vector<double>>& matrix, int length);
void StairifyTallMatrix(std::vector<std::vector<double>>& matrix, int length);
void MoveZeroRowsToBottom(std::vector<std::vector<double>>& matrix);
void ReduceToEchelon(std::vector<std::vector<double>>& matrix);