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
class CPalette;

// Clase CMovement
class CMovement {

	public:
		
		// Contructores
		CMovement();
		
		// Destructor
		~CMovement(void);
		
		virtual void Init(CXMLParser::TXML* movementData, CCharacter *_owner, CPalette *palette);
		

		// startMovement
		virtual void StartMovement();
		
		// finish
		virtual void FinishMovement();

		// cancel
		virtual void CancelMovement();
		

		// update
		void UpdateMovement(vfloat32 time);

		
		// gets & sets

		

		void setActivated(bool activated){_activated = activated;}

		char *getName(){return _name;}
		int getCommandIndex(){return (int)_command;}
		CSpriteAnimated* getSprite(){return _sprite;}

		bool isActivated(){ return _activated;}
		bool canBeBlock(){ return _canBeBlock;}
		bool isProjectile(){return _projectile;}
		// operators

		
		inline bool operator==(const CMovement& m) {
			return strcmp(_name, m._name) == 0;
			//return false;
		} // operator ==

		inline bool operator!=(const CMovement& m){
			return !(*this == m);
		} // operator ==
	
	protected:
		
		virtual void initSprite(CXMLParser::TXML* spriteData, CPalette *palette);
		virtual void initFrames(CXMLParser::TXML* frameData);

		virtual void updateSprite(float time);
		virtual void updateTime(float time);

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
		bool _projectile;

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
