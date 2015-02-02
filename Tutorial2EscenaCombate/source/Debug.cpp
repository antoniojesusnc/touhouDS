



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
#include "Debug.h"
#include "Text.h"


/*
	Metodos de la clase "CDebug"
*/

// Contructor clase CDebug
CDebug::CDebug() {	
	_text = new CText("fnt/default",256,256);
	_text->CreateLayer(false);

	_position = new Vector2();
} // CDebug

// Destructor clase CDebug
CDebug::~CDebug(void) {
	delete _text;
}

CDebug *CDebug::_instance = 0;

CDebug* CDebug::getInstance(){
	if(!_instance){
		_instance = new CDebug();
	}
	return _instance;
} // getPtr

/*
	Metodos de la clase "CDebug"
*/

void CDebug::WriteText(const char* text){
	
	/*
	nocashMessage(text );
	/*/
	_text->WriteText(*_position, text);
	/* */
}

void CDebug::WriteText(const char* text, u16 number){

	char finalText[256];
	sprintf(finalText, "%s %d       \n", text, number);

	WriteText(finalText);
} // WriteText

void CDebug::WriteText(const char* text, double number){

	char finalText[256];
	sprintf(finalText, "%s %f      \n", text, number);

	WriteText(finalText);
} // WriteText

void CDebug::WriteText(const char* text, Vector2 *vector){

	char finalText[256];
	sprintf(finalText, "%s X:%d Y:%d    \n", text, vector->getX(),vector->getY());

	WriteText(finalText);
} // WriteText

void CDebug::Update(){

	
} // Update
