#include "raylib.h"

#include "colors.h"		//custom colors for Tafl board annotation
#include "tafl_variants.h"	//starting grid layouts

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// gcc main.c -o out.a -lraylib -lX11


#define SWIDTH 800
#define SHEIGHT 450

#define TRUE 1
#define FALSE 0

#define DEBUG 

typedef struct{
	int size;
	//not ideal from efficiency standpoint, but keeps boards always static
	//which is really nice, dont really want to debug int** issues
	int state[ALEA_EVANGELII_SIZE][ALEA_EVANGELII_SIZE];
} TaflBoard;

TaflBoard board;

typedef struct{
	int x,y;
} Cell;


Camera3D setupCamera();
void drawGrid(TaflBoard* board);
int isCorner(int variantSize, int x, int y);
int isKingsHall(int variantSizew, int x, int y);
int isSpecialCell(int variantSize, int x, int y);

void initTaflBoard(TaflBoard* dest, enum Variant variant);

BoundingBox getBoundingBoxForCell(int x, int y, float scale);
Cell getSelectedCell(TaflBoard* board, Camera3D* cam);
bool isValidCell(Cell* cell, int size);

Model taflKing, defenderPawn, attackerPawn;

int main(){

	InitWindow(SWIDTH, SHEIGHT, "testing");

	Camera3D cam = setupCamera();

	//load king
	taflKing = LoadModel("res/model/textured_granite_king.obj");
	Texture2D graniteTexture = LoadTexture("res/texture/seamless-granite-2560x2560.png");
	SetMaterialTexture(&taflKing.materials[0], MAP_DIFFUSE, graniteTexture);
	//taflKing.materials[0].maps[MAP_DIFFUSE].texture = graniteTexture;

	//load defender pawn
	defenderPawn = LoadModel("res/model/granite_pawn.obj");
	SetMaterialTexture(&defenderPawn.materials[0], MAP_DIFFUSE, graniteTexture);

	//load attackerPawn
	attackerPawn = LoadModel("res/model/obsidian_pawn.obj");
	Texture2D obsidianTexture = LoadTexture("res/texture/obsidian_750x750.png");
	SetMaterialTexture(&attackerPawn.materials[0], MAP_DIFFUSE, obsidianTexture);
	
	Vector3 position = {0.0f, 0.0f, 0.0f};

	BoundingBox bounds = MeshBoundingBox(taflKing.meshes[0]); 
	
	//int state[TABLUT_SIZE][TABLUT_SIZE];
	enum Variant variant = Alea_Evangelii;
	initTaflBoard(&board, variant);
	printf("variant size: %d\n", board.size);
	

	Ray ray = { 0 };
	bool collision = false;
	SetCameraMode(cam, CAMERA_FREE);

	SetTargetFPS(60);

	Cell selectedCell = (Cell){ -1, -1 };

	while(!WindowShouldClose()){

		UpdateCamera(&cam);

		if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
			selectedCell = getSelectedCell(&board, &cam);
		}

		BeginDrawing();
			ClearBackground(RAYWHITE);

			BeginMode3D(cam);

				drawGrid(&board);

				//rlScalef(0.2f, 0.2f, 0.2f);
				//DrawBoundingBox(bounds, GREEN);

				if(isValidCell(&selectedCell, board.size)){
					DrawBoundingBox(getBoundingBoxForCell(selectedCell.x, selectedCell.y, 10.0f), GREEN);
				}

			EndMode3D();
			
			#ifdef DEBUG
				DrawFPS(10,10);
			#endif

		EndDrawing();

	}
	CloseWindow();

	return 0;
}

void drawGrid(TaflBoard* board){
	//TODO take in an actual grid object or something
	int i,j;
	int lastStyle = 1;//DARK
	int variantSize = board->size;
	Vector3 cellSize = (Vector3){10.0f, 1.0f, 10.0f};
	for(i=0; i < variantSize; i++){
		for(j=0; j < variantSize; j++){
			//TODO add logic for annotations
			Vector3 pos = (Vector3){10.0f*i, 0.0f, 10.0f*j};
			if(isSpecialCell(variantSize, i, j)){
				DrawCubeV(pos, cellSize, YELLOW);
			}else{
				Color col = lastStyle == 1 ? DARK : LIGHT;
				DrawCubeV(pos, cellSize, col);
			}
			lastStyle = lastStyle == 1 ? 0 : 1;

			if( (board->state[i][j] & B) > 0){
				DrawModel(attackerPawn, (Vector3){i*10.0f, 0.0f, j*10.0f}, 0.2f, WHITE);
			}
			else if( (board->state[i][j] & W) > 0){
				DrawModel(defenderPawn, (Vector3){i*10.0f, 0.0f, j*10.0f}, 0.2f, WHITE);
			}
			else if( (board->state[i][j] & K) > 0){
				DrawModel(taflKing, (Vector3){i*10.0f, 0.0f, j*10.0f}, 0.2f, WHITE);
			}
		}
	}
}

Cell getSelectedCell(TaflBoard* board, Camera3D* cam){
	Cell cell = (Cell){ -1, -1 }; //init to an invalid cell
	Ray ray = GetMouseRay(GetMousePosition(), (*cam));
	bool isSelected = false;
	int i,j;

	for(i=0; i < board->size; i++){
		for(j=0; j < board->size; j++){
			isSelected = CheckCollisionRayBox(
				ray, 
				getBoundingBoxForCell(i, j, 10.0f)
			);
			if(isSelected){
				cell.x = i;
				cell.y = j;
				return cell;
			}
		}
	}

	return cell;
}

