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
		enum Direction{NoDir, Up, Down, Left, Right};
		enum Commands{NoInput, Attack, WeakProj, StrongProj, Jump, Dash, Start, Select};

		

		// Destructor
		~CInputs(void);

		//	Metodos
		void Update();
		
		Direction* getDirections(){return _directions;}
		Commands* getCommands(){return _commnads;}
		Vector2* getTouchPos(){return &_touchPos;}

		// singleton
		static CInputs* getInstance();
		

	private:

		void checkCombos();
		void checkDirections();
		
		// resets
		void resetDirections();
		// increment index
		void incrementDirectionIndex();
		void incrementInputsIndex();
		
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
