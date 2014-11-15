



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
#include "Background.h"


// static variables

u8 CBackground::MAX_LAYER_BACKGROUND = 4;

u8 CBackground::Layer = 0;

/*
	Metodos de la clase "CBackground"
*/

// Contructor clase CBackground
CBackground::CBackground(char *background, u8 width, u8 height) {
	
	_name = background;
	NF_LoadTiledBg(background, _name, width, height);	
} // CBackground

// Destructor clase CBackground
CBackground::~CBackground(void) {
}

// Crea el puntero externo a la clase
CBackground *Background;



/*
	Metodos de la clase "CBackground"
*/
u8 CBackground::CreateBackground(bool upScreen){
	_layer = Layer++;
	_upScreen = upScreen;
	
	NF_CreateTiledBg(getScreen(), _layer, _name);
	
	if(Layer >= MAX_LAYER_BACKGROUND){
		Layer = 0;
	}

	return _layer;
} // CreateTiledBg

// Mueve las bolas
void CBackground::MoveBackgroundToPos(Vector2 newPosition) {

	_position = newPosition;
	// Mueve el background
	NF_ScrollBg(getScreen(), _layer, _position.x, _position.y);
} // MoveBackgroundToPos
