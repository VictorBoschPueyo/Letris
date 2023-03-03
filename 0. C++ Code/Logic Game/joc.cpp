#include "joc.h"
#include "boto.h"
#include "Estats.h"
#include "Lletra.h"
#include "Taulell.h"
#include "../Graphic Lib/NFont/NFont.h"
#include <iostream>
#include <time.h>

using namespace std;

const int MAINMENU = 0;
const int PLAYING = 1;
const int PAUSE = 2;
const int GAMEOVER = 3;


//-----------------------------------------
// joc: porta el control de tot el joc
//-----------------------------------------
void joc()
{
    //Inicialitza un objecte de la classe Screen que s'utilitza per gestionar la finestra grafica
    Screen pantalla(MIDA_X, MIDA_Y);
    //Mostrem la finestra grafica
    pantalla.show();

	srand((int)(time(NULL)));

    float timer = 0.0f;
    NFont temps("data/Fonts/FreeSans.ttf", 30, NFont::Color(0,0,0,255));
    bool drawTimer = true;

	Estats estatsJoc;

	//Variables menu principal

	Button botoCatala("./data/GUI/Checkbox_Disabled.png", "./data/GUI/Checkbox_Enabled.png", 50, 150, 20, 20);
	Button botoCastella("./data/GUI/Checkbox_Disabled.png", "./data/GUI/Checkbox_Enabled.png", 50, 200, 20, 20);
	Button botoAngles("./data/GUI/Checkbox_Disabled.png", "./data/GUI/Checkbox_Enabled.png", 50, 250, 20, 20);
	Button start("./data/GUI/Button_Normal.png", "./data/GUI/Button_Pressed.png", 150, 700, 100, 200);
	NFont startText("data/Fonts/FreeSans.ttf", 30, NFont::Color(0, 0, 0, 255));

	string diccionari;

	bool selecCatala = false;
	bool selecCastella = false;
	bool selecAngles = false;

	bool selecCatalaAnte = false;
	bool selecCastellaAnte = false;
	bool selecAnglesAnte = false;
	/////////////////////////////////////////////////

	//Variables playing
	int posicioYCaiguda = 0;
	int fila, columna;
	int caiguda = 0, velocitat = 3;
	bool caient = false, colocat = true;
	int timerReferencia = 20;
	int aleatori;

	int posLletraX = 37, posLletraY = 147;
	
	Sprite rellotge("./data/GUI/Time_Bar.png");

	Taulell taula;
	Lletra l;

	Button botoCreu("./data/GUI/Btn_Circle_Close_1_Normal.png", "./data/GUI/Btn_Circle_Close_3_Pressed.png", 370, 750, 100, 100);
	Button botoPause("./data/GUI/Btn_Circle_Pause_1_Normal.png", "./data/GUI/Btn_Circle_Play_1_Normal.png", 390, 10, 100, 100);
	Button botoCheck("./data/GUI/Button_Normal.png", "./data/GUI/Button_Pressed.png", 150, 750, 200, 100);
	NFont checkText("data/Fonts/FreeSans.ttf", 30, NFont::Color(0, 0, 0, 255));
	/////////////////////////////////////////////////

	//Variable pause
	float tempsPausat;
	bool pausa = false;
	Sprite pausedButton("./data/GUI/Btn_Circle_Play_1_Normal.png");
	/////////////////////////////////////////////////

	//Variables game over
	float tempsEspera;
	/////////////////////////////////////////////////

    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;

    do
    {
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());
        // Captura tots els events de ratoli i teclat de l'ultim cicle
        pantalla.processEvents();

        bool mouseStatus = Mouse_getBtnLeft();
        bool mousePressed = Mouse_getButLeft();
        
        int mousePosX = Mouse_getX();
        int mousePosY = Mouse_getY();

        //mirar quin es l'estat actual
		int estatActual = estatsJoc.estatActual();

		switch (estatActual) {
			case MAINMENU:
				/////////////////////Setup pagina//////////////////////////
				estatsJoc.renderMainMenu();
				botoAngles.Render();
				botoCastella.Render();
				botoCatala.Render();
				start.Render();
				startText.draw(190, 715, NFont::Scale(1.0f), "START");
				///////////////////////////////////////////////////////////

				//////////////////////////Accions//////////////////////////
				selecCatala = botoCatala.UpdateRadio(mousePosX, mousePosY, mousePressed);
				selecCastella = botoCastella.UpdateRadio(mousePosX, mousePosY, mousePressed);
				selecAngles = botoAngles.UpdateRadio(mousePosX, mousePosY, mousePressed);

				if (selecCatala != selecCatalaAnte) {
					if (selecCastellaAnte) {
						selecCastella = botoCastella.UpdateRadio(60, 210, mousePressed);
					}
					if (selecAnglesAnte) {
						selecAngles = botoAngles.UpdateRadio(60, 260, mousePressed);
					}
				}

				if (selecCastella != selecCastellaAnte) {
					if (selecCatalaAnte) {
						selecCatala = botoCatala.UpdateRadio(60, 160, mousePressed);
					}
					if (selecAnglesAnte) {
						selecAngles = botoAngles.UpdateRadio(60, 260, mousePressed);
					}
				}

				if (selecAngles != selecAnglesAnte) {
					if (selecCatalaAnte) {
						selecCatala = botoCatala.UpdateRadio(60, 160, mousePressed);
					}
					if (selecCastellaAnte) {
						selecCastella = botoCastella.UpdateRadio(60, 210, mousePressed);
					}
				}

				if (start.Update(mousePosX, mousePosY, mousePressed)) { //nomes pasar a una altra pagina quan una de les tres opcions estigui
																		//seleccionada. Depen de la opcio es creara un diccionari o un altre
					if (selecCatala || selecCastella || selecAngles) {
						estatsJoc.setMainMenu(false);
						estatsJoc.setPlaying(true);
						if (selecCastella) {
							diccionari = "./data/Dictionaries/Spanish.dic";
						}
						else if (selecCatala) {
							diccionari = "./data/Dictionaries/Catalan.dic";
						}
						else {
							diccionari = "./data/Dictionaries/English.dic";
						}
						taula.omplirDiccionari(diccionari);
					}
				}

				selecCatalaAnte = selecCatala;
				selecCastellaAnte = selecCastella;
				selecAnglesAnte = selecAngles;
				///////////////////////////////////////////////////////////

				break;
			case PLAYING:
				/////////////////////Setup pagina//////////////////////////
				estatsJoc.renderPlaying();
				rellotge.draw(128, 10);
				botoCreu.Render();
				botoPause.Render();
				botoCheck.Render();
				checkText.draw(190, 775, NFont::Scale(1.0f), "CHECK");

				timer += deltaTime;

				if (timer > timerReferencia) { //cada 20 segons incrementem la velocitat
					timerReferencia += 20;
					velocitat += 2;
				}

				if (pausa) {
					timer = tempsPausat;
					pausedButton.draw(390, 10);
				}
				temps.draw(250, 25, NFont::Scale(0.85f), "%d", (int)timer);
				if (!pausa) { //nomes fer aquest proces quan el temps no estigui en pausa
					if (colocat) { //si la peça anterior esta colocada (o just es comença a jugar) es calcula un numero aleatori
							       //que sera la següent lletra a colocar, si no es poden posar mes anem a GameOver
						aleatori = rand() % 101;
						if (taula.calcularPosicio(true, fila, columna)) { //calcular la posicio a priori ( per aixo te el true) on ha d'anar la peca
																		  //si es fals vol dir que el tauler esta ja ple
							l = taula.calcularLletra(aleatori); //crear una lletra amb els valors calculats
							colocat = false;
							caient = true;
						}
						else {
							estatsJoc.setPlaying(false);
							estatsJoc.setGameOver(true);
							tempsEspera = timer;
						}
					}
					else { //es fa caure la lletra a la velocitat indicada, i quan arriba al final s'afegeix al vector que li toca 
						   //(i es corregeix la posicio perque potser no quadra del tot)
						if (caient) { //mentre cau, calcular la posicio per si ha canviat alguna cosa i canviar la fila on va a parar la lletra
									  //perque, sino, tindriem un espai en blanc i es superposarien dues lletres a la següent ronda.
									  //Quan la lletra hagi arribat al punt on ha d'arribar, l'afegim a l'estructura
							taula.calcularPosicio(false, fila, columna);
							if (fila != taula.getFilaActual() && columna == taula.getColumnaActual()) {
								l.setFila(fila);
							}

							caiguda += velocitat;
							if (caiguda > (9 - l.getFila()) * 51) {
								l.setPosY((9 - l.getFila()) * 51 + 147);
								taula.afegeixLletra(l);
								caient = false;
								colocat = true;
								caiguda = 0;
							}
							else {
								l.setPosY(147 + caiguda);
								l.renderLletra(mousePosX, mousePosY, mousePressed);
							}
						}
					}
				}
				else {
					l.renderLletra(mousePosX, mousePosY, mousePressed); //si el temps esta pausat, dibuixem la lletra al lloc del espai calculat l'ultima vegada
				}
				
				taula.renderTaulell(mousePosX, mousePosY, mousePressed); //dibuixem el tauler i la paraula candidata
				taula.renderParaulaCandidata();
				
				///////////////////////////////////////////////////////////

				/////////////////////Accions botons////////////////////////
				if (botoCreu.Update(mousePosX, mousePosY, mousePressed)) { //sempre que apretem el boto de creu eliminem la paraula candidata
					taula.eliminarParaulaCandidata();
				}
				if (botoCheck.Update(mousePosX, mousePosY, mousePressed)) { //si el boto esta apretat i la paraula existeix al abcedari eliminem
																			//la paraula candidata (ja que es correcta) i les lletres seleccionades,
																			//si no es correcta, eliminem la candidata nomes perque esta malament
					if (taula.comprovarParaula()) {
						taula.eliminarLletres();
						taula.eliminarParaulaCandidata();
					}
					else {
						taula.eliminarParaulaCandidata();
					}
					
				}

				if (botoPause.Update(mousePosX, mousePosY, mousePressed)) {
					if (pausa) {
						pausa = false;
					}
					else {
						pausa = true;
						tempsPausat = timer;
					}
				}
				///////////////////////////////////////////////////////////

				break;
			case PAUSE:
				estatsJoc.renderPlaying();
				break;
			case GAMEOVER:
				estatsJoc.renderGameOver();
				timer += deltaTime;
				if (timer > tempsEspera + 5.0f) { //esperem 5 segons, buidem el diccionari i la taula i tornem al menu principal
												  //i totes les variables que interesen aixi en general :)
					estatsJoc.setMainMenu(true);
					estatsJoc.setGameOver(false);
					taula.buidarDiccionari();
					taula.buidarTaula();
					caiguda = 0;
					velocitat = 3;
					timerReferencia = 20;
					timer = 0.0f;
					deltaTime = 0;
				}
				break;
		}

        
        // Actualitza la pantalla
        pantalla.update();

    } while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE));
    // Sortim del bucle si pressionem ESC

}
