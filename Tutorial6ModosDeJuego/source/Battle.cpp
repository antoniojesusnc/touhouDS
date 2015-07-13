



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
CBattle::CBattle(CEngine* engine) {
	_engine = engine;
	
	_topBackground = NULL;
	_botBackground = NULL;
} // CBattle

// Destructor clase CBattle
CBattle::~CBattle(void) {
	/*
	delete [] _buttons;
	/*/
	
	delete _topBackground;
	delete _botBackground;

	for(vu8 i = 0; i < 2; ++i){
		delete _characters[i];
	}
	

} // ~CBattle

/*
	Metodos de la clase "CBattle"
*/

void CBattle::InitBattle(){

	// backgrounds
	// top background
	
	
	
	
	
	// bot background
	//_botBackground = new CBackground("bg/bg3",256,256);
	/*_botBackground->CreateBackground(false);	
	*/
	
	Vector2 *pos = new Vector2(192-128,255*0.5f);
	
	_characters[0] = new CCharacter("sakuya", false);
	_characters[0]->Init(pos);
	
	pos->setX(pos->getX()+64);
	_characters[1] = new CCharacter("sakuya", true);
	_characters[1]->Init(pos);
	//delete pos;
	
	_collision = new CCollision();

	_hud = new CHud();
	_hud->InitHud(_characters[0], _characters[1], 60);

	_remainingTime = 60;
	_acum = 0;
	
	_topBackground = new CBackground("bg/background01",256,256);
	_topBackground->CreateBackground(true);
	
	//_topBackground->CreateBackground(false);
	
	
	_botBackground = new CBackground("bg/nfl",256,256);
	_botBackground->CreateBackground(false);
	
	
}

// Mueve las bolas
void CBattle::Update(vfloat32 time){
	
	
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
} // Update
