



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
#include "Text.h"
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

	// backgrounds
	// top background
	

	
	
	
	Vector2 *position = new Vector2(0,0);
	_backButton	= new CButton("sprite/bola", 32, 32, position);
	position->setXY(255-32,0);
	_startButton = new CButton("sprite/bola", 32, 32, position);


	position->setXY(64,80);
	_characterButtons[0] = new CButton("sprite/bola", 32, 32, position);
	position->setXY(96,80);
	_characterButtons[1]	= new CButton("sprite/bola", 32 , 32, position);
	position->setXY(128,80);
	_characterButtons[2] = new CButton("sprite/bola", 32, 32, position);
	position->setXY(160,80);
	_characterButtons[3] = new CButton("sprite/bola", 32, 32, position);

	position->setXY(0,150);
	_scenarioButtons[0] = new CButton("sprite/bola", 32, 32, position);
	position->setXY(64,150);
	_scenarioButtons[1] = new CButton("sprite/bola", 32 , 32, position);
	position->setXY(128,150);
	_scenarioButtons[2] = new CButton("sprite/bola", 32, 32, position);
	position->setXY(192,150);
	_scenarioButtons[3] = new CButton("sprite/bola", 32, 32, position);

	free(position);
	
	//delete position;
	_topBackground = new CBackground("bg/nfl",256,256);
	_topBackground->CreateBackground(true);
	
	_botBackground = new CBackground("bg/background01",256,256);
	_botBackground->CreateBackground(false);


	_character1 = NULL;
	_character2 = NULL;
	// debug
	_allSelected = true;
}

void CCharacterSelector::selectCharacter(u8 idCharacter){

}

void CCharacterSelector::selectScenario(u8 idScenario){

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

} // Update
