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
class CSpriteAnimated;
class CText;
class CPalette;

// Clase CButton
class CButton {

	public:
				
		// Contructores
		CButton(const char* nameSprite,int width, int height, Vector2* position, bool isSelectable = false);

		// Destructor
		~CButton(void);

		

		// gets & sets
		void setSelected(bool selected);

		bool IsTouched();
		CSpriteAnimated * getFgSprite(void){return _sprite;}
		bool isSelected(){return _selected;}
		

	private:
		
		CSpriteAnimated *_sprite;
		Vector2 *_position;

		bool _isSelectable;
		bool _selected;
};



#endif
