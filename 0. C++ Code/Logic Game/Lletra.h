#pragma once

#include "../Graphic Lib/libreria.h"
#include "Abecedari.h"
#include <string>

using namespace std;

class Lletra{
public:
	Lletra();
	Lletra(const string& cami_normal, const string& cami_pressed, char lletra, int fila, int columna);
	~Lletra();

	int getFila() { return m_fila; }
	int getColumna() { return m_columna; }
	int getPosY() { return m_posY; }
	int getPosicioParaulaBuida() { return posicioParaulaBuida; }
	char getCaracter() { return m_caracter; }
	bool getApretat() { return apretat; }
	bool getApretatAnterior() { return apretatAnterior; }
	string getCamiNormal() { return m_camiNormal; }
	string getCamiPressed() { return m_camiPressed; }

	void setFila(int fila) { m_fila = fila; }
	void setColumna(int columna) { m_columna = columna; }
	void setPosX(int posX) { m_posX = posX; }
	void setPosY(int posY) { m_posY = posY; }
	void setPosicioParaulaBuida(int posicio) { posicioParaulaBuida = posicio; }
	void setCamiNormal(string camiNormal) { m_camiNormal = camiNormal; }
	void setCamiPressed(string camiPressed) { m_camiPressed = camiPressed; }
	void setApretat(bool pressed) { apretat = pressed; }
	void setApretatAnterior(bool pressedAnt) { apretatAnterior = pressedAnt; }
	void setCaracter(char c) { m_caracter = c; }

	bool renderLletra(int mousePosX, int mousePosY, bool mousePressed);
	bool updateLletra(int mousePosX, int mousePosY, bool mouseIsPressed);
	void deseleccionar();
	void recolocar(int posicions);

private:
	int m_fila;
	int m_columna;
	int m_posX;
	int m_posY;

	char m_caracter;

	bool apretat;
	bool apretatAnterior;
	int posicioParaulaBuida;

	string m_camiNormal;
	string m_camiPressed;

	Sprite m_normal;
	Sprite m_pressed;
};
