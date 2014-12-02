#ifndef __BUTTON_H__
#define __BUTTON_H__





/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/


// Includes propietarios NDS
#include <nds.h>
#include "Math.h"
#include "Engine.h"


// Defines
class CSprite;
class CText;

// Clase CButton
class CButton {

	public:
				
		// Contructores
		CButton(const char* nameSprite, const char* text, Vector2* position);

		CButton(CSprite *sprite, CText *text, Vector2* position);
		CButton(CSprite *sprite, Vector2* position);
		CButton(CSprite *bg, CSprite *fg, Vector2* position);
		
		// Destructor
		~CButton(void);

		

		// gets & sets
		bool IsTouched();
		CSprite * getBgSprite(void){return _bgSprite;}
		CSprite * getFgSprite(void){return _fgSprite;}
		CText * getText(void){return _text;}

		
	private:
		
		CSprite *_bgSprite;
		CSprite *_fgSprite;
		CText *_text;
		Vector2 *_position;

};



#endif
