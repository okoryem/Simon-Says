#include "project.h"

pi_joystick_t *js;
pi_i2c_t* device;


int checkingVar = -1;
int run = 1;
coordinate_t initialData = {0, 0, 0};
float initialX, initialY, initialZ;
void openInput(void) {
	js = getJoystickDevice();
}

void closeInput(void) {
	if (js != NULL) {
		freeJoystick(js);
		js = NULL;
	}
}

int randNum() {
	return time(NULL) % 9;
}

void checkJoyInput(void (*callback)(unsigned int code), int delay) {
	if (js != NULL) {
		pollJoystick(js, callback, delay);
	}
}

void handler(unsigned int code) {
	if (code == KEY_RIGHT) {
	// this is for down
		checkingVar = 7;
	} else if (code == KEY_LEFT) {
	// this if for up
		checkingVar = 6;
	} else if (code == KEY_UP) {
	// this is for right
		checkingVar = 4;
	} else if (code == KEY_DOWN) {
	// this is for left
		checkingVar = 5;
	} else if (code == KEY_ENTER) {
		checkingVar = 8;
	}
}

void interrupt_handler(int sig) {
	run = 0;
}

void openTilt(void) {
	signal(SIGINT, interrupt_handler);
	device = geti2cDevice();

	configureAccelGyro(device);
/*
	getGyroPosition(device, &initialData);
	initialX = initialData.x;
	initialY = initialData.y;
	initialZ = initialData.z;
*/
}

void closeTilt(void) {
	if (device != NULL) {
		freei2cDevice(device);
		device = NULL;
	}
}

int checkTilt(int nextMove) {
	int cnt = 0;

	getGyroPosition(device, &initialData);
	initialX = initialData.x;
	initialY = initialData.y;
	initialZ = initialData.z;

	if (device) {
		while(run && getGyroPosition(device, &initialData) && cnt < 10000) {
			checkJoyInput(handler, 10);
			if (getGyroPosition(device, &initialData)) {
				float xDifference = initialData.x - initialX;
				float yDifference = initialData.y - initialY;

				if (nextMove == 0 && xDifference >= 30) {
					return 1;
				} else if (nextMove == 0 && checkingVar != -1) {
					return 0;
				} else if ((xDifference <= -30 || yDifference >= 30 || yDifference <= -30) && nextMove == 0) {
					return 0;
				}


				if (nextMove == 1 && xDifference <= -30) {
					return 1;
				} else if (nextMove == 1 && checkingVar != -1) {
					return 0;
				} else if ((xDifference >= 30 || yDifference >= 30 || yDifference <= -30) && nextMove == 1) {
					return 0;
				}


				if (nextMove == 2 && yDifference >= 30) {
					return 1;
				} else if (nextMove == 2 && checkingVar != -1) {
					return 0;
				} else if ((xDifference <= -30 || xDifference >= 30 || yDifference <= -30) && nextMove == 2) {
					return 0;
				}


				if (nextMove == 3 && yDifference <= -30) {
					return 1;
				} else if (nextMove == 3 && checkingVar != -1) {
					return 0;
				} else if ((xDifference <= -30 || yDifference >= 30 || xDifference >= 30) && nextMove == 3) {
					return 0;
				}
				cnt++;
			}
		}
	}
	return 0;
}

int checkChoice(int nextMove) {
	getGyroPosition(device, &initialData);

	initialX = initialData.x;
	initialY = initialData.y;
	initialZ = initialData.z;

	int cnt = 0;
	while(cnt < 10000) {
		getGyroPosition(device, &initialData);
		float xDifference = initialData.x - initialX;
		float yDifference = initialData.y - initialY;

		checkJoyInput(handler, 10);
		if (checkingVar == nextMove) {

			checkingVar = -1;
			return 1;
		}

		if (xDifference >= 40 || xDifference <= -40 || yDifference >= 40 || yDifference <= -40) {
			return 0;
		}

		if (nextMove == 4 && checkingVar != -1 && checkingVar != 4) {
			checkingVar = -1;
			return 0;
		}

		if (nextMove == 5 && checkingVar != -1 && checkingVar != 5) {
			checkingVar = -1;
			return 0;
		}

		if (nextMove == 6 && checkingVar != -1 && checkingVar != 6) {
			checkingVar = -1;
			return 0;
		}

		if (nextMove == 7 && checkingVar != -1 && checkingVar != 7) {
			checkingVar = -1;
			return 0;
		}

		if (nextMove == 8 && checkingVar != -1 && checkingVar != 8) {
			checkingVar = -1;
			return 0;
		}

		cnt++;
	}
	return 0;
}
