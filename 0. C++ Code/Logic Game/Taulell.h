#pragma once

#include "../Graphic Lib/libreria.h"
#include <string>
#include <vector>
#include "Abecedari.h"
#include "Lletra.h"

using namespace std;

class Taulell {
public:
	Taulell();
	~Taulell();

	int getFilaActual() { return m_filaAct; }
	int getColumnaActual() { return m_columnaAct; }

	void afegeixLletra(Lletra l);
	void renderTaulell(int mousePosX, int mousePosY, bool mousePressed);
	void renderParaulaCandidata();
	void eliminarParaulaCandidata();
	void eliminarLletres();

	bool calcularPosicio(bool nova, int& fila, int& columna);
	Lletra calcularLletra(int random);
	bool comprovarParaula();
	void omplirDiccionari(string diccionari);
	void buidarDiccionari();
	void buidarTaula();

private:
	int m_filaAct;
	int m_columnaAct;

	abecedari vocals[5];
	abecedari consonants[21];

	vector<string> diccionariSencer;
	vector<char> caractersParaulaCandidata;
	vector<string> paraulaCandidata;

	Lletra lletraActual;
	vector<Lletra> taula[8];
};