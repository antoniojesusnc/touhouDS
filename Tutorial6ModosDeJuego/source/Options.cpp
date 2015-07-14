



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
#include "Options.h"
#include "Background.h"
#include "Sprite.h"
#include "Text.h"
#include "Button.h"
#include "Inputs.h"

#include "Debug.h"

/*
	Metodos de la clase "COptions"
*/


// Contructor clase COptions
COptions::COptions(CEngine* engine):CScene(engine) {
	_engine = engine;
	
	_topBackground = NULL;
	_botBackground = NULL;
} // COptions

// Destructor clase COptions
COptions::~COptions(void) {
	/*

	delete _buttons[0];
	delete _topBackground;

	/*/
	

	delete _backButton;

	delete _brightnessButton;

	delete _30SecondButton;
	delete _60SecondButton;
	delete _90SecondButton;		
	
	/* */
		
	


	
	

} // ~COptions

/*
	Metodos de la clase "COptions"
*/

void COptions::InitScene(){

	// backgrounds
	// top background
	

	
	
	
	Vector2 *position = new Vector2(0,0);
	_backButton	= new CButton("sprite/bola", 32, 32, position);
	
	position->setXY(255-32,0);
	_brightnessButton	= new CButton("sprite/bola", 32, 32, position);

	position->setXY(60,80);
	_30SecondButton	= new CButton("sprite/bola", 32, 32, position);
	position->setXY(110,80);
	_60SecondButton	= new CButton("sprite/bola", 32, 32, position);
	position->setXY(160,80);
	_90SecondButton	= new CButton("sprite/bola", 32, 32, position);

	free(position);
	
	//delete position;
	_topBackground = new CBackground("bg/nfl",256,256);
	_topBackground->CreateBackground(true);
	
	
	_botBackground = new CBackground("bg/background01",256,256);
	_botBackground->CreateBackground(false);
	
	
}

// Mueve las bolas
void COptions::Update(vfloat32 time){
	
	
	if(_backButton->IsTouched()) {
		_engine->ChangeScene(CEngine::MENU);

	}else if(_brightnessButton->IsTouched()) {

		
		/*
		u8 var = readPowerManagement((4)) - 64;
		var = ( ((var+1)<=4)?var+1:0 );
		
		writePowerManagement((4),var );
		*/
		

	}else if(_30SecondButton->IsTouched()) {
		_engine->getGameData()->time = 30;

	}else if(_60SecondButton->IsTouched()) {
		_engine->getGameData()->time = 60;
		
	}else if(_90SecondButton->IsTouched()) {
		_engine->getGameData()->time = 90;
	}
} // Update
