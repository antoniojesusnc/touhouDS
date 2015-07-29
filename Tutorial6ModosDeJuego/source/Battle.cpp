



/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/

// Includes C/C++
#include <stdio.h>

// Includes propietarios NDS
#include <nds.h>

// Includes librerias propias
#include <nf_lib.h>

// Includes del programa
#include "Battle.h"
#include "Background.h"
#include "Sprite.h"
#include "Text.h"
#include "Button.h"
#include "Inputs.h"
#include "Hud.h"

#include "Character.h"
#include "Debug.h"

#include "Collision.h"

#include "XMLParser.h"

/*
	Metodos de la clase "CBattle"
*/


// Contructor clase CBattle
CBattle::CBattle(CEngine* engine):CScene(engine)  {
	
} // CBattle

// Destructor clase CBattle
CBattle::~CBattle(void) {
	/*
	delete [] _buttons;
	/*/

	for(vu8 i = 0; i < 2; ++i){
		delete _characters[i];
	}
	delete _hud;

} // ~CBattle

/*
	Metodos de la clase "CBattle"
*/

void CBattle::InitScene(){

	// backgrounds
	// top background
	
	
	
	
	
	// bot background
	//_botBackground = new CBackground("bg/bg3",256,256);
	/*_botBackground->CreateBackground(false);	
	*/
	
	Vector2 *pos = new Vector2(192-128,255*0.5f);
	
	char *character1= getPlayerNameById(_engine->getGameData()->character1);
	_characters[0] = new CCharacter(character1, false);
	_characters[0]->Init(pos);
	//free(character1);
	
	pos->setX(pos->getX()+64);
	char *character2 = getPlayerNameById(_engine->getGameData()->character1);
	_characters[1] = new CCharacter(character2, true);
	_characters[1]->Init(pos);
	//free(character2);
	//delete pos;
	
	_collision = new CCollision();

	_hud = new CHud();

	_hud->InitHud(_characters[0], _characters[1], 60);

	_remainingTime = 60;
	_acum = 0;
	
	char *level = getScenarioById(_engine->getGameData()->level);
	_topBackground = new CBackground(level,256,256);
	_topBackground->CreateBackground(true);
	//free(level);
	//_topBackground->CreateBackground(false);
	
	
	_botBackground = new CBackground("bg/battle/bg",256,256);
	_botBackground->CreateBackground(false);
	
	_pauseMenuOpen = false;
}

// Mueve las bolas
void CBattle::Update(vfloat32 time){
	
	
	if(_pauseMenuOpen){
		_hud->UpdatePause();
		if(_hud->getButtonPressed() != 0){
			if(_hud->getButtonPressed() == 1){
				// click in resume
				_hud->ShowPause(false);
				_pauseMenuOpen = false;
			}else{
				_engine->ChangeScene(CEngine::MENU);
			}
		}
	}else{
		if(CInputs::getInstance()->getCommands()[0] == CInputs::Start){
			_hud->ShowPause(true);
			_pauseMenuOpen = true;
			return;
		}

		_acum += time;

		_characters[0]->UpdateCharacter(time);
		_characters[1]->UpdateCharacter(time);
	
		_collision->CheckCollision(_characters[0], _characters[1]);
		_collision->CheckCollision(_characters[1], _characters[0]);

		if(_acum > 1){
			_acum -= 1;
			_remainingTime -= 1;		
		}

		_hud->Update(_characters[0],_characters[1],_remainingTime);
	}
} // Update


char* CBattle::getPlayerNameById(u8 id){
	switch(id){
		case 0: return "sakuya";
		case 1: return "sakuya";
		case 2: return "sakuya";
		case 3: return "sakuya";
	}

	return "sakuya";
} // getPlayerNameById

char* CBattle::getScenarioById(u8 id){
	switch(id){
		case 0: return "bg/battle/background01";
		case 1: return "bg/battle/background02";
		case 2: return "bg/battle/background03";
		case 3: return "bg/battle/background04";
	}

	return "bg/battle/background01";
} // getScenarioById