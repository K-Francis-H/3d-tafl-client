#include "raylib.h"

#include "colors.h"
#include "tafl_variants.h"
#include "tafl_board.h"		//functions for manipulating game state

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// gcc main.c -o out.a -lraylib -lX11
//gcc main.c tafl_board.c tafl_variants.c -o out.a -lraylib -lX11



#define SWIDTH 1000
#define SHEIGHT 1000

#define TRUE 1
#define FALSE 0

#define DEBUG 

typedef struct{
	Cell start, end;
} Move;

Camera3D setupCamera();

const int DEFENDERS = W;
const int ATTACKERS = B;

Model taflKing, defenderPawn, attackerPawn;

int main(){

	InitWindow(SWIDTH, SHEIGHT, "testing");

	Camera3D cam = setupCamera();

	//game params
	int currentPlayer = B;

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
	enum Variant variant = Brandubh;//Alea_Evangelii;
	initTaflBoard(&board, variant, &taflKing, &defenderPawn, &attackerPawn);
	printf("variant size: %d\n", board.size);
	

	Ray ray = { 0 };
	bool collision = false;
	SetCameraMode(cam, CAMERA_FREE);

	SetTargetFPS(60);

	Cell selectedCell = (Cell){ -1, -1 };
	BoundingBox selectedPiece;
	bool isSelected = false;

	while(!WindowShouldClose()){

		UpdateCamera(&cam);

		if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){

			//check if player is in piece choosing state or move choosing state

			//if piece choosing
				//check the bounding box of pieces for the current player

			//else
				//check bounding boxes of available moves
			int i, j;
			
			
			Ray ray = GetMouseRay(GetMousePosition(), cam);
			for(i=0; i < board.size; i++){
				for(j=0; j < board.size; j++){
					selectedPiece = getBoundingBoxForPiece(&board, i, j, 0.2f);
					isSelected = CheckCollisionRayBox(
						ray, 
						selectedPiece
					);
					if(isKingsHall(i, j, board.size)){
						printf("is king selected: %d\n", isSelected);
					}
					if(isSelected){goto EXIT;}
				}

			}
			EXIT: ;

			//selectedCell = getSelectedCell(&board, &cam);
		}

		BeginDrawing();
			ClearBackground(RAYWHITE);

			BeginMode3D(cam);

				drawGrid(&board, &attackerPawn, &defenderPawn, &taflKing);

				//rlScalef(0.2f, 0.2f, 0.2f);
				//DrawBoundingBox(bounds, GREEN);

				if(isValidCell(&selectedCell, board.size)){
					//DrawBoundingBox(getBoundingBoxForCell(selectedCell.x, selectedCell.y, 10.0f), GREEN);
					Vector3 cellSize = (Vector3){10.0f, 1.0f, 10.0f};
					Vector3 pos = (Vector3){10.0f*selectedCell.x, 0.0f, 10.0f*selectedCell.y};
					DrawCubeV(pos, cellSize, getSelectionColorForCell(selectedCell.x, selectedCell.y));
				}

				if(isSelected){
					DrawBoundingBox(selectedPiece, GREEN);
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


Camera3D setupCamera(){
	Camera3D camera = {0};
	camera.position = (Vector3){150.0f, 40.0f, 150.0f};
	camera.target = (Vector3){0.0f, 0.0f, 0.0f};
	camera.up = (Vector3){0.0f, 1.0f, 0.0f};
	camera.fovy = 45.0f;
	camera.type = CAMERA_PERSPECTIVE;

	return camera;
}
