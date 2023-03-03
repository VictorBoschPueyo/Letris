#pragma once

#include "../Graphic Lib/libreria.h"

//creem aquesta classe que mes endavant sera utiliztada per veure en quin estat ens trobem, depenent de l'estat farem unes accions o unes altres
//ara per ara, hem trobat important només posar si un dels estats es troba en true (es a dir que es el que es troba actiu

class Estats {
public:
	Estats() : mainMenu(true), playing(false), pause(false), gameOver(false) {}
	~Estats() { }

	void setMainMenu(bool main_menu) { mainMenu = main_menu; }
	void setPlaying(bool play) { playing = play; }
	void setPause(bool pausa) { pause = pausa; }
	void setGameOver(bool game_over) { gameOver = game_over; }

	int estatActual();

	bool getMainMenu() { return mainMenu; }
	bool getPlaying() { return playing; }
	bool getPause() { return pause; }
	bool getGameOver() { return gameOver; }

	void renderMainMenu();
	void renderPlaying();
	void renderGameOver();
private:
	bool mainMenu;
	bool playing;
	bool pause;
	bool gameOver;
};