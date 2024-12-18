#include "project.h"

#define WHITE 0xFFFF
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define YELLOW 0xFFE0
#define GREEN 0x07E0

sense_fb_bitmap_t *bm;
pi_framebuffer_t *fb;

void openDisplay(void) {
	fb = getFrameBuffer();
	bm = fb->bitmap;
	clearFrameBuffer(fb, BLACK);
}

void drawSymbol(int nextMove) {
	int seconds = 3;
	int hasPressed = 0;

	// checks right tilt
	if (nextMove == 0) {
		for(int i = 1; i < 7; i++) {
			for (int j = 3; j < 5; j++) {
				bm->pixel[i][j]=BLUE;
			}
		}
		bm->pixel[3][2]=BLUE;
		bm->pixel[3][1]=BLUE;
		bm->pixel[2][2]=BLUE;

		bm->pixel[3][5]=BLUE;
		bm->pixel[3][6]=BLUE;
		bm->pixel[2][5]=BLUE;
	}

	// checks left tilt
	if (nextMove == 1) {
		for(int i = 1; i < 7; i++) {
			for (int j = 3; j < 5; j++) {
				bm->pixel[i][j]=BLUE;
			}
		}
		bm->pixel[4][2]=BLUE;
		bm->pixel[4][1]=BLUE;
		bm->pixel[5][2]=BLUE;

		bm->pixel[4][5]=BLUE;
		bm->pixel[4][6]=BLUE;
		bm->pixel[5][5]=BLUE;
	}

	// checks forward tilt
	if (nextMove == 2) {
		for(int i = 1; i < 7; i++) {
			for (int j = 3; j < 5; j++) {
				bm->pixel[j][i]=BLUE;
			}
		}
		bm->pixel[2][3]=BLUE;
		bm->pixel[1][3]=BLUE;
		bm->pixel[2][2]=BLUE;

		bm->pixel[5][3]=BLUE;
		bm->pixel[6][3]=BLUE;
		bm->pixel[5][2]=BLUE;
	}

	// checks backward tilt
	if (nextMove == 3) {
		for(int i = 1; i < 7; i++) {
			for (int j = 3; j < 5; j++) {
				bm->pixel[j][i]=BLUE;
			}
		}
		bm->pixel[2][4]=BLUE;
		bm->pixel[1][4]=BLUE;
		bm->pixel[2][5]=BLUE;

		bm->pixel[5][4]=BLUE;
		bm->pixel[6][4]=BLUE;
		bm->pixel[5][5]=BLUE;
	}


	// checks right stick
	if (nextMove == 4) {
		for(int i = 1; i < 7; i++) {
			for (int j = 3; j < 5; j++) {
				bm->pixel[i][j]=YELLOW;
			}
		}
		bm->pixel[3][2]=YELLOW;
		bm->pixel[3][1]=YELLOW;
		bm->pixel[2][2]=YELLOW;

		bm->pixel[3][5]=YELLOW;
		bm->pixel[3][6]=YELLOW;
		bm->pixel[2][5]=YELLOW;
	}

	// checks left stick
	if (nextMove == 5) {
		for(int i = 1; i < 7; i++) {
			for (int j = 3; j < 5; j++) {
				bm->pixel[i][j]=YELLOW;
			}
		}
		bm->pixel[4][2]=YELLOW;
		bm->pixel[4][1]=YELLOW;
		bm->pixel[5][2]=YELLOW;

		bm->pixel[4][5]=YELLOW;
		bm->pixel[4][6]=YELLOW;
		bm->pixel[5][5]=YELLOW;
	}

	// checks forward stick
	if (nextMove == 6) {
		for(int i = 1; i < 7; i++) {
			for (int j = 3; j < 5; j++) {
				bm->pixel[j][i]=YELLOW;
			}
		}
		bm->pixel[2][3]=YELLOW;
		bm->pixel[1][3]=YELLOW;
		bm->pixel[2][2]=YELLOW;

		bm->pixel[5][3]=YELLOW;
		bm->pixel[6][3]=YELLOW;
		bm->pixel[5][2]=YELLOW;
	}

	// checks backward stick
	if (nextMove == 7) {
		for(int i = 1; i < 7; i++) {
			for (int j = 3; j < 5; j++) {
				bm->pixel[j][i]=YELLOW;
			}
		}
		bm->pixel[2][4]=YELLOW;
		bm->pixel[1][4]=YELLOW;
		bm->pixel[2][5]=YELLOW;

		bm->pixel[5][4]=YELLOW;
		bm->pixel[6][4]=YELLOW;
		bm->pixel[5][5]=YELLOW;
	}


	// checks press stick
	if (nextMove == 8) {
		for(int i = 3; i < 5; i++) {
			for (int j = 3; j < 5; j++) {
				bm->pixel[j][i]=RED;
			}
		}
		bm->pixel[4][2]=RED;
		bm->pixel[3][2]=RED;

		bm->pixel[5][3]=RED;
		bm->pixel[5][4]=RED;

		bm->pixel[2][3]=RED;
		bm->pixel[2][4]=RED;

		bm->pixel[4][5]=RED;
		bm->pixel[3][5]=RED;
	}


}

int checkCorrect(int isCorrect) {
	clearDisplay();
	if (isCorrect == 1) {
		for (int i = 0; i < 6; i++) {
			bm->pixel[i][i]=GREEN;
		}
		bm->pixel[6][4]=GREEN;
		bm->pixel[7][3]=GREEN;
		sleep(1);
		clearDisplay();
		return 1;
	} else if (isCorrect == 0) {
		for (int i = 0; i < 8; i++) {
			bm->pixel[i][i]=RED;
			bm->pixel[7-i][i]=RED;
		}
		sleep(1);
		clearDisplay();
		return 0;
	}
}
void closeDisplay(void) {
	if (fb != NULL) {
		clearFrameBuffer(fb, BLACK);
		freeFrameBuffer(fb);
		fb = NULL;
	}
}

void clearDisplay(void) {
	if (fb != NULL) {
		clearFrameBuffer(fb, BLACK);
	}
}
