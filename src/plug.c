#include <stdio.h>
#include <raylib.h>

#define COLOR_BACKGROUND GetColor(0x151515FF)

#define PADDLE_HEIGHT 20
#define PADDLE_WIDTH 75

#define BRICK_HEIGHT 20
#define BRICK_WIDTH 50

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
}

void plug_update(void) {
	BeginDrawing();
	ClearBackground(COLOR_BACKGROUND);

	render();

	EndDrawing();
}
