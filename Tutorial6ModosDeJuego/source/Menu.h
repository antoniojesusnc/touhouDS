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
#include "Scene.h"


// Defines
class CScene;
class CButton;
class CText;
class CSprite;
class CBackground;

// Clase CMenu
class CMenu : public CScene {

	public:
				
		// Contructores
		CMenu(CEngine* engine);
		
		// Destructor
		~CMenu(void);

		

		//	Metodos
		void InitScene();

		void Update(vfloat32 time);

		
	private:
		//CSprite *_genericSprite;
		//CText *_genericText;
		CSprite* _logo01;
		CSprite* _logo02;

		CButton* _buttons[4];


		u8 _indexBucle;
		u8 _buttonSelected;
};



#endif
