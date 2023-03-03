#pragma once

#include "../Graphic Lib/libreria.h"
#include <string>

using namespace std;

class abecedari {
public:
	abecedari() { }
	~abecedari() { }

	void setCamiNormal(string camiNor) { m_camiNormal = camiNor; }
	void setCamiPressed(string camiApr) { m_camiPressed = camiApr; }
	void setCaracter(char c) { m_caracter = c; }

	string getCamiNoApretat() { return m_camiNormal; }
	string getCamiApretat() { return m_camiPressed; }
	char getCaracter() { return m_caracter; }

private:
	string m_camiNormal;
	string m_camiPressed;
	char m_caracter;
};