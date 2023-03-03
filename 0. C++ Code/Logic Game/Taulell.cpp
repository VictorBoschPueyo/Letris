#include <iostream>
#include <fstream>

#include "Taulell.h"

Taulell::Taulell() {
	m_columnaAct = 0;
	m_filaAct = 0;
	string normalPath;
	string pressedPath;
	char lletra;
	int voc = 0, con = 0;

	for (int i = 0; i < 26; i++) { //posar les vocals al array de vocals i tal
		lletra = 97 + i;
		normalPath = "./data/Letters/white_" + std::to_string(i) + ".png";
		pressedPath = "./data/Letters/yellow_" + std::to_string(i) + ".png";

		if (i == 0 || i == 4 || i == 8 || i == 14 || i == 20) {
			vocals[voc].setCaracter(lletra);
			vocals[voc].setCamiNormal(normalPath);
			vocals[voc].setCamiPressed(pressedPath);
			voc++;
		}
		else {
			consonants[con].setCaracter(lletra);
			consonants[con].setCamiNormal(normalPath);
			consonants[con].setCamiPressed(pressedPath);
			con++;
		}
	}
}

Taulell::~Taulell() { }

void Taulell::renderTaulell(int mousePosX, int mousePosY, bool mousePressed) {
	for (int i = 0; i < 8; i++) { //mirar cada component del array i fer render de cada lletra de cada vector
		if (taula[i].size() != 0) {
			for (int j = 0; j < taula[i].size(); j++) {
				if (taula[i][j].renderLletra(mousePosX, mousePosY, mousePressed)) { //es true si la lletra ha canviat d'estat
					if (taula[i][j].getApretat()) {
						if (paraulaCandidata.size() == 9) {
							//eliminar tota la paraula candidata
						}
						else {
							taula[i][j].setPosicioParaulaBuida(paraulaCandidata.size());
							paraulaCandidata.push_back(taula[i][j].getCamiNormal());
							caractersParaulaCandidata.push_back(taula[i][j].getCaracter());
							taula[i][j].setApretatAnterior(true);
						}
					}
				}
			}
		}
	}
}

void Taulell::eliminarParaulaCandidata() {
	if (paraulaCandidata.size() != 0) {
		paraulaCandidata.resize(0);
		caractersParaulaCandidata.resize(0);
	}

	for (int i = 0; i < 8; i++) { //mirar cada component del array i fer render de cada lletra de cada vector
		if (taula[i].size() != 0) {
			for (int j = 0; j < taula[i].size(); j++) {
				if (taula[i][j].getApretat()) {
					taula[i][j].deseleccionar();
				}
			}
		}
	}
}

void Taulell::renderParaulaCandidata() {
	Sprite camiLletra;
	if (paraulaCandidata.size() != 0) {
		for (int i = 0; i < paraulaCandidata.size(); i++) {
			camiLletra.create(paraulaCandidata[i].c_str());
			camiLletra.draw(37 + i * 51, 700);
		}
	}
}

bool Taulell::calcularPosicio(bool nova, int& fila, int& columna) {
	int referencia = taula[0].size();
	fila = referencia;
	columna = 0;
	for (int i = 1; i < 8; i++) {
		if (referencia > taula[i].size()) {
			fila = taula[i].size();
			columna = i;
			referencia = taula[i].size();
		}
	}

	if (nova) {
		m_filaAct = fila;
		m_columnaAct = columna;
	}

	if (referencia == 10) {
		return false;
	}
	else {
		return true;
	}
}

Lletra Taulell::calcularLletra(int random) {
	if (random <= 55) {
		int agafar = rand() % 5;
		//assignar els valors d'una vocal aleatoria a lletraActual
		lletraActual.setApretat(false);
		lletraActual.setCamiNormal(vocals[agafar].getCamiNoApretat());
		lletraActual.setCamiPressed(vocals[agafar].getCamiApretat());
		lletraActual.setCaracter(vocals[agafar].getCaracter());

		lletraActual.setColumna(m_columnaAct);
		lletraActual.setFila(m_filaAct);
		lletraActual.setPosX(37 + 51 * m_columnaAct);
		lletraActual.setPosY(147);
	}
	else {
		int agafar = rand() % 21;
		//assignar els valors d'una consonant aleatoria a lletraActual
		lletraActual.setApretat(false);
		lletraActual.setCamiNormal(consonants[agafar].getCamiNoApretat());
		lletraActual.setCamiPressed(consonants[agafar].getCamiApretat());
		lletraActual.setCaracter(consonants[agafar].getCaracter());

		lletraActual.setColumna(m_columnaAct);
		lletraActual.setFila(m_filaAct);
		lletraActual.setPosX(37 + 51 * m_columnaAct);
		lletraActual.setPosY(147);
	}
	return lletraActual;
}

void Taulell::afegeixLletra(Lletra l) {
	taula[m_columnaAct].push_back(l);
}

void Taulell::eliminarLletres() {
	vector<Lletra>::iterator iter, final;
	int j, longIndeElim;
	int indeEliminar[10];
	for (int i = 0; i < 8; i++) { //mirar cada component del array i guardarse els indexos de les lletres apretades
		if (taula[i].size() != 0) {
			j = 0;
			final = taula[i].end();
			longIndeElim = 0;
			for (iter = taula[i].begin(); iter != final; iter++) {
				if ((*iter).getApretat()) {
					indeEliminar[longIndeElim] = j;
					longIndeElim += 1;
				}
				else if (longIndeElim > 0) {
					(*iter).recolocar(longIndeElim);
				}
				j++;
			}

			iter = taula[i].begin();

			for (int k = longIndeElim - 1; k >= 0; k--) {
				taula[i].erase(iter + indeEliminar[k]);
			}
		}
	}
}

bool Taulell::comprovarParaula() {
	bool trobat = false;
	int i = 0;
	string paraula = "";
	for (int j = 0; j < caractersParaulaCandidata.size(); j++) {
		paraula += caractersParaulaCandidata[j];
	}
	while (!trobat) {
		if (diccionariSencer[i] == paraula) {
			return true;
		}
		else {
			i++;
			if (diccionariSencer.size() == i) {
				return false;
			}
		}
	}
}

void Taulell::omplirDiccionari(string diccionari) {
	ifstream fin;
	fin.open(diccionari);
	if (fin.fail()) {
		cout << "No es pot obrir el fitxer" << endl;
		system("PAUSE");
	}
	while (!fin.eof()) {
		string paraula = "";
		getline(fin, paraula);
		diccionariSencer.push_back(paraula);
	}
}

void Taulell::buidarDiccionari() {
	int tamanyDiccionari = diccionariSencer.size();
	for (int i = 0; i < tamanyDiccionari; i++) {
		diccionariSencer.pop_back();
	}
}

void Taulell::buidarTaula() {
	int tamany;
	for (int i = 0; i < 8; i++) {
		tamany = taula[i].size();
		for (int j = 0; j < tamany; j++) {
			taula[i].pop_back();
		}
	}
}
