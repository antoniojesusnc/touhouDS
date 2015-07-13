



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
CMenu::CMenu(CEngine* engine) {
	_engine = engine;
	
	_topBackground = NULL;
	_botBackground = NULL;
} // CMenu

// Destructor clase CMenu
CMenu::~CMenu(void) {
	/*

	delete _buttons[0];
	delete _topBackground;

	/*/
	

	for(_indexBucle = 0; _indexBucle < 4; ++_indexBucle){
		
		delete _buttons[_indexBucle];
		
	}
	delete _topBackground;
	delete _botBackground;
	/* */
		
	


	
	

} // ~CMenu

/*
	Metodos de la clase "CMenu"
*/

void CMenu::InitMenu(){

	// backgrounds
	// top background
	

	
	
	
	Vector2 *position = new Vector2(50,40);
	
	_buttons[0]	= new CButton("sprite/bola", 32, 32, position);
	
	position->setX(170);
	_buttons[1]	= new CButton("sprite/bola", 32, 32, position);
	
	position->setX(50);
	position->setY(120);
	_buttons[2]	= new CButton("sprite/bola", 32, 32, position);

	position->setX(170);
	position->setY(120);
	_buttons[3]	= new CButton("sprite/bola", 32, 32, position);
	
	free(position);
	
	//delete position;
	
	
	_topBackground = new CBackground("bg/nfl",256,256);
	_topBackground->CreateBackground(true);
	
	
	_botBackground = new CBackground("bg/background01",256,256);
	_botBackground->CreateBackground(false);
	
	
}

// Mueve las bolas
void CMenu::Update(vfloat32 time){
	
	
	if(_buttons[0]->IsTouched()) {
		
		//_engine->ChangeScene(CEngine::MENU);
		_engine->ChangeScene(CEngine::ARCADE);
	}
	
	

} // Update
