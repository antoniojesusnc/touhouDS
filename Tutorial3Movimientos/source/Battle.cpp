



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

#include "Character.h"
#include "Debug.h"


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
	delete _time;

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
	
	
	_topBackground = new CBackground("bg/nfl",256,256);
	_topBackground->CreateBackground(true);
	
	// bot background
	//CBackground *backgroundBot = new CBackground("bg/n256,256);
	//backgroundBot->CreateBackground(false);	
	
	Vector2 *pos = new Vector2(192-64,255*0.5f);
	_characters[0] = new CCharacter("sakuya" );
	_characters[0]->Init(pos);
	//delete pos;

	
}

// Mueve las bolas
void CBattle::Update(vfloat32 time){	
	_characters[0]->UpdateCharacter(time);
} // Update
