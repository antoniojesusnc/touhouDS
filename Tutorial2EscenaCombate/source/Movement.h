#ifndef __MOVEMENT_H__
#define __MOVEMENT_H__




/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/



// Includes propietarios NDS
#include <nds.h>

#include "Input.h"

// Defines
class CSpriteAnimated;

// Clase CMovement
class CMovement {

	public:
		
		// Contructores
		CMovement(const char *movement);
		
		// Destructor
		~CMovement(void);
		
		void Init();

		// startMovement
		void StartMovement();
		
		// cancel
		void CancelMovement();
		
		// update
		void UpdateMovement(u16 time);

		// gets & sets
		bool isActivated(){ return _activated;}
		bool canBeBlock(){ return _canBeBlock;}

	private:
		
		u8 _damage;
		u8 _duration;
		u8 _currentDuration;

		CInput::Direction _direction;
		CInput::Inputs _input;

		CSpriteAnimated *_sprite;
		Vector2 *_offsetPerFrame;

		bool _canBeBlock;
		bool _activated;

	
};



#endif
