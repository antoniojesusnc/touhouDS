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
class CSprite;
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

		

		void setActivated(bool activated){_activated = activated;}

		char *getName(){return _name;}
		int getCommandIndex(){return (int)_command;}
		CSpriteAnimated* getSprite(){return _sprite;}

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

		CInputs::Commands _command;

		// character Pointers
		CCharacter *_owner;
		Vector2 *_characterPosition;

		// movement attributes
		char *_name;
		u8 _priority;
		float _totalDuration;
		bool _canBeBlock;
		bool _loopeable;
		u8 _numFrames;

		// attributes per frame
		float *_durationPerFrame;
		u8 *_damagePerFrame;
		Vector2 **_positionPerFrame;
		Vector2 **_offsetPerFrame;

		// othres
		float _currentDuration;
		Vector2 *_position;
		CSpriteAnimated *_sprite;		
		u8 _frame;

		bool _activated;
		CInputs::Direction _lookDirection;
};



#endif
