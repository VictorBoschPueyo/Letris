#include "Lletra.h"
#include <iostream>

Lletra::Lletra(const string& cami_normal, const string& cami_pressed, char lletra, int fila, int columna) {
	m_camiNormal = cami_normal;
	m_camiPressed = cami_pressed;

	m_fila = fila;
	m_columna = columna;
	m_posX = 37 + 51 * columna;
	m_posY = 147;

	m_caracter = lletra;

	posicioParaulaBuida = -1;
	apretat = false;
	apretatAnterior = false;
}

Lletra::Lletra() { }

Lletra::~Lletra() { }

bool Lletra::renderLletra(int mousePosX, int mousePosY, bool mousePressed) {
	bool retorn;
	apretat = updateLletra(mousePosX, mousePosY, mousePressed);
	if (apretat) {
		m_pressed.create(m_camiPressed.c_str());
		m_pressed.draw(m_posX, m_posY);
	}
	else {
		m_normal.create(m_camiNormal.c_str());
		m_normal.draw(m_posX, m_posY);
	}

	if (apretat != apretatAnterior) {
		return true;
	}
	return false;
}

bool Lletra::updateLletra(int mousePosX, int mousePosY, bool mouseIsPressed) {
	if ((mousePosX >= m_posX) && (mousePosX <= m_posX + 50) && (mousePosY >= m_posY) && (mousePosY <= m_posY + 50)){
		if (mouseIsPressed) {
			if (apretat == true) {
				apretat = false;
				return false;
			}
			else {
				apretat = true;
				return true;
			}
		}
		else {
			if (apretat == true) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	else {
		if (apretat == true) {
			return true;
		}
		else {
			return false;
		}
	}
}

void Lletra::deseleccionar() {
	apretat = false;
	apretatAnterior = false;
	posicioParaulaBuida = -1;
}

void Lletra::recolocar(int posicions) {
	m_fila = m_fila - posicions;
	m_posY = m_posY + posicions * 51;
}