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
class CMenu;

// Clase CEngine
class CEngine {

	public:
		
		enum Scenes{MENU, ARCADE, VERSUS, OPTION};
		
		// Contructores
		CEngine();
		
		// Destructor
		~CEngine(void);

		
		//	Metodos
		

		void ChangeScene(Scenes newScene);

		void InitEngine();

		void Update();

		// Gets y sets
		CMenu* getMenu(){return _menu;};	
		
	private:
		
		CEngine::Scenes _currentScene;

		// scenes
		CMenu* _menu;
};



#endif
