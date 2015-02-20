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
#include "XMLParser.h"

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
		
		void Init(CXMLParser::TXML* movementData, CCharacter *_owner);
		

		// startMovement
		void StartMovement();
		
		// cancel
		void CancelMovement();
		

		// update
		void UpdateMovement(vfloat32 time);

		
		// gets & sets

		char *getName(){return _name;}

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
		
		void initSprite(CXMLParser::TXML* spriteData);
		void initFrames(CXMLParser::TXML* frameData);

		// character Pointers
		CCharacter *_owner;
		Vector2 *_characterPosition;

		CInputs::Direction _direction;
		CInputs::Commands _command;

		// movement attributes
		char *_name;
		u8 _priority;
		u8 _totalDuration;
		bool _canBeBlock;
		bool _loopeable;

		// attributes per frame
		Vector2 *_offsetPerFrame;
		Vector2 *_positionPerFrame;
		Vector2 *_damagePerFrame;
		float *_durationPerFrame;


		u8 _currentDuration;
		Vector2 *_position;
		CSpriteAnimated *_sprite;		

		bool _activated;
		CInputs::Direction _lookDirection;
};



#endif
