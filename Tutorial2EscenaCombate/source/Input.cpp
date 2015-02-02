



/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/

// Includes C/C++
#include <stdio.h>

// Includes propietarios NDS
#include <nds.h>

// Includes librerias propias
#include <nf_lib.h>

// Includes del programa
#include "Input.h"


/*
	Metodos de la clase "CInput"
*/

// Contructor clase CInput
CInput::CInput() {
	_keys = 0;
} // CInput

// Destructor clase CInput
CInput::~CInput(void) {
	delete &_touchPos;
	delete &_touchScreen;
} // ~CInput

CInput *CInput::_instance = 0;

CInput* CInput::getInstance(){
	if(!_instance){
		_instance = new CInput();
	}
	return _instance;
} // getPtr

/*
	Metodos de la clase "CInput"
*/
void CInput::checkDirections(){
	if(_keys == KEY_UP){
		_inputs[_directionIndex] = Up;
		incrementDirectionIndex();
	}
	if(_keys == KEY_DOWN){
		_inputs[_directionIndex] = Down;
		incrementDirectionIndex();
	}
	if(_keys == KEY_LEFT){
		_inputs[_directionIndex] = Left;
		incrementDirectionIndex();
	}
	if(_keys == KEY_RIGHT){
		_inputs[_directionIndex] = Right;
		incrementDirectionIndex();
	}
	
} // checkDirections

void CInput::incrementDirectionIndex(){
	++_directionIndex;
	if(_directionIndex > 2){
		_directionIndex = 0;
	}
} // incrementDirectionIndex

void CInput::incrementInputsIndex(){
	++_inputIndex;
	if(_inputIndex > 4){
		_inputIndex = 0;
	}
} // incrementInputsIndex
		
		
void CInput::Update(){

	scanKeys();
	_keys = keysDown();
	touchRead(&_touchScreen);
	_touchPos.x = _touchScreen.px;
	_touchPos.y = _touchScreen.py;

	//_keys = keysHeld();
	
	//_keys = keysUp();
	
	//_keys = keysCurrent ();
	
	checkDirections();
} // Update
