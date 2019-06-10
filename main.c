#include "raylib.h"
#include "colors.h"	//custom colors for Tafl board annotation
#include <stdio.h>

// gcc main.c -o out.a -lraylib -lX11


#define SWIDTH 800
#define SHEIGHT 450

#define TRUE 1
#define FALSE 0

#define DEBUG 1

Camera3D setupCamera();
void drawGrid();
int isCorner(int x, int y);
int isKingsHall(int x, int y);
int isSpecialCell(int x, int y);

#define TABLUT_SIZE 9
//Color TABLUT_GRID[TABLUT_SIZE][TABLUT_SIZE] = {
//{YELLOW, 
//};

int main(){

	InitWindow(SWIDTH, SHEIGHT, "testing");

	Camera3D cam = setupCamera();

	//load king
	Model taflKing = LoadModel("res/model/textured_granite_king.obj");
	Texture2D graniteTexture = LoadTexture("res/texture/seamless-granite-2560x2560.png");
	SetMaterialTexture(&taflKing.materials[0], MAP_DIFFUSE, graniteTexture);
	//taflKing.materials[0].maps[MAP_DIFFUSE].texture = graniteTexture;

	//load defender pawn
	Model defenderPawn = LoadModel("res/model/granite_pawn.obj");
	SetMaterialTexture(&defenderPawn.materials[0], MAP_DIFFUSE, graniteTexture);

	//load attackerPawn
	Model attackerPawn = LoadModel("res/model/obsidian_pawn.obj");
	Texture2D obsidianTexture = LoadTexture("res/texture/obsidian_750x750.png");
	SetMaterialTexture(&attackerPawn.materials[0], MAP_DIFFUSE, obsidianTexture);
	
	Vector3 position = {0.0f, 0.0f, 0.0f};

	SetTargetFPS(60);

	while(!WindowShouldClose()){

		BeginDrawing();
			ClearBackground(RAYWHITE);

			BeginMode3D(cam);

				//TODO draw grid
				//DrawRectangle(0,0,200,200,YELLOW);
				//DrawCubeV((Vector3){0.0f, 0.0f, 0.0f}, (Vector3){10.0f, 1.0f, 10.0f}, YELLOW);
				drawGrid();

				//DrawModel(taflKing, position, 0.2f, WHITE);
				DrawModel(taflKing, position, 0.2f, LAST_MOVE_DARK);//WHITE);
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

void drawGrid(){
	//TODO take in an actual grid object or something
	int i,j;
	int lastStyle = 1;//DARK
	Vector3 cellSize = (Vector3){10.0f, 1.0f, 10.0f};
	for(i=0; i < TABLUT_SIZE; i++){
		for(j=0; j < TABLUT_SIZE; j++){
			//TODO add logic for annotations
			Vector3 pos = (Vector3){10.0f*i, 0.0f, 10.0f*j};
			if(isSpecialCell(i, j)){
				DrawCubeV(pos, cellSize, YELLOW);
			}else{
				Color col = lastStyle == 1 ? DARK : LIGHT;
				DrawCubeV(pos, cellSize, col);
			}
			lastStyle = lastStyle == 1 ? 0 : 1;
		}
	}
}

int isCorner(int x, int y){
	return x == 0 && y == 0 ||
	x == 0 && y == TABLUT_SIZE-1 ||
	x == TABLUT_SIZE-1 && y == 0 ||
	x == TABLUT_SIZE && y == TABLUT_SIZE;
}

int isKingsHall(int x, int y){
	return x == TABLUT_SIZE/2 && y == TABLUT_SIZE/2; 
}

int isSpecialCell(int x, int y){
	return isKingsHall(x, y) || isCorner(x, y);
}

Camera3D setupCamera(){
	Camera3D camera = {0};
	camera.position = (Vector3){110.0f, 40.0f, 110.0f};
	camera.target = (Vector3){0.0f, 0.0f, 0.0f};
	camera.up = (Vector3){0.0f, 1.0f, 0.0f};
	camera.fovy = 60.0f;
	camera.type = CAMERA_PERSPECTIVE;

	return camera;
}
