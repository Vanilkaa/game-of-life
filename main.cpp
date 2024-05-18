#include <raylib.h>
#include <ctime>
#include <unistd.h>
#include "simulation.hpp"

int main() {
	Color GRID = {9, 43, 90, 255};

	const int WINDOW_WIDTH = 1000;
	const int WINDOW_HEIGHT = 1000;
	const int CELL_SIZE = 10;
	int FPS = 60;
	double UPS = 7.5;

	//SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Game of Life");
	SetTargetFPS(FPS);
	ClearBackground(GRID);
	Simulation simulation{WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE};

	struct timespec start, current;

	clock_gettime(CLOCK_MONOTONIC, &start);

	while(WindowShouldClose() == false) {
		// events
		
		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			Vector2 mousePosition = GetMousePosition();
			int row = mousePosition.y / CELL_SIZE;
			int column = mousePosition.x / CELL_SIZE;
			simulation.ToggleCell(row, column);
		}

		if(IsKeyPressed(KEY_SPACE)) {
			simulation.Run();
		}
		
		if(IsKeyPressed(KEY_C)) {
			ClearBackground(GRID);
			simulation.ClearGrid();
		}
		
		if(IsKeyPressed(KEY_R)) {
			if(!simulation.IsRunning()) {
				ClearBackground(GRID);
				simulation.CreateRandomState();
			}
		}

		if(IsKeyPressed(KEY_PERIOD)) {
			UPS *= 2;
		}

		if(IsKeyPressed(KEY_COMMA)) {
			UPS /= 2;
		}
		
		if(IsKeyPressed(KEY_N)) {
			if(!simulation.IsRunning()) {
				simulation.Run();
				simulation.Update();
				simulation.Run();
			}
		}
		// updating state
		
		long interval_ns = 1000000000/UPS;
		clock_gettime(CLOCK_MONOTONIC, &current);
		long elapsed_ns = (current.tv_sec - start.tv_sec) * 1000000000 + (current.tv_nsec - start.tv_nsec);
		if (elapsed_ns >= interval_ns) {
			if(UPS > FPS) {
				for(int i = 0; i < UPS/FPS; i++) {
					simulation.Update();
				}
			}
			else {
				simulation.Update();
			}
			start = current;
		}
		
		// drawing
		BeginDrawing();
		//ClearBackground(GRID);
		simulation.Draw();
		//DrawFPS(0, 0);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
