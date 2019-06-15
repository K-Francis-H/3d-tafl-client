#ifndef TAFLBOARD_H
#define TAFL_BOARD_H

typedef struct{
	int size;
	//not ideal from efficiency standpoint, but keeps boards always static
	//which is really nice, dont really want to debug int** issues
	int state[ALEA_EVANGELII_SIZE][ALEA_EVANGELII_SIZE];
	Model *king, *attacker, *defender;
} TaflBoard;

TaflBoard board;

typedef struct{
	int x,y;
} Cell;

void drawGrid(TaflBoard* board, Model* attackerPawn, Model* defenderPawn, Model* taflKing);
int isCorner(int variantSize, int x, int y);
int isKingsHall(int variantSizew, int x, int y);
int isSpecialCell(int variantSize, int x, int y);
Color getSelectionColorForCell(int x, int y);

void initTaflBoard(TaflBoard* dest, enum Variant variant, Model* kingModel, Model* defender, Model* attacker);

BoundingBox getBoundingBoxForCell(int x, int y, float scale);
BoundingBox getBoundingBoxForPiece(TaflBoard* board, int x, int y, float scale);
Cell getSelectedCell(TaflBoard* board, Camera3D* cam);
bool isValidCell(Cell* cell, int size);
#endif
