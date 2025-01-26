#include <stdio.h>
#include <raylib.h>

#include "plug.c"
 
int main(void) {
	InitWindow(800, 800, "BrickBreaker");

	SetTargetFPS(60);

	// Main Game Loop
	while(!WindowShouldClose()) {
		plug_update();
	}

	CloseWindow();

	return 0;
}
