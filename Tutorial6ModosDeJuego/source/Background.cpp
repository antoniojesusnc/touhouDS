



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
#include "Debug.h"


// static variables

u8 CBackground::MAX_LAYER_BACKGROUND = 3;

u8 CBackground::Layer = 3;

/*
	Metodos de la clase "CBackground"
*/

// Contructor clase CBackground
CBackground::CBackground(const char *background, u16 width, u16 height) {
	
	_layer = CBackground::Layer++;
	if(CBackground::Layer >= CBackground::MAX_LAYER_BACKGROUND){
		CBackground::Layer = 1;
	}
	//_name = background;
	u8 size = strlen(background);
	_name = (char*)malloc(sizeof(char)*size+1);
	strcpy(_name,background);
	_name[size] = '\0';

	NF_LoadTiledBg(background, background, width, height);		
} // CBackground

// Destructor clase CBackground
CBackground::~CBackground(void) {

	NF_UnloadTiledBg(_name); // delete from ram
	
	NF_DeleteTiledBg(getScreen(), getLayer()); // delete from screen and vram
	

	free(_name);
	

	//delete[] _name;
	//delete _position;
}

// Crea el puntero externo a la clase
CBackground *Background;



/*
	Metodos de la clase "CBackground"
*/
u8 CBackground::CreateBackground(bool upScreen){
	
	_upScreen = upScreen;
	
	NF_CreateTiledBg(getScreen(), _layer, _name);
	
	

	return _layer;
} // CreateTiledBg

// Mueve las bolas
void CBackground::MoveBackgroundOffset(const Vector2 &offset) {

	*_position += offset;
	// Mueve el background
	NF_ScrollBg(getScreen(), _layer, _position->getX(), _position->getY());
} // MoveBackgroundToPos