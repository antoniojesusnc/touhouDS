

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
#include "Inputs.h"
#include "Movement.h"
#include "ProjectileMovement.h"
#include "Character.h"
#include "SpriteAnimated.h"
#include "Sprite.h"
#include "Projectile.h"

// static variables
/*
	Metodos de la clase "CProjectileMovement"
*/

CProjectileMovement *ProjectileMovement;

// Contructor clase CProjectileMovement
CProjectileMovement::CProjectileMovement() {
	
} // CProjectileMovement

// Destructor clase CProjectileMovement
CProjectileMovement::~CProjectileMovement(void) {
} // ~CProjectileMovement

/*
	Metodos de la clase "CProjectileMovement"
*/

void CProjectileMovement::Init(CXMLParser::TXML* projectileMovementData, CCharacter *owner, CPalette *palette) {
		
	CMovement::Init(projectileMovementData, owner, palette);

	_projectile = true;
	//_position = new Vector2(0,0);
	//_position->setXY(_characterPosition->getX(),_characterPosition->getY());
	
	_firstPosOffset = new Vector2();
	char *auxTag;
	for(vu8 i = 0; i < projectileMovementData->numChilds; ++i){
		auxTag = projectileMovementData->childs[i]->tag;
		
		if(strcmp(auxTag, "speedX") == 0){
			_speedX = atof(projectileMovementData->childs[i]->value);
		}else if(strcmp(auxTag, "speedY") == 0){
			_speedY = atof(projectileMovementData->childs[i]->value);
		}else if(strcmp(auxTag, "firstPositionX") == 0){
			_firstPosOffset->setX( atoi(projectileMovementData->childs[i]->value));
		}else if(strcmp(auxTag, "firstPositionY") == 0){
			_firstPosOffset->setY( atoi(projectileMovementData->childs[i]->value));
		}else if(strcmp(auxTag, "numProjectiles") == 0){
			_numProjectiles = atoi(projectileMovementData->childs[i]->value);
			//_totalDuration = atof(projectileMovementData->childs[i]->value);
		}else if(strcmp(auxTag, "dispersion") == 0){
			_dispersion = atof(projectileMovementData->childs[i]->value);
		}else if(strcmp(auxTag, "projMovementData") == 0){
			initFrames(projectileMovementData->childs[i]);
		} // end if

	} // end for
		
	_sprite->setDurationPerFrame(_durationPerFrame);
	
	initProjectiles();


} // Init

void CProjectileMovement::initFrames(CXMLParser::TXML* projectileMovementData) {
	
	_numFrames = projectileMovementData->numChilds;
	
	
	_durationPerFrame = (float*)malloc(sizeof(float)*_numFrames);	
	
	char* auxTagFrame;
	for(vu8 i = 0; i < _numFrames; ++i){
		for(vu8 k = 0; k < projectileMovementData->childs[k]->numChilds; ++k){
			auxTagFrame = projectileMovementData->childs[i]->childs[k]->tag;
			if(strcmp(auxTagFrame, "duration") == 0){
				_durationPerFrame[i] = atof(projectileMovementData->childs[i]->childs[k]->value);
			}
		}
	} // end for frames
} // initFrames

void CProjectileMovement::initProjectiles(){

	_projectiles = (CProjectile**)malloc(sizeof(CProjectile*)* _numProjectiles);
	CProjectile *temp;
	
	float newSpeedY = _speedY;
	int mod;
	bool pair = _numProjectiles % 2 == 0;
	for(vu8 i = 0; i < _numProjectiles; ++i){

		if(_numProjectiles != 1){
			if(pair){
				mod = (i % 2 == 0)?1:-1;
				newSpeedY = _speedY + mod*_dispersion*((i/2)+1);
				
			}else{
				mod = _numProjectiles/2 - i;
				newSpeedY = _speedY + mod*_dispersion;
			}

		}

		temp = new CProjectile(_sprite,_speedX, newSpeedY);
		_projectiles[i] = temp;
	} 
	
}

void CProjectileMovement::StartMovement() {
	/*
	if(_activated){
		CancelMovement();
	}
	*/

	//printf("\n Starting");\
	
	_activated = true;
	
	_currentDuration = 0;
	_frame = 0;


	Vector2 temp(_characterPosition->getX()+_firstPosOffset->getX(), _characterPosition->getY()+_firstPosOffset->getY());
	_sprite->MoveSpriteToVRam(true,true);
	//printf("\n %s",_name);
	for(vu8 i = 0; i < _numProjectiles; ++i){
		_projectiles[i]->Start(&temp, _sprite);
	} 

} // StartProjectileMovement

void CProjectileMovement::FinishMovement() {
	//printf("\n FinishMovement");

	CMovement::FinishMovement();

	for(vu8 i = 0; i < _numProjectiles; ++i){
		_projectiles[i]->Finish();
	} 
	_sprite->removeFromVRam();
	
	
	//_sprite->removeFromScreen();
} // FinishMovement

void CProjectileMovement::CancelMovement() {
	//printf("\n cancel");
	
	FinishMovement();

	
	/*
	_activated = false;
	/*
	//delete _position;
	//_position = NULL;
	//*_characterPosition += *_offsetPerFrame[_frame];

	_sprite->removeFromScreen();
	_sprite->removeFromVRam();
	*/
} // CancelProjectileMovement

void CProjectileMovement::UpdateMovement(float time){
	updateTime(time);
	updateSprite(time);


} // UpdateMovement

void CProjectileMovement::updateSprite(vfloat32 time) {
	

	for(vu8 i = 0; i < _numProjectiles; ++i){
		_projectiles[i]->UpdateProjectile(time);
	}
	/*
	_sprite->UpdateAnimation(time);
	
	if(_frame != _sprite->getFrame()){
		_frame = _sprite->getFrame();

		//printf("\n 1 %d %d",_characterPosition->getX(), _characterPosition->getY());
		//printf("\n 2 %d %d %d",_frame, _offsetPerFrame[_frame]->getX(), _offsetPerFrame[_frame]->getY());
		*_characterPosition += *_offsetPerFrame[_frame];
		//printf("\n 3 %d %d",_characterPosition->getX(), _characterPosition->getY());
		_position->setXY(*_characterPosition);
		//printf("\n 4 %d %d",_characterPosition->getX(), _characterPosition->getY());

		

		*_position += *_positionPerFrame[_frame];

		_sprite->MoveSpriteToPos(_position);
	}
	*/
} // updateSprite