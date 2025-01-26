#include <stdint.h>
#include <stdio.h>
#include <raylib.h>

#define COLOR_BACKGROUND GetColor(0x151515FF)

#define PADDLE_HEIGHT 20
#define PADDLE_WIDTH 75

#define BRICKS_IN_ROW 15
#define TOTAL_ROWS 5

#define BRICK_HEIGHT 20
#define BRICK_WIDTH 50

typedef struct Brick {
	float x;
	float y;
	float width;
	float height;
} Brick;

void draw_bricks(int bricksInRow, int numRows) {
	Brick bricks[numRows][bricksInRow];
	
	int width = GetScreenWidth();
	int height = GetScreenHeight();

	for(int i = 0; i < numRows; ++i) {
		for(int j = 0; j < bricksInRow; ++j) {
			bricks[i][j] = (Brick){
				 .x = j * BRICK_WIDTH + (width - bricksInRow * BRICK_WIDTH) / 2, // Center bricks horizontally
				 .y = i * BRICK_HEIGHT + (height - numRows * BRICK_HEIGHT) / 8, // Center bricks vertically
				 .width = BRICK_WIDTH,
				 .height = BRICK_HEIGHT
			};

			Rectangle rect = *(Rectangle*)&bricks[i][j];

			DrawRectangleRec(rect, RED);
			DrawRectangleLinesEx(rect, 1, WHITE);
		}
	}
}


static void render(void) {
	int width = GetScreenWidth();
	int height = GetScreenHeight();

	Rectangle paddle = {
		.x = width/4 - 25,
		.y = height - 50,
		.width = PADDLE_WIDTH,
		.height = PADDLE_HEIGHT,
	};

	DrawRectangleRec(paddle, WHITE);

	draw_bricks(BRICKS_IN_ROW, TOTAL_ROWS);
}

void plug_update(void) {
	BeginDrawing();
	ClearBackground(COLOR_BACKGROUND);

	render();

	EndDrawing();
}
