

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
#include "Character.h"
#include "Inputs.h"
#include "Movement.h"
#include "Math.h"
#include "XMLParser.h"
#include "XMLParser2.h"

#include "Debug.h"

// static variables
/*
	Metodos de la clase "CCharacter"
*/

// Contructor clase CCharacter
CCharacter::CCharacter(const char *character) {
	strcpy(_name, character);

	

	_input = CInputs::getInstance();
	//_standPos = new CSpriteAnimated("sprite/characters/sakuya/sakuya1","sprite/characters/sakuya/original",32,64, 1);
	//_standPos = new CSpriteAnimated("sprite/bola","sprite/bola",32,32, 2);
	//_standPos = new CSpriteAnimated("sprite/characters/sakuya/bola","sprite/characters/sakuya/bola",32,32, 2);
	//_standPos = new CSpriteAnimated("sprite/characters/sakuya/sakuya1","sprite/characters/sakuya/original",32,64, 6);

} // CCharacter

// Destructor clase CCharacter
CCharacter::~CCharacter(void) {

} // ~CCharacter

/*
	Metodos de la clase "CCharacter"
*/

void CCharacter::Init(Vector2 *position) {

	//*
	CXMLParser *data = new CXMLParser("sakuya");
	//CXMLParser *data = new CXMLParser("demo");
	/*/
	CXMLParser2 *data = new CXMLParser2("demo");
	/* */

	// leo las caracteristicas del player
	_health = 100;
	_position = new Vector2(*position);
	_horizontalSpeed = new Vector2(2,0);

	// leo la lista de movimientos
	_movementList = new CMovement[3]();
	// load movements
	_movementList[0].Init("0", this);
	_movementList[1].Init("1", this);
	_movementList[2].Init("2", this);
	
	
	//_currentMovement = &_movementList[0];
	//_currentMovement->StartMovement(_position);
	_indexMovement = 0;
	_movementList[_indexMovement].StartMovement();
} // Init

void CCharacter::checkMovement() {
	if(_input->getDirections()[0] == CInputs::NoDir){
		if(checkAndChangeIfDiferent(0)) return;
	}

	if(_input->getDirections()[0] == CInputs::Right){
		*_position += *_horizontalSpeed;
		if(checkAndChangeIfDiferent(1)) return;
	}

	if(_input->getDirections()[0] == CInputs::Left){
		*_position -= *_horizontalSpeed;
		if(checkAndChangeIfDiferent(2)) return;
	}

} // checkMovement

bool CCharacter::checkAndChangeIfDiferent(u8 newIndex){
	if(_indexMovement != newIndex){
		
		_movementList[_indexMovement].CancelMovement();
		_indexMovement = newIndex;
		_movementList[_indexMovement].StartMovement();

		return true;
	}
	return false;
} // checkAndChangeIfDiferent


void CCharacter::UpdateCharacter(vfloat32 time) {
	

	checkMovement();

	_movementList[_indexMovement].UpdateMovement(time);
	//_currentMovement->UpdateMovement(time);

	
} // UpdateCharacter