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
		CButton(const char* nameSprite,int width, int height, Vector2* position);

		// Destructor
		~CButton(void);

		

		// gets & sets
		bool IsTouched();
		CSprite * getFgSprite(void){return _fgSprite;}

		
	private:
		
		CSprite *_fgSprite;
		Vector2 *_position;

		
};



#endif
