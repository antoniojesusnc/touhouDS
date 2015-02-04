#ifndef __MENU_H__
#define __MENU_H__





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
class CEngine;
class CButton;
class CText;
class CSprite;
class CBackground;

// Clase CMenu
class CMenu {

	public:
				
		// Contructores
		CMenu(CEngine* engine);
		
		// Destructor
		~CMenu(void);

		

		//	Metodos
		void InitMenu();

		void Update(vfloat32 time);

		
	private:
		
		CBackground *_topBackground;
		CBackground *_botBackground;


		//CSprite *_genericSprite;
		//CText *_genericText;

		CEngine* _engine;
		CButton* _buttons[4];

		u8 _indexBucle;
		u8 _buttonSelected;
};



#endif
