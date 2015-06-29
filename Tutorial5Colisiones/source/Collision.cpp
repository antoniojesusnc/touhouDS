



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
#include "Collision.h"

#include "Character.h"
#include "Movement.h"
#include "ProjectileMovement.h"
#include "Math.h"


/*

	Metodos de la clase "CCollision"
*/


// Contructor clase CCollision
CCollision::CCollision() {
	_rect1 = new Rect();
	_rect2 = new Rect();
} // CCollision

// Destructor clase CCollision
CCollision::~CCollision(void) {


} // ~CCollision

/*
	Metodos de la clase "CCollision"
*/

void CCollision::CheckCollision(CCharacter *defender, CCharacter *attacker){

	if(defender->hasProjectileActive() && attacker->hasProjectileActive()){
		checkCollisionBetweenProjectile(defender->getActiveProjectileMovements(), 
										attacker->getActiveProjectileMovements(),
										attacker->getMaxActiveMovement());
	}

	
	if(attacker->hasProjectileActive()){
		checkCollisionProjectile(defender,attacker->getActiveProjectileMovements(), attacker->getMaxActiveMovement());
	}

	if(!checkCollisionBetweenAttacks(defender, attacker)){
		if(checkCollisionBody(defender, attacker)){
			printf(" hitBody ");
		}
	}else{
		printf(" hitAttack ");
	}

	
	


} // CheckCollision

void CCollision::checkCollisionBetweenProjectile(CProjectileMovement **projectilesDef, CProjectileMovement **projectilesAttk, u8 maxElements){
	

	for(vu8 i = 0; i < maxElements; ++i){
		if(projectilesDef[i]->getCurrentHitBox() == NULL)
				continue;
		for(vu8 j = 0; j < maxElements; ++j){
			if(projectilesAttk[j]->getCurrentHitBox() == NULL)
				continue;

			_rect1->setWidth(projectilesDef[i]->getCurrentHitBox()->getWidth());
			_rect1->setHeight(projectilesDef[i]->getCurrentHitBox()->getHeight());

			_num1 = projectilesDef[i]->getNumProjectiles();

			if(projectilesDef[i] != NULL && projectilesAttk[i] != NULL){
			
				_num2 = projectilesAttk[i]->getNumProjectiles();
			
				_rect2->setWidth(projectilesAttk[j]->getCurrentHitBox()->getWidth());
				_rect2->setHeight(projectilesAttk[j]->getCurrentHitBox()->getHeight());

				for(vu8 p1 = 0; p1 < _num1; ++p1){
					for(vu8 p2 = 0; p2 < _num2; ++p2){
						if(	projectilesDef[i]->getProjectiles()[p1]->isEnable() &&
							projectilesAttk[j]->getProjectiles()[p1]->isEnable() ){
						
								_rect1->setX(projectilesDef[i]->getCurrentHitBox()->getX() + projectilesDef[i]->getProjectiles()[p1]->getPosition()->getX());
								_rect1->setY(projectilesDef[i]->getCurrentHitBox()->getY() + projectilesDef[i]->getProjectiles()[p1]->getPosition()->getY());

								_rect2->setX(projectilesAttk[j]->getCurrentHitBox()->getX() + projectilesAttk[j]->getProjectiles()[p2]->getPosition()->getX());
								_rect2->setY(projectilesAttk[j]->getCurrentHitBox()->getY() + projectilesAttk[j]->getProjectiles()[p2]->getPosition()->getY());

								if(_rect1->collisionBetweenRect(_rect2)){
									projectilesDef[i]->getProjectiles()[p1]->Finish();
									projectilesAttk[j]->getProjectiles()[p2]->Finish();
								}
						} // if bot enable
					}
				}
			} // if have proyectiles
		}
	}
	
}

