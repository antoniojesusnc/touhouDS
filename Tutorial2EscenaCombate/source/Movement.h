#ifndef __MOVEMENT_H__
#define __MOVEMENT_H__




/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/



// Includes propietarios NDS
#include <nds.h>

#include "Inputs.h"

// Defines
class Vector2;
class CSpriteAnimated;
class CCharacter;

// Clase CMovement
class CMovement {

	public:
		
		// Contructores
		CMovement();
		
		// Destructor
		~CMovement(void);
		
		void Init(const char *movement, CCharacter *_owner);

		// startMovement
		void StartMovement(Vector2* position);
		
		// cancel
		void CancelMovement();
		

		// update
		void UpdateMovement(vfloat32 time);

		
		// gets & sets

		char *getName(){return _name;}

		void setDamage(u8 damage){_damage = damage;}
		void setDuration(u8 duration){_duration = duration;}
		void setActivated(bool activated){_activated = activated;}
		
		bool isActivated(){ return _activated;}
		bool canBeBlock(){ return _canBeBlock;}
		// operators

		
		inline bool operator==(const CMovement& m) {
			return strcmp(_name, m._name) == 0;
			//return false;
		} // operator ==

		inline bool operator!=(const CMovement& m){
			return !(*this == m);
		} // operator ==
	
	private:
		
		CCharacter *_owner;
		Vector2 *_characterPosition;

		CInputs::Direction _direction;
		CInputs::Commands _command;

		char *_name;
		u8 _damage;
		u8 _duration;
		u8 _currentDuration;
		Vector2 *_position;
		CSpriteAnimated *_sprite;		
		Vector2 *_offsetPerFrame;

		bool _canBeBlock;
		bool _activated;
		bool _loopeable;
		CInputs::Direction _lookDirection;
};



#endif
