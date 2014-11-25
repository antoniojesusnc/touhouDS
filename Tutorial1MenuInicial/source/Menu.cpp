



/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/

// Includes C/C++
#include <stdio.h>

// Includes propietarios NDS
#include <nds.h>

// Includes librerias propias
#include <nf_lib.h>

// Includes del programa
#include "Menu.h"
#include "Background.h"
#include "Text.h"

/*
	Metodos de la clase "CMenu"
*/


// Contructor clase CMenu
CMenu::CMenu(CEngine* engine) {
	_engine = engine;
	
	
	CBackground *background = new CBackground("bg/nfl",256,256);

	background->CreateBackground(false);
	background->CreateBackground(true);

	
	CText *text = new CText("fnt/default",256,256);
	u8 colorWhite;
	u8 colorGreen;

	Vector2 position = Vector2(5,5);
	text->CreateLayer(false);

	colorGreen = text->CreateColor(5,30,5);
	colorWhite = text->CreateColor(31,31,31);
	
	text->WriteText(position,"Arcade");

	text->setColor(colorWhite);
	position.x = 18;
	text->WriteText(position,"Vs Mode");
	
	position.y = 15;
	position.x = 5;
	text->WriteText(position,"Practice");

	position.x = 18;
	text->WriteText(position,"Options");

	
} // CMenu

// Destructor clase CMenu
CMenu::~CMenu(void) {
}

/*
	Metodos de la clase "CMenu"
*/

// Mueve*/as bolas
void CMenu::Update(){
	
} // Update
