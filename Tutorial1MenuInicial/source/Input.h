#ifndef __INPUT_H__
#define __INPUT_H__





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
class CInput {

	public:
		enum Direction{Up, Down, Left, Right};
		enum Inputs{Attack, WeakProj, StrongProj, Jump, Dash, Start, Select};

		

		

		// Destructor
		~CInput(void);

		//	Metodos
		void Update();
		
		u8* getDirections(){return _directions;}
		u8* getInputs(){return _inputs;}
		Vector2* getTouchPos(){return &_touchPos;}

		// singleton
		static CInput* getInstance();
		

	private:

		void checkCombos();
		void checkDirections();
		
		// increment index
		void incrementDirectionIndex();
		void incrementInputsIndex();
		
		u16 _keys;
		touchPosition _touchScreen;
		Vector2 _touchPos;
		
		u8 _directions[2];
		u8 _directionIndex;
		
		u8 _inputs[4];
		u8 _inputIndex;

		// singleton
		// private constructor
		CInput();

		static CInput *_instance;
};



#endif