void CCollision::checkCollisionProjectile(CCharacter *defender, CProjectileMovement **projectiles, u8 maxElements){
	_rect1->setX(defender->getBody()->getX() + defender->getPosition()->getX());
	_rect1->setY(defender->getBody()->getX() + defender->getPosition()->getY());
	_rect1->setWidth(defender->getBody()->getWidth());
	_rect1->setHeight(defender->getBody()->getHeight());


	for(vu8 i = 0; i < maxElements; ++i){
		if(projectiles[i]->getCurrentHitBox() == NULL)
			continue;

		_rect2->setWidth(projectiles[i]->getCurrentHitBox()->getWidth());
		_rect2->setHeight(projectiles[i]->getCurrentHitBox()->getHeight());

		_num1 = projectiles[i]->getNumProjectiles();

		
		for(vu8 p1 = 0; p1 < _num1; ++p1){
			if(	projectiles[i]->getProjectiles()[p1]->isEnable() ){
				_rect2->setX(projectiles[i]->getCurrentHitBox()->getX() + projectiles[i]->getProjectiles()[p1]->getPosition()->getX());
				_rect2->setY(projectiles[i]->getCurrentHitBox()->getY() + projectiles[i]->getProjectiles()[p1]->getPosition()->getY());

				//printf("\n1 X:%d Y:%d W: %d H: %d",_rect1->getX(),_rect1->getY(),_rect1->getWidth(),_rect1->getHeight());
				//printf("\n2 X:%d Y:%d W: %d H: %d",_rect2->getX(),_rect2->getY(),_rect2->getWidth(),_rect2->getHeight());
				if(_rect1->collisionBetweenRect(_rect2)){
					projectiles[i]->getProjectiles()[p1]->Finish();
					defender->TakeHitPoints(projectiles[i]->getCurrentDamage());
					//NF_Error(1,"a",12);
					printf(" hit ");
				}
			}
		}
	}
} // checkCollisionProjectile

bool CCollision::checkCollisionBetweenAttacks(CCharacter *defender, CCharacter *attacker){

	if(defender->getCurrentMovement()->getCurrentHitBox() == NULL)
		return false;

	_rect1->setX(defender->getCurrentMovement()->getCurrentHitBox()->getX() + defender->getPosition()->getX());
	_rect1->setY(defender->getCurrentMovement()->getCurrentHitBox()->getY() + defender->getPosition()->getY());
	_rect1->setWidth(defender->getCurrentMovement()->getCurrentHitBox()->getWidth() );
	_rect1->setHeight(defender->getCurrentMovement()->getCurrentHitBox()->getHeight() );

	_rect2->setX(attacker->getCurrentMovement()->getCurrentHitBox()->getX() + attacker->getPosition()->getX());
	_rect2->setY(attacker->getCurrentMovement()->getCurrentHitBox()->getY() + attacker->getPosition()->getY());
	_rect2->setWidth(attacker->getCurrentMovement()->getCurrentHitBox()->getWidth() );
	_rect2->setHeight(attacker->getCurrentMovement()->getCurrentHitBox()->getHeight() );

	if(_rect1->collisionBetweenRect(_rect2)){
		if(attacker->getCurrentMovement()->getcurrentPriority() > defender->getCurrentMovement()->getcurrentPriority()){
			defender->TakeHitPoints( attacker->getCurrentMovement()->getCurrentDamage() );
			return true;
		}
	}
	return false;
} // checkCollisionBetweenAttacks

bool CCollision::checkCollisionBody(CCharacter *defender, CCharacter* attacker){

	if(attacker->getCurrentMovement()->getCurrentHitBox() == NULL){
		//printf("\n asd");
		return false;
	}

	_rect1->setX(defender->getBody()->getX() + defender->getPosition()->getX());
	_rect1->setY(defender->getBody()->getY() + defender->getPosition()->getY());
	_rect1->setWidth(defender->getBody()->getWidth() );
	_rect1->setHeight(defender->getBody()->getHeight() );

	_rect2->setX(attacker->getCurrentMovement()->getCurrentHitBox()->getX() + attacker->getPosition()->getX());
	_rect2->setY(attacker->getCurrentMovement()->getCurrentHitBox()->getY() + attacker->getPosition()->getY());
	_rect2->setWidth(attacker->getCurrentMovement()->getCurrentHitBox()->getWidth() );
	_rect2->setHeight(attacker->getCurrentMovement()->getCurrentHitBox()->getHeight() );

	if(_rect1->collisionBetweenRect(_rect2)){
		defender->TakeHitPoints( attacker->getCurrentMovement()->getCurrentDamage() );
		return true;
	}
	
	return false;
} // checkCollisionBody
