



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
#include "Menu.h"
#include "Background.h"
#include "Sprite.h"
#include "Text.h"
#include "Button.h"
#include "Inputs.h"

#include "Debug.h"

/*
	Metodos de la clase "CMenu"
*/


// Contructor clase CMenu
CMenu::CMenu(CEngine* engine):CScene(engine) {
	
} // CMenu

// Destructor clase CMenu
CMenu::~CMenu(void) {
	/*

	delete _buttons[0];
	delete _topBackground;

	/*/
	
	delete _logo01;
	delete _logo02;

	for(_indexBucle = 0; _indexBucle < 4; ++_indexBucle){
		
		delete _buttons[_indexBucle];
		
	}
	//delete _buttons;
	/* */
		
	


	
	

} // ~CMenu

/*
	Metodos de la clase "CMenu"
*/

void CMenu::InitScene(){

	Vector2 *position = new Vector2(0,0);

	// logo
	position->setXY(64,64);
	_logo01 = new CSprite("sprite/menu/MainLogo01", "sprite/menu/MainLogo01",64,64);
	_logo01->MoveSpriteToVRam(true, true);
	_logo01->CreateSprite(position);
	
	position->setX(128);
	_logo02 = new CSprite("sprite/menu/MainLogo02", "sprite/menu/MainLogo02",64,64);
	_logo02->MoveSpriteToVRam(true, true);
	_logo02->CreateSprite(position);


	// buttons
	position->setXY(64,70);
	_buttons[0]	= new CButton("sprite/menu/ArcadeText", 64, 32, position);
	
	position->setX(128);
	_buttons[1]	= new CButton("sprite/menu/StoryText", 64, 32, position);
	
	position->setX(64);
	position->setY(120);
	_buttons[2]	= new CButton("sprite/menu/ConfigText", 64, 32, position);

	position->setX(128);
	position->setY(120);
	_buttons[3]	= new CButton("sprite/menu/VSPlayerText", 64, 32, position);
	
	free(position);
	
	//delete position;
	
	
	_topBackground = new CBackground("bg/menu/menuTopBG",256,256);
	_topBackground->CreateBackground(true);
	
	if(!CEngine::DEBUG){
		_botBackground = new CBackground("bg/menu/menuBotBG",256,256);
		_botBackground->CreateBackground(false);
	}
	
	
	
}

// Mueve las bolas
void CMenu::Update(vfloat32 time){
	
	
	if(_buttons[0]->IsTouched()) {
		
		//_engine->ChangeScene(CEngine::MENU);
		_engine->ChangeScene(CEngine::ARCADE_CHAR_SELECT);
	}

	if(_buttons[2]->IsTouched()) {
		
		//_engine->ChangeScene(CEngine::MENU);
		_engine->ChangeScene(CEngine::OPTION);
	}
	
	

} // Update
