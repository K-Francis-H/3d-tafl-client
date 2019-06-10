#include "raylib.h"
#include <stdio.h>

// gcc main.c -o out.a -lraylib -lX11


#define SWIDTH 800
#define SHEIGHT 450

#define DEBUG 1

Camera3D setupCamera();

int main(){

	InitWindow(SWIDTH, SHEIGHT, "testing");

	Camera3D cam = setupCamera();

	Model taflKing = LoadModel("res/model/textured_granite_king.obj");
	Texture2D graniteTexture = LoadTexture("res/texture/seamless-granite-2560x2560.png");
	SetMaterialTexture(&taflKing.materials[0], MAP_DIFFUSE, graniteTexture);
	//taflKing.materials[0].maps[MAP_DIFFUSE].texture = graniteTexture;
	
	Vector3 position = {0.0f, 0.0f, 0.0f};

	SetTargetFPS(60);

	while(!WindowShouldClose()){

		BeginDrawing();
			ClearBackground(RAYWHITE);

			BeginMode3D(cam);
				DrawModel(taflKing, position, 0.2f, WHITE);
				DrawGrid(9, 1.0f);
			EndMode3D();
			
			if(DEBUG){
				DrawFPS(10,10);
			}

		EndDrawing();

	}
	CloseWindow();

	return 0;
}

Camera3D setupCamera(){
	Camera3D camera = {0};
	camera.position = (Vector3){10.0f, 10.0f, 10.0f};
	camera.target = (Vector3){0.0f, 0.0f, 0.0f};
	camera.up = (Vector3){0.0f, 1.0f, 0.0f};
	camera.fovy = 60.0f;
	camera.type = CAMERA_PERSPECTIVE;

	return camera;
}
