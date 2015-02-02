



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
#include "Button.h"
#include "Sprite.h"
#include "Text.h"
#include "Input.h"

#include "Debug.h"

/*
	Metodos de la clase "CButton"
*/


// Contructor clase CButton
CButton::CButton(const char* nameSprite,int width, int height, Vector2* position){
	
	_fgSprite = new CSprite(nameSprite, nameSprite,width, height);
	_fgSprite->MoveSpriteToVRam(false,true);
	_fgSprite->CreateSprite(position);
	
	_position = new Vector2(*position);

} // ctor

// Destructor clase CButton
CButton::~CButton(void) {
	
	if(_fgSprite != NULL){
		delete _fgSprite;
	}

	delete _position;
} // ~CButton




/*
	Metodos de la clase "CButton"
*/
bool CButton::IsTouched(){
	Vector2 *posScreen = CInput::getInstance()->getTouchPos();
	
	if(posScreen->getX() > _position->getX() ) {
		if( posScreen->getX() < (_position->getX() + _fgSprite->getSize()->getX() ) ){
			if(posScreen->getY() > _position->getY() ) {
				if( posScreen->getY() < (_position->getY() + _fgSprite->getSize()->getY() ) ){
					return true;
				}
			}
		}
		
	}
	
	return false;
} // IsTouched