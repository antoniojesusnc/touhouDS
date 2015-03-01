#ifndef __INPUTS_H__
#define __INPUTS_H__





/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/


// Includes propietarios NDS
#include <nds.h>
#include "Math.h"


// Defines


// Clase CInput
class CInputs {

	public:
		enum Direction{	DirBackDown, DirDown, DirFrontDown, DirBack, DirStand, DirFront, DirBackUp, DirUp, DirFrontUp};
		enum Commands{
					BackDown, Down, FrontDown, Back, Stand, Front, BackUp, Up, FrontUp,
					AttackBackDown, AttackDown, AttackFrontDown, AttackBack, AttackStand, AttackFront, AttackBackUp, AttackUp, AttackFrontUp,
					ProjBackDown, ProjDown, ProjFrontDown, ProjBack, ProjStand, ProjFront, ProjBackUp, ProjUp, ProjFrontUp,
					StrongProjBackDown, StrongProjDown, StrongProjFrontDown, StrongProjBack, StrongProjStand, StrongProjFront, StrongProjBackUp, StrongProjUp, StrongProjFrontUp,
					DashBackDown, DashDown, DashFrontDown, DashBack, DashStand, DashFront, DashBackUp, DashUp, DashFrontUp,
					Hit, HitAir, HitGround,
					Start, Select, NoCommand,
					Size
		};
	
		

		// Destructor
		~CInputs(void);

		//	Metodos
		void Update();
		
		Direction* getDirections(){return _directions;}
		Commands* getCommands(){return _commnads;}
		Vector2* getTouchPos(){return &_touchPos;}

		// singleton
		static CInputs* getInstance();
		
		Commands stringToCommand(char* string);
		char* commandToString(Commands command);

	private:

		void checkCombos();
		void checkDirections();
		
		// resets
		void resetDirections();
		// increment index
		void incrementDirectionIndex();
		void incrementInputsIndex();
		
		// debug

		u16 _keys;
		touchPosition _touchScreen;
		Vector2 _touchPos;
		
		Direction _directions[2];
		u8 _directionIndex;
		
		Commands _commnads[4];
		u8 _commnadsIndex;

		// singleton
		// private constructor
		CInputs();

		static CInputs *_instance;
};



#endif
