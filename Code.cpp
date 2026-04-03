#include <iostream>
#include "clsLoginScreen.h"

void StartSystem() {

	short trials = 2;

	while (trials != 0) {

		clsLoginScreen::ShowLoginScreen(trials);
		trials = 2;
	}
}

int main() {

	StartSystem();
}

