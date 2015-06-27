#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__




/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/



// Includes propietarios NDS
#include <nds.h>
#include "Inputs.h"

// Defines
class CMovement;
class CPalette;
class Vector2;
class CSpriteAnimated;

// Clase CProjectile
class CProjectile {

	public:
		
		// Contructores
		CProjectile(CSpriteAnimated *sprite, float speedX, float speedY);
		
		// Destructor
		~CProjectile(void);
		
		// start
		void Start(Vector2 *position, CSpriteAnimated *sprite);
		
		// update
		void UpdateProjectile(vfloat32 time);

		// finish
		void Finish();

		// other methods
		void ChangeLookDirection();

		// gets & sets
		Vector2* getPosition(){return _position;}

	private:

		// projectileistics
		float _speedX;
		float _speedY;

		CSpriteAnimated* _sprite;
		CPalette *_palette;
		Vector2* _position;

		float _acumX;
		float _acumY;

		// movemnts
		CInputs::Commands _lookingFor;
};



#endif