BoundingBox getBoundingBoxForCell(int x, int y, float scale){
	return (BoundingBox){
			(Vector3){ scale*x-scale/2.0f, 1.0f, scale*y-scale/2.0f}, 
			(Vector3){scale*(x+1)-scale/2.0f, 1.0f, scale*(y+1)-scale/2.0f}
		};
}

int isCorner(int variantSize, int x, int y){
	return x == 0 && y == 0 ||
	x == 0 && y == variantSize-1 ||
	x == variantSize-1 && y == 0 ||
	x == variantSize-1 && y == variantSize-1;
}

int isKingsHall(int variantSize, int x, int y){
	return x == variantSize/2 && y == variantSize/2; 
}

int isSpecialCell(int variantSize, int x, int y){
	return isKingsHall(variantSize, x, y) || isCorner(variantSize, x, y);
}

bool isValidCell(Cell* cell, int size){
	return cell->x >= 0 && cell->y >= 0
	&& cell->y < size && cell->x < size;
}

Camera3D setupCamera(){
	Camera3D camera = {0};
	camera.position = (Vector3){150.0f, 40.0f, 150.0f};
	camera.target = (Vector3){0.0f, 0.0f, 0.0f};
	camera.up = (Vector3){0.0f, 1.0f, 0.0f};
	camera.fovy = 45.0f;
	camera.type = CAMERA_PERSPECTIVE;

	return camera;
}

void initTaflBoard(TaflBoard* dest, enum Variant variant){
	int i,j;
	switch(variant){
		case Brandubh:
			dest->size = BRANDUBH_SIZE;
			for(i=0; i < BRANDUBH_SIZE; i++){
				for(j=0; j < BRANDUBH_SIZE; j++){
					dest->state[i][j] = BRANDUBH[i][j];
				}
			}
			break;
		case Gwddbwyll:
			dest->size = GWDDBWYLL_SIZE;
			for(i=0; i < GWDDBWYLL_SIZE; i++){
				for(j=0; j < GWDDBWYLL_SIZE; j++){
					dest->state[i][j] = GWDDBWYLL[i][j];
				}
			}
			break;
		case Fidchell:
			dest->size = FIDCHELL_SIZE;
			for(i=0; i < FIDCHELL_SIZE; i++){
				for(j=0; j < FIDCHELL_SIZE; j++){
					dest->state[i][j] = FIDCHELL[i][j];
				}
			}
			break;
		case Ard_Ri:
			dest->size = ARD_RI_SIZE;
			for(i=0; i < ARD_RI_SIZE; i++){
				for(j=0; j < ARD_RI_SIZE; j++){
					dest->state[i][j] = ARD_RI[i][j];
				}
			}
			break;
		case Tablut:
			dest->size = TABLUT_SIZE;
			for(i=0; i < TABLUT_SIZE; i++){
				for(j=0; j < TABLUT_SIZE; j++){
					dest->state[i][j] = TABLUT[i][j];
				}
			}
			break;
		case Tawlbwrdd:
			dest->size = TAWLBWRDD_SIZE;
			for(i=0; i < TAWLBWRDD_SIZE; i++){
				for(j=0; j < TAWLBWRDD_SIZE; j++){
					dest->state[i][j] = TAWLBWRDD[i][j];
				}
			}
			break;
		case Tawlbwrdd_Alternate:
			dest->size = TAWLBWRDD_ALT_SIZE;
			for(i=0; i < TAWLBWRDD_ALT_SIZE; i++){
				for(j=0; j < TAWLBWRDD_ALT_SIZE; j++){
					dest->state[i][j] = TAWLBWRDD_ALTERNATE[i][j];
				}
			}
			break;
		case Tawlbwrdd_Alternate_2:
			dest->size = TAWLBWRDD_ALT_2_SIZE;
			for(i=0; i < TAWLBWRDD_ALT_2_SIZE; i++){
				for(j=0; j < TAWLBWRDD_ALT_2_SIZE; j++){
					dest->state[i][j] = TAWLBWRDD_ALTERNATE_2[i][j];
				}
			}
			break;
		case Hnefatafl:
			dest->size = HNEFATAFL_SIZE;
			for(i=0; i < HNEFATAFL_SIZE; i++){
				for(j=0; j < HNEFATAFL_SIZE; j++){
					dest->state[i][j] = HNEFATAFL[i][j];
				}
			}
			break;
		case Large_Hnefatafl:
			dest->size = LARGE_HNEFATAFL_SIZE;
			for(i=0; i < LARGE_HNEFATAFL_SIZE; i++){
				for(j=0; j < LARGE_HNEFATAFL_SIZE; j++){
					dest->state[i][j] = LARGE_HNEFATAFL[i][j];
				}
			}
			break;
		case Alea_Evangelii:
			dest->size = ALEA_EVANGELII_SIZE;
			for(i=0; i < ALEA_EVANGELII_SIZE; i++){
				for(j=0; j < ALEA_EVANGELII_SIZE; j++){
					dest->state[i][j] = ALEA_EVANGELII[i][j];
				}
			}
			break;
	}
}
