



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
#include "Inputs.h"

#include "Debug.h"

/*
	Metodos de la clase "CButton"
*/


// Contructor clase CButton
CButton::CButton(const char* nameSprite,int width, int height, Vector2* position, bool isSelectable){
	
	_isSelectable = isSelectable;
	_selected = false;
	_sprite = new CSpriteAnimated(nameSprite, nameSprite,width, height,_isSelectable?2:1);
	
	_sprite->MoveSpriteToVRam(false,true);
	_sprite->CreateSprite(position);
	_sprite->setOrder(0);

	_position = new Vector2(*position);

} // ctor

// Destructor clase CButton
CButton::~CButton(void) {
	
	delete _sprite;
	

	//delete _position;
} // ~CButton

void CButton::setSelected(bool selected){
	if(_isSelectable){
		_selected = selected;
		_sprite->setFrame(_selected?1:0);
	}
} // setSelected


/*
	Metodos de la clase "CButton"
*/
bool CButton::IsTouched(){
	Vector2 *posScreen = CInputs::getInstance()->getTouchPos();
	
	if(posScreen->getX() > _position->getX() ) {
		if( posScreen->getX() < (_position->getX() + _sprite->getSize()->getX() ) ){
			if(posScreen->getY() > _position->getY() ) {
				if( posScreen->getY() < (_position->getY() + _sprite->getSize()->getY() ) ){
					return true;
				}
			}
		}
		
	}
	
	return false;
} // IsTouched