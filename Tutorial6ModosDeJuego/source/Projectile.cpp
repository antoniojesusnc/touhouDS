

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
#include "Projectile.h"
#include "Inputs.h"
#include "Movement.h"
#include "SpriteAnimated.h"
#include "Palette.h"
#include "Math.h"
#include "XMLParser.h"

#include "Debug.h"

// static variables
/*
	Metodos de la clase "CProjectile"
*/

// Contructor clase CProjectile
CProjectile::CProjectile(CSpriteAnimated *sprite, float speedX, float speedY) {
	_sprite = new CSpriteAnimated(*sprite);
	_speedX = speedX;
	_speedY = speedY;

	_position = new Vector2();
} // CProjectile

// Destructor clase CProjectile
CProjectile::~CProjectile(void) {

} // ~CProjectile

/*
	Metodos de la clase "CProjectile"
*/

void CProjectile::Start(Vector2 *position, CSpriteAnimated *sprite) {
	
	
	_enable  = true;

	_sprite->setInVRam(sprite->isInVRam());
	_sprite->setIdVRam(sprite->getIdVRam());
	_sprite->setUpScreen(sprite->isUpScreen());

	//printf("\nID %d %d \nIDV %d %d",sprite->getIdRam(),_sprite->getIdRam(),sprite->getIdVRam(),_sprite->getIdVRam() );

	//printf("\n %d %d %d", _sprite->getPalette()->getIdRam(), _sprite->getPalette()->getIdVRam(),_sprite->isInVRam() );
	//printf("\n %s ", _sprite->getName() );
	_position->setXY(position->getX(), position->getY());
	_sprite->CreateSprite(position);
	
	_acumX = 0;
	_acumY = 0;
} // Start


void CProjectile::UpdateProjectile(vfloat32 time) {
	if(!_enable)
		return;

	_acumX += time;
	_acumY += time;

	//printf("\n %f %f",_acumX, _speedX);
	if(_speedX > 0){
		while(_acumX >= _speedX){
			_acumX -= _speedX;
			_position->setX(_position->getX()+1);
		}
	}
	if(_speedX < 0){
		while(-_acumX <= _speedX){
			_acumX += _speedX;
			_position->setX(_position->getX()-1);
		}
	}

	if(_speedY > 0){
		while(_acumY >= _speedY){
			_acumY -= _speedY;
			_position->setY(_position->getY()+1);
		}
	}
	if(_speedY < 0){
		while(-_acumY <= _speedY){
			_acumY += _speedY;
			_position->setY(_position->getY()-1);
		}
	}

	//_position->setX(_position->getX()+_speed->getX());
	//_position->setY(_position->getY()+_speed->getY());
	_sprite->MoveSpriteToPos(_position);

	_sprite->UpdateAnimation(time);
} // UpdateProjectile

void CProjectile::Finish() {

	if(_enable){
		_enable = false;
		_sprite->removeFromScreen();
	}


} // Finish