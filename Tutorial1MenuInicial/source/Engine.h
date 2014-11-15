#ifndef __ENGINE_H__
#define __ENGINE_H__





/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/


// Includes propietarios NDS
#include <nds.h>
#include "Menu.h"
#include "Math.h"



// Defines


// Clase CEngine
class CEngine {

	public:
		
		enum Scenes{MENU, ARCADE, VERSUS, OPTION};
		
		// Contructores
		CEngine();
		
		// Destructor
		~CEngine(void);

		
		//	Metodos
		void Update();

		void ChangeScene(Scenes newScene);

		// Gets y sets
		CMenu* getMenu(){return _menu;};	
		
	private:
		
		CMenu* _menu;
};



#endif
