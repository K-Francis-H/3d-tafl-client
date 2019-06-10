#define E 0x00
#define W 0x01
#define B 0x02
#define K 0x04

#define SELECTED 8
#define VALID_MOVE 16
#define LAST_MOVE 32
#define FLAG_MASK (SELECTED | VALID_MOVE | LAST_MOVE)

#define BLACK_MASK B
#define WHITE_MASK (W | K)
#define PIECE_MASK (BLACK_MASK | WHITE_MASK)

#define TABLUT_SIZE 9
#define BRANDUBH_SIZE 7
#define GWDDBWYLL_SIZE 7
#define FIDCHELL_SIZE 7
#define ARD_RI_SIZE 7
#define EALDFAEDER_SIZE 9
#define TAWLBWRDD_SIZE 11
#define TAWLBWRDD_ALT_SIZE 11
#define TAWLBWRDD_ALT_2_SIZE 11
#define HNEFATAFL_SIZE 11
#define LARGE_HNEFATAFL_SIZE 13
#define ALEA_EVANGELII_SIZE 19

int BRANDUBH[BRANDUBH_SIZE][BRANDUBH_SIZE] = {
	{0,0,0,B,0,0,0},
	{0,0,0,B,0,0,0},
	{0,0,0,W,0,0,0},
	{B,B,W,K,W,B,B},
	{0,0,0,W,0,0,0},
	{0,0,0,B,0,0,0},
	{0,0,0,B,0,0,0}
	
};

int GWDDBWYLL[GWDDBWYLL_SIZE][GWDDBWYLL_SIZE] = {
	{0,0,B,0,B,0,0},
	{0,0,0,0,0,0,0},
	{B,0,0,W,0,0,B},
	{0,0,W,K,W,0,0},
	{B,0,0,W,0,0,B},
	{0,0,0,0,0,0,0},
	{0,0,B,0,B,0,0}
	
};

int FIDCHELL[FIDCHELL_SIZE][FIDCHELL_SIZE] = {
	{B,0,B,B,B,0,B},
	{0,0,0,W,0,0,0},
	{B,0,0,W,0,0,B},
	{B,W,W,K,W,W,B},
	{B,0,0,W,0,0,B},
	{0,0,0,W,0,0,0},
	{B,0,B,B,B,0,B}
	
};

int ARD_RI[ARD_RI_SIZE][ARD_RI_SIZE] = {
	{B,0,B,B,B,0,B},
	{0,0,0,B,0,0,0},
	{B,0,W,W,W,0,B},
	{B,B,W,K,W,B,B},
	{B,0,W,W,W,0,B},
	{0,0,0,B,0,0,0},
	{B,0,B,B,B,0,B}
	
};

int TABLUT[TABLUT_SIZE][TABLUT_SIZE] = {
	{0,0,0,B,B,B,0,0,0},
	{0,0,0,0,B,0,0,0,0},
	{0,0,0,0,W,0,0,0,0},
	{B,0,0,0,W,0,0,0,B},
	{B,B,W,W,K,W,W,B,B},
	{B,0,0,0,W,0,0,0,B},
	{0,0,0,0,W,0,0,0,0},
	{0,0,0,0,B,0,0,0,0},
	{0,0,0,B,B,B,0,0,0}
};

int TAWLBWRDD[TAWLBWRDD_SIZE][TAWLBWRDD_SIZE] = { 
	{0,0,0,0,B,B,B,0,0,0,0},
	{0,0,0,0,B,0,B,0,0,0,0},
	{0,0,0,0,0,B,0,0,0,0,0},
	{0,0,0,0,0,W,0,0,0,0,0},
	{B,B,0,0,W,W,W,0,0,B,B},
	{B,0,B,W,W,K,W,W,B,0,B},
	{B,B,0,0,W,W,W,0,0,B,B},
	{0,0,0,0,0,W,0,0,0,0,0},
	{0,0,0,0,0,B,0,0,0,0,0},
	{0,0,0,0,B,0,B,0,0,0,0},
	{0,0,0,0,B,B,B,0,0,0,0}
};

