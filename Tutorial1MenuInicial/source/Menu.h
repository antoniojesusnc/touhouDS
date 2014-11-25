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

// Clase CMenu
class CMenu {

	public:
				
		// Contructores
		CMenu(CEngine* engine);
		
		// Destructor
		~CMenu(void);

		
		//	Metodos
		void Update();

		
	private:
		
		CEngine* _engine;
};



#endif
