#ifndef __CHARACTER_H__
#define __CHARACTER_H__




/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/



// Includes propietarios NDS
#include <nds.h>


// Defines
class CMovement;
class CSpriteAnimated;
class Vector2;

// Clase CCharacter
class CCharacter {

	public:
		
		// Contructores
		CCharacter(const char *character, Vector2 *position);
		
		// Destructor
		~CCharacter(void);
		
		void Init(void);
				
		// update
		void UpdateCharacter(vfloat32 time);

		// gets & sets
		

	private:
		// basic
		char* _name;
		u16 _health;
		Vector2* _position;

		// graphics
		CSpriteAnimated* _standPos;

		// movemnts
		CMovement *_currentMovement;
		CMovement *_movementList;
	
};



#endif
