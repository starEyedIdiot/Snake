#include "raylib.h"
#include <utility>
#include <deque>
#include <vector>

const int screenWidth = 640;
const int screenHeight = 640;

const int cellSize = 32;

const int gridColumns = screenWidth / cellSize;
const int gridRows = screenHeight / cellSize;

std::deque<Vector2> snake;
Vector2 food;

bool grow = false;
bool alive = true;

Vector2 spawnFood() {
	while (true) {
		Vector2 f = {
			(float)GetRandomValue(0, gridColumns - 1),
			(float)GetRandomValue(0, gridRows - 1)
		};

		bool collides = false;

		for (const auto& segment : snake) {
			if (segment.x == f.x && segment.y == f.y) {
				collides = true;
				break;
			}
		}

		if (!collides) return f;
	}
}

int main()
{
	Vector2 direction = Vector2{ 1, 0 };
	food = { 0,0 };

	snake.push_back({ 5, 5 });
	snake.push_back({ 4, 5 });
	snake.push_back({ 3, 5 });

	InitWindow(screenWidth, screenHeight, "Snake!!!");

	SetTargetFPS(15);
	// HideCursor();


	// Main game loop
	while (!WindowShouldClose())
	{
		if (alive) {
			if (IsKeyDown(KEY_RIGHT)) direction = { 1,0 };
			if (IsKeyDown(KEY_LEFT)) direction = { -1,0 };
			if (IsKeyDown(KEY_UP)) direction = { 0,-1 };
			if (IsKeyDown(KEY_DOWN)) direction = { 0,1 };


			Vector2 newHead = snake.front();
			newHead.x += direction.x;
			newHead.y += direction.y;

			// wrap around
			newHead.x = ((int)newHead.x + gridColumns) % gridColumns;
			newHead.y = ((int)newHead.y + gridRows) % gridRows;

			for (Vector2 part : snake)
				if (part.x == newHead.x && part.y == newHead.y) alive = false;
				

			if (newHead.x == food.x && newHead.y == food.y)
			{
				grow = true;
				food = spawnFood();
			}
			

			// add new head
			snake.push_front(newHead);

			// remove tail
			if (!grow) snake.pop_back();
			grow = false;
		}

		BeginDrawing();

		ClearBackground(BLACK);

		for (int x = 0; x <= screenWidth; x += cellSize) {
			DrawLine(x, 0, x, screenHeight, LIGHTGRAY);
		}
		for (int y = 0; y <= screenHeight; y += cellSize) {
			DrawLine(0, y, screenWidth, y, LIGHTGRAY);
		}

		if(!alive) DrawText("You lost!", screenWidth / 2, screenHeight / 2, 24, WHITE);

		for (Vector2 vec : snake)
			DrawRectangle(vec.x * cellSize, vec.y * cellSize, cellSize, cellSize, DARKGREEN);

		DrawRectangle(food.x * cellSize, food.y * cellSize, cellSize, cellSize, MAROON);

		EndDrawing();

	}

	CloseWindow();

	return 0;
}

