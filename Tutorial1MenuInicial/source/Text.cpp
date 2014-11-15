



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
#include "Text.h"


// static variables

u8 CText::MAX_LAYER_TEXT = 4;

u8 CText::Layer = 0;

/*
	Metodos de la clase "CText"
*/

// Contructor clase CText
CText::CText(char *text, u8 width, u8 height) {
	
	_layerCreated = false;
	
	_name = text;
	NF_LoadTextFont(text, _name, width, height, 0);	
} // CText

CText::CText(CText &text) {
	if(text.isLayerCreated()){
		_layerCreated = true;
		_layer = text.getLayer();
		_upScreen = text.isUpScreen();
		_name = text.getName();
	}
} // CText

// Destructor clase CText
CText::~CText(void) {
}

// Crea el puntero externo a la clase
CText *Text;



/*
	Metodos de la clase "CText"
*/
u8 CText::CreateLayer(bool upScreen){

	_layerCreated = true;
	_layer = Layer++;
	_upScreen = upScreen;
	
	NF_CreateTextLayer(getScreen(), _layer, 0, _name);
	
	if(Layer >= MAX_LAYER_TEXT){
		Layer = 0;
	}

	return _layer;
} // CreateTiledBg

// Mueve las bolas
void CText::WriteText(Vector2 &newPosition, char* text, ...){
	
	if(!_layerCreated)
		CreateLayer();
		
	char finalText[256];
	//sprintf(finalText, text, ...);

	_position = newPosition;
	
	NF_WriteText(getScreen(), _layer, _position.x, _position.y, finalText);
} // MoveTextToPos
