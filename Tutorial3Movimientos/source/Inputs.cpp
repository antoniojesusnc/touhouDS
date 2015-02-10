



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
#include "Inputs.h"


/*
	Metodos de la clase "CInput"
*/

// Contructor clase CInput
CInputs::CInputs() {
	_keys = 0;
} // CInput

// Destructor clase CInput
CInputs::~CInputs(void) {
	delete &_touchPos;
	delete &_touchScreen;
} // ~CInput

CInputs *CInputs::_instance = 0;

CInputs* CInputs::getInstance(){
	if(!_instance){
		_instance = new CInputs();
	}
	return _instance;
} // getPtr

/*
	Metodos de la clase "CInput"
*/
void CInputs::checkDirections(){
	resetDirections();

	if(_keys == KEY_UP){
		_directions[_directionIndex] = Up;
		incrementDirectionIndex();
	}
	if(_keys == KEY_DOWN){
		_directions[_directionIndex] = Down;
		incrementDirectionIndex();
	}
	if(_keys == KEY_LEFT){
		_directions[_directionIndex] = Left;
		incrementDirectionIndex();
	}
	if(_keys == KEY_RIGHT){
		_directions[_directionIndex] = Right;
		incrementDirectionIndex();
	}
	
} // checkDirections

void CInputs::incrementDirectionIndex(){
	++_directionIndex;
	if(_directionIndex > 2){
		_directionIndex = 0;
	}
} // incrementDirectionIndex

void CInputs::resetDirections(){
	for(vu8 i = 0; i < 2; ++i){
		_directions[_directionIndex] = NoDir;
	}
	_directionIndex = 0;
} // incrementDirectionIndex

void CInputs::incrementInputsIndex(){
	++_commnadsIndex;
	if(_commnadsIndex > 4){
		_commnadsIndex = 0;
	}
} // incrementInputsIndex
		
		
void CInputs::Update(){

	scanKeys();
	//_keys = keysDown();
	

	_keys = keysHeld();

	touchRead(&_touchScreen);
	_touchPos.x = _touchScreen.px;
	_touchPos.y = _touchScreen.py;
	
	checkDirections();

	//_keys = keysUp();
	
	//_keys = keysCurrent ();
	
	
} // Update
