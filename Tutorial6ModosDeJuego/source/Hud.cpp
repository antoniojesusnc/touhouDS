



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
#include "Inputs.h"
#include "Hud.h"
#include "Palette.h"
#include "SpriteAnimated.h"
#include "Button.h"
#include "Text.h"
#include "Character.h"

/*
	Metodos de la clase "CHud"
*/


// Contructor clase CHud
CHud::CHud() {
	
	_healthBarPlayer1 = NULL;
	_healthBarPlayer2 = NULL;
	_timeTems = NULL;
	_timeUnits = NULL;

	// Pause menu
	_pauseBackground = NULL;
	_pauseText = NULL;
	_pauseResumeButton = NULL;
	_pauseExitButton = NULL;

	// victory and Loose menu
	_victoryText = NULL;
	_looseText = NULL;

} // CHud

// Destructor clase CHud
CHud::~CHud(void) {

	delete _healthBarPlayer1;
	delete _healthBarPlayer2;
	delete _timeTems;
	delete _timeUnits;

	// Pause menu
	delete _pauseBackground;
	delete _pauseText;
	delete _pauseResumeButton;
	delete _pauseExitButton;

	// victory and Loose menu
	delete _victoryText;
	delete _looseText;

} // ~CHud

/*
	Metodos de la clase "CHud"
*/

void CHud::InitHud(CCharacter * player1, CCharacter * player2, u8 initialTime){

	CPalette * hudPalette = new CPalette("sprite/hud/hud");
	hudPalette->MovePaletteToVRam(false);
	
	Vector2 *positions = new Vector2();
	
	// loading health bar
	positions->setXY(5,5);
	_healthBarPlayer1 = new CSpriteAnimated("sprite/hud/healthBar0",64,32,10);
	_healthBarPlayer1->MoveSpriteToVRam(false,false,true);
	_healthBarPlayer1->setPalette(hudPalette);
	_healthBarPlayer1->CreateSprite(positions);

	positions->setXY(255-5-64,5);
	_healthBarPlayer2 = new CSpriteAnimated(*_healthBarPlayer1);
	_healthBarPlayer2->CreateSprite(positions);
	_healthBarPlayer2->FlipTo(CInputs::DirBack);
	

	
	// loading numbers
	positions->setXY(96,80);
	_timeTems = new CSpriteAnimated("sprite/hud/numbers",32,32,10);
	_timeTems->MoveSpriteToVRam(false,false,true);
	_timeTems->setPalette(hudPalette);
	_timeTems->CreateSprite(positions);

	positions->setXY(128,80);
	_timeUnits = new CSpriteAnimated(*_timeTems);
	_timeUnits->CreateSprite(positions);




	

	temp1 = 0;
	temp2 = 0;

	Update(player1, player2, initialTime);

	

	// victory and loose text
	_victoryText = NULL;
	_looseText = NULL;

	delete positions;
}

// Mueve las bolas
void CHud::Update(CCharacter * player1, CCharacter * player2, u8 time){
	
	u8 frame = 10 - (10 * player1->getHealth()) / (player1->getMaxHealth());
	_healthBarPlayer1->setFrame(frame);

	frame = 10 - (10 * player2->getHealth()) / (player2->getMaxHealth());
	_healthBarPlayer2->setFrame(frame);

	_timeTems->setFrame(time/10);
	_timeUnits->setFrame(time%10);

} // Update

void CHud::ShowPause(bool pause){
	if(pause){
		// pause menu
		// top elements
		Vector2 *positions = new Vector2();
		
		CPalette *pausePalleteTop = new CPalette("sprite/hud/hud");
		pausePalleteTop->MovePaletteToVRam(true);
	
		_pauseText = new CSpriteAnimated("sprite/hud/healthBar0",32,32,10);
		_pauseText->MoveSpriteToVRam(true,false,true);
		_pauseText->setPalette(pausePalleteTop);
		_pauseText->CreateSprite(positions);

		// bot elements
		CPalette *pausePalleteBot = new CPalette("sprite/hud/hud");
		pausePalleteBot->MovePaletteToVRam(false);

		positions->setXY(128,80);
		_pauseBackground = new CSpriteAnimated("sprite/hud/healthBar0",32,32,10);
		_pauseBackground->MoveSpriteToVRam(false,false,true);
		_pauseBackground->setPalette(pausePalleteBot);
		_pauseBackground->CreateSprite(positions);		
	
		_pauseResumeButton = new CButton("sprite/bola", 32, 32, positions);
		_pauseExitButton = new CButton("sprite/bola", 32, 32, positions);

		free(positions);
	}else{
		
		delete _pauseBackground;
		delete _pauseText;
		delete _pauseResumeButton;
		delete _pauseExitButton;
		_buttonPressed = 0;

		_pauseBackground = NULL;
		_pauseText = NULL;
		_pauseResumeButton = NULL;
		_pauseExitButton = NULL;
	}
} // ShowPause

void CHud::UpdatePause(){
	if(_pauseResumeButton->IsTouched()) {
		_buttonPressed = 1;
	}else if(_pauseExitButton->IsTouched()) {
		_buttonPressed = 2;
	}else{
		_buttonPressed = 0;
	}
} // UpdatePause
