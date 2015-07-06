



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
#include "Text.h"
#include "Character.h"

/*
	Metodos de la clase "CHud"
*/


// Contructor clase CHud
CHud::CHud() {
	
} // CHud

// Destructor clase CHud
CHud::~CHud(void) {


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




	delete positions;

	temp1 = 0;
	temp2 = 0;

	Update(player1, player2, initialTime);
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
