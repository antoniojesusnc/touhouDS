



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

u8 CText::MAX_COLOR_TEXT = 31;

u8 CText::Color = 0;

/*
	Metodos de la clase "CText"
*/

// Contructor clase CText
CText::CText(const char *text, u16 width, u16 height) {
	
	_layerCreated = false;
	
	_name = text;
	NF_LoadTextFont(text, _name, width, height, 0);	
} // CText

// Destructor clase CText
CText::~CText(void) {

	NF_ClearTextLayer(getScreen(),getLayer());
	NF_DeleteTextLayer(getScreen(),getLayer());
	NF_UnloadTextFont(getName());


	delete _name;
	delete _position;
	delete _name;
} // ~CText

// Crea el puntero externo a la clase
CText *Text;



/*
	Metodos de la clase "CText"
*/
u8 CText::CreateLayer(bool upScreen){

	_layerCreated = true;
	
	_layer = CBackground::Layer++;
	if(CBackground::Layer >= CBackground::MAX_LAYER_BACKGROUND){
		CBackground::Layer = 0;
	}

	
	_upScreen = upScreen;
	
	NF_CreateTextLayer(getScreen(), _layer, 0, _name);
	
	return _layer;
} // CreateTiledBg

// Create color
u8 CText::CreateColor(u8 red, u8 green, u8 blue){
	if(!isLayerCreated()){
		CreateLayer();
	}

	_color = Color++;

	NF_DefineTextColor(getScreen(), _layer, _color, red, green, blue);

	if(Color >= MAX_COLOR_TEXT){
		Color = 0;
	}

	return _color;
} // CreateColor
		
void CText::setColor(u8 newColor){
	NF_SetTextColor(getScreen(), _layer, _color);

	_color = newColor;
} // setColor

// Write text
void CText::WriteText(const Vector2 &newPosition, const char* text, ...){
	
	if(!isLayerCreated()){
		CreateLayer();
	}	
	//char finalText[256];
	//sprintf(finalText, text, ...);
	delete _position;
	_position = new Vector2(newPosition);
	
	NF_WriteText(getScreen(), _layer, _position->getX(), _position->getY(), text);
} // MoveTextToPos
