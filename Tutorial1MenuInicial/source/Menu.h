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


// Defines


// Clase CMenu
class CMenu {

	public:
		
		static u8 MAX_LAYER_MENU;
		enum Scenes{MENU, ARCADE, VERSUS, OPTION};
		
		// Contructores
		CMenu();
		
		// Destructor
		~CMenu(void);

		
		//	Metodos
		void Update();

		void ChangeScene(Scenes newScene);

		// Gets y sets
		CMenu* getMenu(){return _menu;};	
		
	private:
		
		CMenu* _menu;
};



#endif
