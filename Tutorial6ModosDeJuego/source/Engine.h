#ifndef __ENGINE_H__
#define __ENGINE_H__





/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/


// Includes propietarios NDS
#include <nds.h>

#include "Includes.h"

// Defines
class CMenu;
class CBattle;

// Clase CEngine
class CEngine {

	public:
		
		enum Scenes{MENU, ARCADE, VERSUS, OPTION, SIZE};
		
		// Contructores
		CEngine();
		
		// Destructor
		~CEngine(void);

		
		//	Metodos
		

		void ChangeScene(Scenes newScene);

		void InitEngine();

		void MainBucle();

		// Gets y sets
		CMenu* getMenu(){return _menu;};	
		
	private:
		
		void UnloadCurrentScene();
		void LoadNewScene();
		void ExecuteChangeScene();

		CEngine::Scenes _currentScene;
		CEngine::Scenes _newScene;
		// scenes
		CMenu* _menu;
		CBattle* _arcade;

		// others
		CInputs *_input;
		CTime *_time;
};

#endif