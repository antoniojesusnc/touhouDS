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
class CScene;

// Clase CEngine
class CEngine {

	public:
		
		struct TOptions{
			u8 level;
			u8 character1;
			u8 character2;
			u8 time;
		};

		enum Scenes{MENU, ARCADE_BATTLE, ARCADE_CHAR_SELECT, VERSUS_BATTLE, VERSUS_CHAR_SELECT, OPTION, SIZE};
		
		// Contructores
		CEngine();
		
		// Destructor
		~CEngine(void);

		
		//	Metodos
		

		void ChangeScene(Scenes newScene);

		void InitEngine();

		void MainBucle();

		
		// gets & sets
		TOptions* getGameData(){
			return &_gameData;
		}
		
		


	private:
		
		void UnloadCurrentScene();
		void LoadNewScene();
		void ExecuteChangeScene();

		CEngine::Scenes _currentScene;
		CEngine::Scenes _newScene;
		// scenes
		CScene *_curScene;
		// others
		CInputs *_input;
		CTime *_time;
		TOptions _gameData;
};

#endif