int TAWLBWRDD_ALTERNATE[TAWLBWRDD_ALT_SIZE][TAWLBWRDD_ALT_SIZE] = { 
	{0,0,0,0,B,B,B,0,0,0,0},
	{0,0,0,0,B,B,B,0,0,0,0},
	{0,0,0,0,0,W,0,0,0,0,0},
	{0,0,0,0,0,W,0,0,0,0,0},
	{B,B,0,0,W,W,W,0,0,B,B},
	{B,B,W,W,W,K,W,W,W,B,B},
	{B,B,0,0,W,W,W,0,0,B,B},
	{0,0,0,0,0,W,0,0,0,0,0},
	{0,0,0,0,0,W,0,0,0,0,0},
	{0,0,0,0,B,B,B,0,0,0,0},
	{0,0,0,0,B,B,B,0,0,0,0}
};

int TAWLBWRDD_ALTERNATE_2[TAWLBWRDD_ALT_2_SIZE][TAWLBWRDD_ALT_2_SIZE] = { 
	{0,0,0,B,B,B,B,B,0,0,0},
	{0,0,0,0,0,B,0,0,0,0,0},
	{0,0,0,0,0,W,0,0,0,0,0},
	{B,0,0,0,0,W,0,0,0,0,B},
	{B,0,0,0,W,W,W,0,0,0,B},
	{B,B,W,W,W,K,W,W,W,B,B},
	{B,0,0,0,W,W,W,0,0,0,B},
	{B,0,0,0,0,W,0,0,0,0,B},
	{0,0,0,0,0,W,0,0,0,0,0},
	{0,0,0,0,0,B,0,0,0,0,0},
	{0,0,0,B,B,B,B,B,0,0,0}
};

int HNEFATAFL[HNEFATAFL_SIZE][HNEFATAFL_SIZE] = {
	{0,0,0,B,B,B,B,B,0,0,0},
	{0,0,0,0,0,B,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{B,0,0,0,0,W,0,0,0,0,B},
	{B,0,0,0,W,W,W,0,0,0,B},
	{B,B,0,W,W,K,W,W,0,B,B},
	{B,0,0,0,W,W,W,0,0,0,B},
	{B,0,0,0,0,W,0,0,0,0,B},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,B,0,0,0,0,0},
	{0,0,0,B,B,B,B,B,0,0,0}
};

int LARGE_HNEFATAFL[LARGE_HNEFATAFL_SIZE][LARGE_HNEFATAFL_SIZE] = {
	{0,0,0,0,B,B,B,B,B,0,0,0,0},
	{0,0,0,0,0,0,B,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,W,0,0,0,0,0,0},
	{B,0,0,0,0,0,W,0,0,0,0,0,B},
	{B,0,0,0,0,0,W,0,0,0,0,0,B},
	{B,B,0,W,W,W,K,W,W,W,0,B,B},
	{B,0,0,0,0,0,W,0,0,0,0,0,B},
	{B,0,0,0,0,0,W,0,0,0,0,0,B},
	{0,0,0,0,0,0,W,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,B,0,0,0,0,0,0},
	{0,0,0,0,B,B,B,B,B,0,0,0,0}
};

int ALEA_EVANGELII[ALEA_EVANGELII_SIZE][ALEA_EVANGELII_SIZE] = {
	{0,0,B,0,0,B,0,0,0,0,0,0,0,B,0,0,B,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{B,0,0,0,0,B,0,0,0,0,0,0,0,B,0,0,0,0,B},
	{0,0,0,0,0,0,0,B,0,B,0,B,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,B,0,W,0,W,0,B,0,0,0,0,0,0},
	{B,0,B,0,0,B,0,0,0,0,0,0,0,B,0,0,B,0,B},
	{0,0,0,0,B,0,0,0,0,W,0,0,0,0,B,0,0,0,0},
	{0,0,0,B,0,0,0,0,W,0,W,0,0,0,0,B,0,0,0},
	{0,0,0,0,W,0,0,W,0,W,0,W,0,0,W,0,0,0,0},
	{0,0,0,B,0,0,W,0,W,K,W,0,W,0,0,B,0,0,0},
	{0,0,0,0,W,0,0,W,0,W,0,W,0,0,W,0,0,0,0},
	{0,0,0,B,0,0,0,0,W,0,W,0,0,0,0,B,0,0,0},
	{0,0,0,0,B,0,0,0,0,W,0,0,0,0,B,0,0,0,0},
	{B,0,B,0,0,B,0,0,0,0,0,0,0,B,0,0,B,0,B},
	{0,0,0,0,0,0,B,0,W,0,W,0,B,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,B,0,B,0,B,0,0,0,0,0,0,0},
	{B,0,0,0,0,B,0,0,0,0,0,0,0,B,0,0,0,0,B},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,B,0,0,B,0,0,0,0,0,0,0,B,0,0,B,0,0}
};
