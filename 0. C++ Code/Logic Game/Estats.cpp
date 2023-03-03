#include "Estats.h"
#include "boto.h"
#include "../Graphic Lib/NFont/NFont.h"

void Estats::renderMainMenu() {
	Sprite fons("./data/GUI/MainMenu_BG.png");
	NFont textCatala("data/Fonts/FreeSans.ttf", 30, NFont::Color(0, 0, 0, 255));
	NFont textCastella("data/Fonts/FreeSans.ttf", 30, NFont::Color(0, 0, 0, 255));
	NFont textAngles("data/Fonts/FreeSans.ttf", 30, NFont::Color(0, 0, 0, 255));

	fons.draw(0, 0);
	textAngles.draw(80, 245, NFont::Scale(0.70f), "ANGLES");
	textAngles.draw(80, 195, NFont::Scale(0.70f), "CASTELLA");
	textAngles.draw(80, 145, NFont::Scale(0.70f), "CATALA");
}

void Estats::renderGameOver() {
	Sprite fons("./data/GUI/GameOver.png");
	fons.draw(0, 0);
}

void Estats::renderPlaying() {
	Sprite fons("./data/GUI/background_play.png");
	fons.draw(0, 0);
}

int Estats::estatActual() {
	if (getMainMenu()) {
		return 0;
	}
	else if (getPlaying()) {
		return 1;
	}
	else if (getPause()) {
		return 2;
	}
	else {
		return 3;
	}
}
