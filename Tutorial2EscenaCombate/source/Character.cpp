

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
#include "Character.h"
#include "SpriteAnimated.h"

// static variables
/*
	Metodos de la clase "CCharacter"
*/

// Contructor clase CCharacter
CCharacter::CCharacter(const char *character, Vector2 *position) {
	strcpy(_name, character);

	_health = 100;
	_position = new Vector2(*position);

	//_standPos = new CSpriteAnimated("sprite/characters/sakuya/sakuya1","sprite/characters/sakuya/original",32,64, 1);
	//_standPos = new CSpriteAnimated("sprite/bola","sprite/bola",32,32, 2);
	
	
	//_standPos = new CSpriteAnimated("sprite/characters/sakuya/bola","sprite/characters/sakuya/bola",32,32, 2);

	//_standPos = new CSpriteAnimated("sprite/characters/sakuya/sakuya1","sprite/characters/sakuya/original",32,64, 6);
	_standPos = new CSpriteAnimated("sprite/characters/sakuya/personaje","sprite/characters/sakuya/personaje",64,64,12);

} // CCharacter

// Destructor clase CCharacter
CCharacter::~CCharacter(void) {

} // ~CCharacter

/*
	Metodos de la clase "CCharacter"
*/

void CCharacter::Init(void) {
	_standPos->MoveSpriteToVRam(true,true);
	_standPos->CreateSprite(_position);
} // Init

void CCharacter::UpdateCharacter(vfloat32 time) {
	_standPos->UpdateAnimation(time);
} // UpdateCharacter