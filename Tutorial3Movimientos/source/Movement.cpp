

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
#include "Math.h"
#include "Movement.h"
#include "Character.h"
#include "SpriteAnimated.h"

// static variables
/*
	Metodos de la clase "CMovement"
*/

CMovement *Movement;

// Contructor clase CMovement
CMovement::CMovement() {
	
	_activated = false;

	
} // CMovement

// Destructor clase CMovement
CMovement::~CMovement(void) {
} // ~CMovement

/*
	Metodos de la clase "CMovement"
*/

void CMovement::Init(CXMLParser::TXML* movement, CCharacter *owner) {

	/*
	strcpy(_name, movement);
	_owner = owner;
	_characterPosition = owner->getPosition();
	
	
	if(strcmp(movement,"0") == 0){
		
		_sprite = new CSpriteAnimated("sprite/characters/sakuya/sakuya3","sprite/characters/sakuya/sakuya",32,64,6);

		_currentDuration = 0;
		_loopeable = true;
		_canBeBlock = true;
		_offsetPerFrame = new Vector2[_sprite->getMaxFrame()];
		_lookDirection = CInputs::Right;
	}

	if(strcmp(movement,"1") == 0){
		strcpy(_name, movement);
		_sprite = new CSpriteAnimated("sprite/characters/sakuya/sakuya2","sprite/characters/sakuya/sakuya",32,64,9);

		_currentDuration = 0;
		_loopeable = true;
		_canBeBlock = true;
		_offsetPerFrame = new Vector2[_sprite->getMaxFrame()];
		_lookDirection = CInputs::Right;
	}

	if(strcmp(movement,"2") == 0){
		strcpy(_name, movement);
		_sprite = new CSpriteAnimated("sprite/characters/sakuya/sakuya1","sprite/characters/sakuya/sakuya",32,64,9);

		_currentDuration = 0;
		_loopeable = true;
		_canBeBlock = true;
		_offsetPerFrame = new Vector2[_sprite->getMaxFrame()];
		_lookDirection = CInputs::Left;
	}
	*/
	/*
	strcpy(_name, movement);	

	_sprite = new CSpriteAnimated("sprite/characters/sakuya/personaje","sprite/characters/sakuya/personaje",64,64,12);

	_activated = true;
	_currentDuration = 0;
	_loopeable = true;
	_canBeBlock = true;
	_offsetPerFrame = new Vector2[_sprite->getMaxFrame()];
	*/
	
	
} // Init

void CMovement::StartMovement() {

	_activated = true;
	
	_position = new Vector2(*_characterPosition);
	//_position = _position + *position;

	_sprite->MoveSpriteToVRam(true,true);
	_sprite->CreateSprite(_characterPosition);
	_sprite->FlipTo(_lookDirection);
	//_sprite->CreateSprite( _offsetPerFrame[0] + _characterPosition);

} // StartMovement

void CMovement::CancelMovement() {
	_activated = false;
	delete _position;
	_position = NULL;

	_sprite->removeFromScreen();
	_sprite->removeFromVRam();

} // CancelMovement

void CMovement::UpdateMovement(vfloat32 time) {
	if(!isActivated())
		return;
	
	_sprite->UpdateAnimation(time);
	
	_sprite->MoveSpriteToPos(_characterPosition);
	//_sprite->MoveSpriteToPos(_offsetPerFrame[_sprite->getFrame()] + _characterPosition);
	_currentDuration += time;

	
	if(!_loopeable && _currentDuration >= _duration){
		if(_loopeable){
			_currentDuration = 0;
		}else{
			setActivated(false);
		}
	}
} // UpdateMovement