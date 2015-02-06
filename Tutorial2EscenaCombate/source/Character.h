#ifndef __CHARACTER_H__
#define __CHARACTER_H__




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

		// other methods
		void changeLookDirection();

		// gets & sets
		Vector2* getPosition(){return _position;}
		bool isLookingRight(){return _lookingFor == CInputs::Right;}

	private:

		void checkMovement();

		//bool checkAndChangeIfDiferent(CMovement *m);
		bool checkAndChangeIfDiferent(u8 newIndex);

		// characteristics
		char* _name;
		u16 _health;
		Vector2 *_horizontalSpeed;

		// graphics
		Vector2* _position;
		CSpriteAnimated* _standPos;

		// movemnts
		//CMovement *_currentMovement;
		
		CMovement *_movementList;
		u8 _indexMovement;
		CInputs::Direction _lookingFor;

		CInputs *_input;
	
};



#endif
