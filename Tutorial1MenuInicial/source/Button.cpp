



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
CButton::CButton(const char* nameSprite, const char* text, Vector2* position){
	
}

CButton::CButton(CSprite *sprite, CText *text, Vector2* position){
	
	text->WriteText(*position,"A");
	sprite->CreateSprite(position);
	/*
	_sprite = new CSprite(*sprite);
	CBackground *background = new CBackground("bg/nfl",256,256);

	background->CreateBackground(false);
	background->CreateBackground(true);

	
	CText *text = new CText("fnt/default",256,256);
	u8 colorWhite;
	u8 colorGreen;

	Vector2 position(5,5);
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
	*/
	
} // CButton

CButton::CButton(CSprite *bg, CSprite *fg, Vector2* position){
	_position = new Vector2(*position);
	
	_bgSprite = bg;
	_bgSprite ->CreateSprite(_position);
	_fgSprite = fg;
	_fgSprite ->CreateSprite(_position);
} // CButton

// Destructor clase CButton
CButton::~CButton(void) {
	delete _bgSprite;
	delete _fgSprite;
	delete _text;
	delete _position;
} // ~CButton




/*
	Metodos de la clase "CButton"
*/
bool CButton::IsTouched(){
	Vector2 *posScreen = CInput::getInstance()->getTouchPos();

	if(posScreen->getX() > _position->getX() ) {
		if( posScreen->getX() < (_position->getX() + _bgSprite->getSize()->getX() ) ){
			if(posScreen->getY() > _position->getY() ) {
				if( posScreen->getY() < (_position->getY() + _bgSprite->getSize()->getY() ) ){
					return true;
				}
			}
		}
		
	}
	return false;
} // IsTouched