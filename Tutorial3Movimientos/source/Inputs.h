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

					JumpBackDown, JumpDown, JumpFrontDown, JumpBack, JumpStand, JumpFront, JumpBackUp, JumpUp, JumpFrontUp,
					JumpAttackBackDown, JumpAttackDown, JumpAttackFrontDown, JumpAttackBack, JumpAttackStand, JumpAttackFront, JumpAttackBackUp, JumpAttackUp, JumpAttackFrontUp,
					JumpProjBackDown, JumpProjDown, JumpProjFrontDown, JumpProjBack, JumpProjStand, JumpProjFront, JumpProjBackUp, JumpProjUp, JumpProjFrontUp,
					JumpStrongProjBackDown, JumpStrongProjDown, JumpStrongProjFrontDown, JumpStrongProjBack, JumpStrongProjStand, JumpStrongProjFront, JumpStrongProjBackUp, JumpStrongProjUp, JumpStrongProjFrontUp,
					JumpDashBackDown, JumpDashDown, JumpDashFrontDown, JumpDashBack, JumpDashStand, JumpDashFront, JumpDashBackUp, JumpDashUp, JumpDashFrontUp,

					Hit, HitAir, HitGround,
					Start, Select, NoCommand,
					Size
		};
	
		

		// Destructor
		~CInputs(void);

		//	Metodos
		void Update();
		
		Direction* getDirections(){return _directions;}
		Commands* getCommands(){return _commands;}
		Vector2* getTouchPos(){return &_touchPos;}

		// singleton
		static CInputs* getInstance();
		
		Commands commandToJumpCommand(Commands command);

		Commands stringToCommand(char* string);
		char* commandToString(Commands command);
		char *directionToString(Direction dir);
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
		
		Commands _commands[4];
		u8 _commandsIndex;

		// singleton
		// private constructor
		CInputs();

		static CInputs *_instance;
};



#endif
