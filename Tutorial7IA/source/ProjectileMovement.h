#ifndef __PROJECTILEMOVEMENT_H__
#define __PROJECTILEMOVEMENT_H__




/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/



// Includes propietarios NDS
#include <nds.h>

#include "Inputs.h"
//#include "Movement.h"
#include "XMLParser.h"

// Defines
class Vector2;
class CSprite;
class CSpriteAnimated;
class CCharacter;
class CProjectile;
class CRect;

// Clase CProjectileMovement
class CProjectileMovement: public CMovement {

	public:
		
		// Contructores
		CProjectileMovement();
		
		// Destructor
		~CProjectileMovement(void);

		void Init(CXMLParser::TXML* movementData, CCharacter *_owner, CPalette *palette);
		

		// startMovement
		void StartMovement();
		
		// finish
		void FinishMovement();

		// cancel
		void CancelMovement();
		

		// update
		void UpdateMovement(vfloat32 time);

		int getCommandIndex(){return (int)_command;}
		CProjectile** getProjectiles(){return _projectiles;}
		u8 getNumProjectiles(){return _numProjectiles;}
		/*
		void setActivated(bool activated){_activated = activated;}

		char *getName(){return _name;}
		int getCommandIndex(){return (int)_command;}
		CSpriteAnimated* getSprite(){return _sprite;}

		bool isActivated(){ return _activated;}
		bool canBeBlock(){ return _canBeBlock;}
		*/
		// operators

	protected:

		void initFrames(CXMLParser::TXML* frameData);
		void initProjectiles();
		void updateSprite(float time);

		CProjectile **_projectiles;

		float _speedX;
		float _speedY;
		Vector2* _firstPosOffset;
		u8 _numProjectiles;
		float _dispersion;



};



#endif
