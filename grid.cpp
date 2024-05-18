#include <raylib.h>
#include "grid.hpp"

void Grid::Draw() {
	
	Color LIVE = {139, 185, 255, 255};
	Color DEAD = {33, 74, 130, 95};

	int gridWidth = 0;

	for(int row = 0; row < rows; row++) {
		for(int column = 0; column < columns; column++) {
			Color color = cells[row * columns + column] ? LIVE : DEAD;
			DrawRectangle(column * cellSize, row * cellSize, cellSize - gridWidth, cellSize - gridWidth, color);
			//DrawCircle(column * cellSize + cellSize/2, row * cellSize + cellSize/2, cellSize/2, color); 
		}
	}
}

void Grid::SetValue(int row, int column, int value) {
	if(IsWithinBounds(row, column)) {
		cells[row*columns + column] = value;
	}
}

int Grid::GetValue(int row, int column) {
	if(IsWithinBounds(row, column)) {
		return cells[row * columns+column];
	}
	return 0;
}

bool Grid::IsWithinBounds(int row, int column) {
	if(row >= 0 && row < rows && column >= 0 && column < columns) {
		return true;
	}
	return false;
}

void Grid::FillRandom() {
	for(int row = 0; row < rows; row++) {
		for(int column = 0; column < columns; column++) {
			int randomValue = GetRandomValue(0, 4);
			cells[row * columns + column] = (randomValue == 4) ? 1 : 0;
		}
	}
}

void Grid::Clear() {
	for(int row = 0; row < rows; row++) {
		for(int column = 0; column < columns; column++) {
			cells[row * columns + column] = 0;
		}
	}
}

void Grid::ToggleCell(int row, int column) {
	if(IsWithinBounds(row, column)) {
		cells[row * columns + column] = !cells[row * columns + column];
	}
}
