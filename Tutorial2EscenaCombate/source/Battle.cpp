



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
#include "Input.h"

#include "Character.h"
#include "Debug.h"

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
	delete _time;

	delete[] _characters;
	

} // ~CBattle

/*
	Metodos de la clase "CBattle"
*/

void CBattle::InitBattle(){

	// backgrounds
	// top background
	

	_topBackground = new CBackground("bg/nfl",256,256);
	_topBackground->CreateBackground(false);
	
	// bot background
	//CBackground *backgroundBot = new CBackground("bg/n256,256);
	//backgroundBot->CreateBackground(false);	
	
	Vector2 *pos = new Vector2(192-64,255*0.5f);
	_characters[0] = new CCharacter("sakuya",pos );
	_characters[0]->Init();
	delete pos;

}

// Mueve las bolas
void CBattle::Update(vfloat32 time){	
	_characters[0]->UpdateCharacter(time);
} // Update
