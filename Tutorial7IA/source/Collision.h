#ifndef __COLLISION_H__
#define __COLLISION_H__





/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/


// Includes propietarios NDS
#include <nds.h>
#include "Math.h"
#include "Engine.h"


// Defines
class CCharacter;
class CMovement;
class CProjectileMovement;

// Clase CCollision
class CCollision {

	public:
				
		// Contructores
		CCollision();
		
		// Destructor
		~CCollision(void);

		void CheckCollision(CCharacter *defender, CCharacter *attacker);

	private:

		void checkCollisionBetweenProjectile(CProjectileMovement **projectilesDef, CProjectileMovement **projectilesAttk, u8 maxElements);

		void checkCollisionProjectile(CCharacter *defender, CProjectileMovement **projectiles, u8 maxElements);

		bool checkCollisionBetweenAttacks(CCharacter *defender, CCharacter *attacker);
		bool checkCollisionBody(CCharacter *defender, CCharacter* attacker);


		Rect *_rect1;
		Rect *_rect2;
		u8 _num1; 
		u8 _num2;


};

#endif
