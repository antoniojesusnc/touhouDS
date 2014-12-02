



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
#include "Input.h"

#include "Debug.h"

/*
	Metodos de la clase "CMenu"
*/


// Contructor clase CMenu
CMenu::CMenu(CEngine* engine) {
	_engine = engine;
	
} // CMenu

// Destructor clase CMenu
CMenu::~CMenu(void) {
	/*
	delete [] _buttons;
	/*/
	for(_indexBucle = 0; _indexBucle < 4; ++_indexBucle){
		delete _buttons[_indexBucle];
	}
	/* */
	delete _topBackground;
	delete _botBackground;
	delete _genericSprite;
	delete _genericText;
} // ~CMenu

/*
	Metodos de la clase "CMenu"
*/

void CMenu::InitMenu(){

	// backgrounds
	// top background
	_topBackground = new CBackground("bg/nfl",256,256);
	_topBackground->CreateBackground(true);

	// bot background
	//CBackground *backgroundBot = new CBackground("bg/nfl",256,256);
	//backgroundBot->CreateBackground(false);
	
	
	_genericSprite = new CSprite("sprite/bola", "sprite/bola", 32, 32);	
	_genericSprite->MoveSpriteToVRam(true,true);
	

	Vector2 position = Vector2(50,40);
	//NF_Error(2,"a %d a",4);
	_genericSprite->CreateSprite(&position);
	
	_buttons[0]	= new CButton(_genericSprite,_genericSprite,&position);

	position.x = 170;
	_buttons[1]	= new CButton(_genericSprite,_genericSprite,&position);

	
	position.x = 50;
	position.y = 120;
	_buttons[2]	= new CButton(_genericSprite,_genericSprite,&position);

	position.x = 170;
	position.y = 120;
	_buttons[3]	= new CButton(_genericSprite,_genericSprite,&position);
	
}

// Mueve*/as bolas
void CMenu::Update(){
	
	CDebug::getInstance()->WriteText("  cc            ");
	
	for(_indexBucle = 0; _indexBucle < 4; ++_indexBucle){
		
		if(_buttons[_indexBucle]->IsTouched()) {
			CDebug::getInstance()->WriteText("a ver: ", _indexBucle);
			_engine->ChangeScene(CEngine::MENU);
			return;
		}
	} 
	

} // Update
