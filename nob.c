#define NOB_IMPLEMENTATION
#include "nob.h"

int build_raylib_libs() {
	nob_mkdir_if_not_exists("raylib");

	char libs[8][10] = {
		"rcore",
		"raudio",
		"rglfw",
		"rmodels",
		"rshapes",
		"rtext",
		"rtextures",
		"utils"
	};

	char sourceFile[256];
	char outputFile[256];

	for (int i = 0; i < sizeof(libs) / sizeof(libs[0]); ++i) {
		snprintf(sourceFile, sizeof(sourceFile), "./include/raylib/src/%s.c", libs[i]);
		snprintf(outputFile, sizeof(outputFile), "raylib/%s.o", libs[i]);

		Nob_Cmd cmd = {0};

		if(strcmp(libs[i], "rglfw") != 0) {
			nob_cmd_append(
				&cmd, 
				"clang", 
				"-g", 
				"-DPLATFORM_DESKTOP", 
				"-fPIC", 
				"-DSUPPORT_FILEFORMAT_FLAC=1", 
				"-I./include/raylib/src/external/glfw/include",
				"-DGRAPHICS_API_OPENGL_33",
				"-c",
				sourceFile,
				"-o",
				outputFile
			);
		} else {
			nob_cmd_append(
				&cmd, 
				"clang", 
				"-g", 
				"-DPLATFORM_DESKTOP", 
				"-fPIC", 
				"-DSUPPORT_FILEFORMAT_FLAC=1", 
				"-I./include/raylib/src/external/glfw/include",
				"-DGRAPHICS_API_OPENGL_33",
				"-x",
				"objective-c",
				"-c",
				sourceFile,
				"-o",
				outputFile
			);
		}

		if (!nob_cmd_run_sync(cmd)) return 1;
	}

	return 0;
}

int build_dylib() {
	Nob_Cmd cmd = {0};
	nob_cmd_append(
		&cmd, 
		"cc", 
		"-shared", 
		"-fPIC", 
		"-framework", 
		"CoreVideo", 
		"-framework", 
		"IOKit", 
		"-framework", 
		"Cocoa", 
		"-framework", 
		"GLUT", 
		"-framework", 
		"OpenGL",
		"-install_name",
		"@rpath/libraylib.dylib",
		"-o",
		"raylib/libraylib.dylib",
		"raylib/rcore.o",
		"raylib/raudio.o",
		"raylib/rglfw.o",
		"raylib/rmodels.o",
		"raylib/rshapes.o",
		"raylib/rtext.o",
		"raylib/rtextures.o",
		"raylib/utils.o"
	);

	if (!nob_cmd_run_sync(cmd)) return 1;
	return 0;
}

int build_executable() {
	Nob_Cmd cmd = {0};
	nob_cmd_append(
		&cmd, 
		"clang", 
		"-Wall", 
		"-Wextra", 
		"-g",
		"-I.",
		"-I./include/raylib/src/",
		"-o",
		"brickbreaker",
		"./src/brickbreaker.c",
		"raylib/libraylib.dylib",
		"-framework", 
		"IOKit", 
		"-framework", 
		"Cocoa", 
		"-framework", 
		"GLUT", 
		"-framework", 
		"OpenGL",
		"-lm",
		"-ldl",
		"-lpthread",
		"-rpath",
		".",
		"-rpath",
		"raylib"
	);

	if (!nob_cmd_run_sync(cmd)) return 1;
	return 0;
}

int build_raylib() {
	if(build_raylib_libs() != 0) {
		return 1;
	}

	return build_dylib();
}

int main(int argc, char **argv)
{
	NOB_GO_REBUILD_URSELF(argc, argv);
	if(build_raylib() != 0) {
		return 1;
	}

	return build_executable();
}


