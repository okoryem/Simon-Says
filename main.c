#include "project.h"

int main(void) {
	int gamePlayLoop = 1;
	int num;
	openDisplay();
	openInput();
	openTilt();

	while (gamePlayLoop == 1) {
		num = randNum();

		if (num <= 3) {
			printf("\nNew Symbol Tile\n");
			drawSymbol(num);
			gamePlayLoop = checkCorrect(checkTilt(num));
			clearDisplay();
		} else {
			printf("\nNew Symbol Joy\n");
			drawSymbol(num);
			gamePlayLoop = checkCorrect(checkChoice(num));
			clearDisplay();
		}

		sleep(1);

	}


	closeTilt();
	closeInput();
	clearDisplay();
	closeDisplay();
	return 1;
}
