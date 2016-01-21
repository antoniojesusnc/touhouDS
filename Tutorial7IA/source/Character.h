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
#include "XMLParser.h"

// Defines
class CMovement;
class CProjectileMovement;
class CPalette;
class Vector2;

// Clase CCharacter
class CCharacter {

	public:
		
		// Contructores
		CCharacter(const char* character, bool pnj);
		
		// Destructor
		~CCharacter(void);
		
		void Init(Vector2 *position);
		
		// update
		void UpdateCharacter(vfloat32 time);

		// other methods
		void ChangeLookDirection();


		void TakeHitPoints(u16 damage);

		// gets & sets
		u16 getMaxHealth(){return _maxHealth;}
		u16 getHealth(){return _health;}

		Vector2* getPosition(){return _position;}
		bool isLookingRight(){return _lookingFor == CInputs::Front;}
		bool isPNJ(){return _pnj;}

		char* getName(){return _name;}
		Rect* getBody(){return _body;}
		
		CMovement* getCurrentMovement(){return _movementList[_indexMovement];}
		bool hasProjectileActive(){return _someProjActive;}
		u8 getMaxActiveMovement(){return _maxActiveMovement;}
		CProjectileMovement** getActiveProjectileMovements(){return _activeProjMovements;}


	private:

		void checkMovement();
		void checkMovementPNJ();

		//bool checkAndChangeIfDiferent(CMovement *m);
		bool checkChangeCommand(u8 newIndex, bool force = false);
		void activateProjMovements(u8 index);

		void loadAttributes(CXMLParser::TXML* data);
		void loadBody(CXMLParser::TXML* data);
		void loadPalette();
		void loadMovements(CXMLParser::TXML* data);
		void loadProjMovements(CXMLParser::TXML* data);
		
		void executeJump();

		

		// characteristics
		char* _name;
		u16 _maxHealth;
		u16 _health;
		Vector2 *_horizontalSpeed;
		Rect *_body;
		bool _pnj;

		// jump variables
		u8 _groundY;
		u8 _maxJumpHeight;

		CInputs::Direction _jumping;

		// graphics
		CPalette *_palette;
		Vector2* _position;

		// movemnts
		CMovement **_movementList;
		u8 _indexMovement;

		// projectiles
		CProjectileMovement **_projMovementList;
		CProjectileMovement** _activeProjMovements;
		u8 _maxActiveMovement;
		bool _someProjActive;

		CInputs::Commands _lookingFor;

		CInputs *_input;
		CInputs::Direction *_directions;
		CInputs::Commands *_commands;
		
		
	
};



#endif
