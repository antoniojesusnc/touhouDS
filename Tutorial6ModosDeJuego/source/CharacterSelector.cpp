



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
#include "CharacterSelector.h"
#include "Background.h"
#include "Sprite.h"
#include "SpriteAnimated.h"
#include "Button.h"
#include "Inputs.h"

#include "Debug.h"

/*
	Metodos de la clase "CCharacterSelector"
*/


// Contructor clase CCharacterSelector
CCharacterSelector::CCharacterSelector(CEngine* engine):CScene(engine)  {
	
} // CCharacterSelector

// Destructor clase CCharacterSelector
CCharacterSelector::~CCharacterSelector(void) {
	/*

	delete _buttons[0];
	delete _topBackground;

	/*/
	

	delete _backButton;
	delete _startButton;

	//delete _character1;
	//delete _character2;

	for(vu8 i = 0; i < 4; ++i){
		delete _characterButtons[i];
	}

	for(vu8 i = 0; i < 4; ++i){
		delete _characters[i];
	}
	//free(_characterButtons);

	for(vu8 i = 0; i < 4; ++i){
		delete _scenarioButtons[i];
	}
	//free(_scenarioButtons);
	/* */
		
	


	
	

} // ~CCharacterSelector

/*
	Metodos de la clase "CCharacterSelector"
*/

void CCharacterSelector::InitScene(){

	
	
	// exit and play button	
	Vector2 *position = new Vector2(0,0);
	_backButton	= new CButton("sprite/charSelector/exitButton", 32, 16, position);
	position->setXY(255-32,0);
	_startButton = new CButton("sprite/charSelector/playButton", 32, 16, position);



	// characters
	position->setXY(64,80);
	_characterButtons[0] = new CButton("sprite/charSelector/aya", 32, 64, position, true);
	position->setXY(96,80);
	_characterButtons[1]	= new CButton("sprite/charSelector/sakuya", 32 , 64, position, true);
	position->setXY(128,80);
	_characterButtons[2] = new CButton("sprite/charSelector/hong", 32, 64, position, true);
	position->setXY(160,80);
	_characterButtons[3] = new CButton("sprite/charSelector/tenshi", 32, 64, position, true);

	// scenarios
	position->setXY(0,150);
	_scenarioButtons[0] = new CButton("sprite/charSelector/bg1", 64, 32, position, true);
	position->setXY(64,150);
	_scenarioButtons[1] = new CButton("sprite/charSelector/bg2", 64 ,32, position, true);
	position->setXY(128,150);
	_scenarioButtons[2] = new CButton("sprite/charSelector/bg3", 64, 32, position, true);
	position->setXY(192,150);
	_scenarioButtons[3] = new CButton("sprite/charSelector/bg4", 64, 32, position, true);

	free(position);
	
	// load characters in memory

	//float allDurations[8] = {0.2f,0.2f,0.2f,0.2f,0.2f,0.2f,0.2f,0.2f};
	
	float *allDurations = (float*)malloc(sizeof(float)*8);
	for(vu8 i = 0; i < 8; ++i){
		allDurations[i] = 0.1f;
	}
	
	_characters[0] = new CSpriteAnimated("sprite/charSelector/ayaSelected", "sprite/charSelector/ayaSelected", 32,64,8);
	_characters[0]->setDurationPerFrame(allDurations);
	_characters[1] = new CSpriteAnimated("sprite/charSelector/sakuyaSelected", "sprite/charSelector/sakuyaSelected", 32,64,6);
	_characters[1]->setDurationPerFrame(allDurations);
	_characters[2] = new CSpriteAnimated("sprite/charSelector/hongSelected", "sprite/charSelector/hongSelected", 32,64,6);
	_characters[2]->setDurationPerFrame(allDurations);
	_characters[3] = new CSpriteAnimated("sprite/charSelector/tenshiSelected", "sprite/charSelector/tenshiSelected", 64,64,8);
	_characters[3]->setDurationPerFrame(allDurations);
	

	// background
	_topBackground = new CBackground("bg/charSelector/back_blue",256,256);
	_topBackground->CreateBackground(true);
	
	if(!CEngine::DEBUG){
		_botBackground = new CBackground("bg/charSelector/back_red",256,256);
		_botBackground->CreateBackground(false);
	}
	


	_character1 = NULL;
	_character2 = NULL;
	// debug
	_allSelected = true;
}

void CCharacterSelector::selectCharacter(u8 idCharacter){
	if(_engine->getGameData()->character1 < 100)
		_characterButtons[_engine->getGameData()->character1]->setSelected(false);

	_engine->getGameData()->character1 = idCharacter;
	_characterButtons[idCharacter]->setSelected(true);

	_allSelected = _engine->getGameData()->level < 100;


	if(_character1 != NULL){
		_character1->removeFromScreen();
		_character1->removeFromVRam();
	}

	_character1 = _characters[idCharacter];
	_character1->MoveSpriteToVRam(true, true);
	Vector2 *position = new Vector2(32,192-80);
	_character1->CreateSprite(position);
} // selectCharacter

void CCharacterSelector::selectScenario(u8 idScenario){
	if(_engine->getGameData()->level < 100)
		_scenarioButtons[_engine->getGameData()->level]->setSelected(false);
	_engine->getGameData()->level = idScenario;
	_scenarioButtons[idScenario]->setSelected(true);

	_allSelected = _engine->getGameData()->character1 < 100;
}

// Mueve las bolas
void CCharacterSelector::Update(vfloat32 time){
	
	
	if(_backButton->IsTouched()) {
		_engine->ChangeScene(CEngine::MENU);

	}else if(_startButton->IsTouched()) {
		if(_allSelected)
			_engine->ChangeScene(CEngine::ARCADE_BATTLE);
	}else{
		for(vu8 i = 0; i < 4; ++i){
			if(_characterButtons[i]->IsTouched())
				selectCharacter(i);
		}

		for(vu8 i = 0; i < 4; ++i){
			if(_scenarioButtons[i]->IsTouched())
				selectScenario(i);
		}
	}

	if(_character1 != NULL){
		_character1->UpdateAnimation(time);
	}

} // Update
