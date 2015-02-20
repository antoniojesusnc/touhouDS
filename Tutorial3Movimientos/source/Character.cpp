

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

	
	//CXMLParser *data = new CXMLParser("sakuya");
	CXMLParser *xmlRaw = new CXMLParser("sakuya");
	_position = new Vector2(*position);

	loadAttributes(xmlRaw->getDataByTag("data"));
	//loadMovements(xmlRaw->getDataByTag("movements"));
	//_currentMovement = &_movementList[0];
	//_currentMovement->StartMovement(_position);
	_indexMovement = 0;
	//_movementList[_indexMovement].StartMovement();
} // Init

void CCharacter::loadAttributes(CXMLParser::TXML *data){
	// leo las caracteristicas del player
	for(vu8 i = 0; i < data->numChilds; ++i){
		if(strcmp(data->childs[i]->tag, "health") == 0){
			_health = atoi(data->childs[i]->value);
		}else if(strcmp(data->tag, "a") == 0){
		
		}
	}

	_horizontalSpeed = new Vector2(2,0);
} // loadAttributes

void CCharacter::loadMovements(CXMLParser::TXML *data){

	//_movementList = new CMovement[data->numChilds]();
	// leo la lista de movimientos
	for(vu8 i = 0; i < data->numChilds; ++i){
		//_movementList[i].Init(data->childs[i], this);
	}

	/*	
	_movementList = new CMovement[3]();
	// load movements
	_movementList[0].Init("0", this);
	_movementList[1].Init("1", this);
	_movementList[2].Init("2", this);
	*/
} // loadMovements

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
	
	/*
	checkMovement();

	_movementList[_indexMovement].UpdateMovement(time);
	*/

	
} // UpdateCharacter