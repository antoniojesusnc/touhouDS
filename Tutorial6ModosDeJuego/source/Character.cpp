

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
#include "ProjectileMovement.h"
#include "SpriteAnimated.h"
#include "Palette.h"
#include "Math.h"
#include "XMLParser.h"

#include "Debug.h"

// static variables
/*
	Metodos de la clase "CCharacter"
*/

// Contructor clase CCharacter
CCharacter::CCharacter(const char* character, bool pnj) {
	_pnj = pnj;
	vu8 lenth = strlen(character);
	_name = (char*)malloc(sizeof(char)*(lenth) );
	strcpy(_name, character );
	_name[lenth] = '\0';
	
	
	_input = CInputs::getInstance();
	_commands = _input->getCommands();
	_directions = _input->getDirections();
	//_standPos = new CSpriteAnimated("sprite/characters/sakuya/sakuya1","sprite/characters/sakuya/original",32,64, 1);
	//_standPos = new CSpriteAnimated("sprite/bola","sprite/bola",32,32, 2);
	//_standPos = new CSpriteAnimated("sprite/characters/sakuya/bola","sprite/characters/sakuya/bola",32,32, 2);
	//_standPos = new CSpriteAnimated("sprite/characters/sakuya/sakuya1","sprite/characters/sakuya/original",32,64, 6);

} // CCharacter

// Destructor clase CCharacter
CCharacter::~CCharacter(void) {
	free(_name);

	
	delete _palette;
	
	for(vu8 i = 0; i < CInputs::Size; ++i){
		delete _movementList[i];
		delete _projMovementList[i];
	}
	
} // ~CCharacter

/*
	Metodos de la clase "CCharacter"
*/

void CCharacter::Init(Vector2 *position) {

	
	//CXMLParser *data = new CXMLParser("sakuya");
	CXMLParser *xmlRaw = new CXMLParser(_name);
	
	
	_position = new Vector2(*position);
	_groundY = _position->getY();
	_jumping = CInputs::DirStand;
	_maxActiveMovement = 5;
	
	loadAttributes(xmlRaw->getDataByTag("data"));
	
	loadPalette();
	
	loadMovements(xmlRaw->getDataByTag("movements"));
	
	loadProjMovements(xmlRaw->getDataByTag("projMovements"));
	
	_indexMovement = (u16)CInputs::Stand;
	if(_movementList[_indexMovement] != NULL)
		_movementList[_indexMovement]->StartMovement();
	
	free(xmlRaw);
	//delete xmlRaw;
} // Init

void CCharacter::loadAttributes(CXMLParser::TXML *data){
	// leo las caracteristicas del player
	for(vu8 i = 0; i < data->numChilds; ++i){
		if(strcmp(data->childs[i]->tag, "health") == 0){
			_maxHealth = _health = atoi(data->childs[i]->value);
		}else if(strcmp(data->childs[i]->tag, "maxJumpHeight") == 0){
			_maxJumpHeight = _position->getY() - atoi(data->childs[i]->value);
			printf("\n\n%d",_maxJumpHeight );
		}else if(strcmp(data->childs[i]->tag, "body") == 0){
			loadBody(data->childs[i]);
		}

	}

	_horizontalSpeed = new Vector2(2,0);
} // loadAttributes

void CCharacter::loadBody(CXMLParser::TXML *data){
	// leo las caracteristicas del player
	_body = new Rect();
	for(vu8 i = 0; i < data->numChilds; ++i){
		if(strcmp(data->childs[i]->tag, "posX") == 0){
			_body->setX(atoi(data->childs[i]->value));
		}else if(strcmp(data->childs[i]->tag, "posY") == 0){
			_body->setY(atoi(data->childs[i]->value));
		}else if(strcmp(data->childs[i]->tag, "width") == 0){
			_body->setWidth(atoi(data->childs[i]->value));
		}else if(strcmp(data->childs[i]->tag, "height") == 0){
			_body->setHeight(atoi(data->childs[i]->value));
		}
	}

	_horizontalSpeed = new Vector2(2,0);
} // loadAttributes



void CCharacter::loadPalette(){

	
	char path[100];
	strcpy(path,"sprite/characters/");
	strcat(path, getName());
	strcat(path, "/");
	strcat(path, getName());
	_palette = new CPalette(path);
	//free(path);
	

	
} // loadPallete

void CCharacter::loadMovements(CXMLParser::TXML *data){
	
	//printf("\n %d ",_movementList );//,sizeof(CMovement*));

	u8 num = CInputs::Size;
	//_movementList = (CMovement**)malloc(sizeof(CMovement*)*data->numChilds);
	_movementList = (CMovement**)malloc(sizeof(CMovement*)* num);
	//_movementList = (*CMovement)[data->numChilds];
	
	for(vu8 i = 0; i < num; ++i){
		_movementList[i] = NULL;
	}
	CMovement *tempMovement;

	// leo la lista de movimientos
	for(vu8 i = 0; i < data->numChilds; ++i){
		tempMovement = new CMovement();
		tempMovement->Init(data->childs[i], this, _palette);

		_movementList[tempMovement->getCommandIndex()] = tempMovement;
		//tempMovement = NULL;		
	}
	
	
	printf("\n MOVEments");
	for(vu8 i = 0; i < num; ++i){
		if(_movementList[i] != NULL){
			printf("\n %d %s",i, CInputs::getInstance()->commandToString((CInputs::Commands)i ) );
			
		}
	}
	

	/*	
	_movementList = new CMovement[3]();
	// load movements
	_movementList[0].Init("0", this);
	_movementList[1].Init("1", this);
	_movementList[2].Init("2", this);
	*/
} // loadMovements

void CCharacter::loadProjMovements(CXMLParser::TXML *data){
	
	//printf("\n %d ",_movementList );//,sizeof(CMovement*));
	// max 5 movements
	_activeProjMovements = (CProjectileMovement**)malloc(sizeof(CProjectileMovement*)* _maxActiveMovement);
	for(vu8 i = 0; i < _maxActiveMovement; ++i){
		_activeProjMovements[i] = NULL;
	}
	_someProjActive = false;

	u8 num = CInputs::Size;
	//_movementList = (CMovement**)malloc(sizeof(CMovement*)*data->numChilds);
	_projMovementList = (CProjectileMovement**)malloc(sizeof(CProjectileMovement*)* num);
	//_movementList = (*CMovement)[data->numChilds];
	
	for(vu8 i = 0; i < num; ++i){
		_projMovementList[i] = NULL;
	}
	CProjectileMovement *tempProjMovement;

	// leo la lista de movimientos
	for(vu8 i = 0; i < data->numChilds; ++i){
		tempProjMovement= new CProjectileMovement();
		tempProjMovement->Init(data->childs[i], this, _palette);

		_projMovementList[tempProjMovement->getCommandIndex()] = tempProjMovement;
		//tempMovement = NULL;		
	}
	
	/*
	for(vu8 i = 0; i < num; ++i){
		if(_projMovementList[i] != NULL){
			printf("\nProj %d %s",i, CInputs::getInstance()->commandToString((CInputs::Commands)i ) );
			
		}
	}
	*/

	/*	
	_movementList = new CMovement[3]();
	// load movements
	_movementList[0].Init("0", this);
	_movementList[1].Init("1", this);
	_movementList[2].Init("2", this);
	*/
} // loadMovements

void CCharacter::checkMovement() {
	
	bool canJump = _jumping == CInputs::DirStand;

	if(canJump){
		//printf("\n %s %s",CInputs::getInstance()->directionToString(_jumping), CInputs::getInstance()->directionToString(_directions[0]));
		if(_directions[0] == CInputs::DirUp){
			_jumping = CInputs::DirUp;
			checkChangeCommand((u16)CInputs::Up, true);
		} else if(_directions[0] == CInputs::DirFrontUp){
			_jumping = CInputs::DirFrontUp;
			checkChangeCommand((u16)CInputs::FrontUp, true);
		} else if(_directions[0] == CInputs::DirBackUp){
			_jumping = CInputs::DirBackUp;
			checkChangeCommand((u16)CInputs::BackUp, true);
		}
	}

	if(canJump ){
		checkChangeCommand((u16)_commands[0]);
	}else{
		checkChangeCommand((u16)_input->commandToJumpCommand(_commands[0]));
	}
	/*
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
	*/

} // checkMovement

void CCharacter::checkMovementPNJ() {
	
	checkChangeCommand((u16)CInputs::Stand);
	/*
	bool canJump = _jumping == CInputs::DirStand;

	
	if(canJump){
		//printf("\n %s %s",CInputs::getInstance()->directionToString(_jumping), CInputs::getInstance()->directionToString(_directions[0]));
		if(_directions[0] == CInputs::DirUp){
			_jumping = CInputs::DirUp;
			checkChangeCommand((u16)CInputs::Up, true);
		} else if(_directions[0] == CInputs::DirFrontUp){
			_jumping = CInputs::DirFrontUp;
			checkChangeCommand((u16)CInputs::FrontUp, true);
		} else if(_directions[0] == CInputs::DirBackUp){
			_jumping = CInputs::DirBackUp;
			checkChangeCommand((u16)CInputs::BackUp, true);
		}
	}

	if(canJump ){
		checkChangeCommand((u16)_commands[0]);
	}else{
		checkChangeCommand((u16)_input->commandToJumpCommand(_commands[0]));
	}
	/*
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
	*/

} // checkMovement

bool CCharacter::checkChangeCommand(u8 newIndex, bool force){

	/*
	if(newIndex != CInputs::Stand && newIndex != CInputs::NoCommand){
		printf("\n %d %s ",newIndex, CInputs::getInstance()->commandToString((CInputs::Commands)(newIndex)) );
	}
	*/

	if(!force && (!_movementList[_indexMovement]->canBeBlock() && _movementList[_indexMovement]->isActivated()) )
		return false;

	if(force || (_indexMovement != newIndex || !_movementList[_indexMovement]->isActivated()) ){
		
		if(force || _movementList[newIndex] != NULL){
			_movementList[_indexMovement]->CancelMovement();
			_indexMovement = newIndex;
			_movementList[_indexMovement ]->StartMovement();

			if(_projMovementList[_indexMovement] != NULL){
				activateProjMovements(newIndex);
			}

			return true;
		}
	}
	return false;
} // checkAndChangeIfDiferent


void CCharacter::executeJump() {
	vu8 jumpSpeed = 2;
	if(_jumping != CInputs::DirStand){
		if(_jumping == CInputs::DirUp){
			_position->setY(_position->getY() - jumpSpeed);
		} else if(_jumping == CInputs::DirFrontUp){
			_position->setXY(_position->getX() + jumpSpeed*0.5f, _position->getY() - jumpSpeed);
		} else if(_jumping == CInputs::DirBackUp){
			_position->setXY(_position->getX() - jumpSpeed*0.5f, _position->getY() - jumpSpeed);

		} else if(_jumping == CInputs::DirDown){
			_position->setY(_position->getY() + jumpSpeed);
		} else if(_jumping == CInputs::DirFrontDown){
			_position->setXY(_position->getX() + jumpSpeed*0.5f, _position->getY() + jumpSpeed);
		} else if(_jumping == CInputs::DirBackDown){
			_position->setXY(_position->getX() - jumpSpeed*0.5f, _position->getY() + jumpSpeed);
		}
	}

	if(_position->getY() <= _maxJumpHeight){
		_position->setY(_maxJumpHeight);

		if(_jumping == CInputs::DirUp){
			_jumping = CInputs::DirDown;
		} else if(_jumping == CInputs::DirFrontUp){
			_jumping = CInputs::DirFrontDown;
		} else if(_jumping == CInputs::DirBackUp){
			_jumping = CInputs::DirBackDown;
		} 
	}

	if(_position->getY() >= _groundY){
		_position->setY(_groundY);
		_jumping = CInputs::DirStand;
		checkChangeCommand((u16)CInputs::Stand, true);
		/*
		if(_jumping == CInputs::DirDown){
			_jumping = CInputs::DirStand;
		} else if(_jumping == CInputs::DirFrontDown){
			_jumping = CInputs::DirStand;
		} else if(_jumping == CInputs::DirBackDown){
			_jumping = CInputs::DirStand;
		}
		*/
	}
} // executeJump

void CCharacter::activateProjMovements(u8 index){
	bool exist = false;
	
	if(_someProjActive){
		for(vu8 i = 0; i < _maxActiveMovement && !exist; ++i){
			if(_activeProjMovements[i]->getCommandIndex() == index){
				exist = true;
				_activeProjMovements[i]->CancelMovement();
				_activeProjMovements[i] = NULL;
			}
		}
	}

	for(vu8 i = 0; i < _maxActiveMovement; ++i){
		if(_activeProjMovements[i] == NULL){
			_activeProjMovements[i] = _projMovementList[index];
			_activeProjMovements[i]->StartMovement();
			_someProjActive = true;
			return;
		}
	}
	
} // activateProjMovements


void CCharacter::UpdateCharacter(vfloat32 time) {
	
	
	
	if(_movementList[_indexMovement] != NULL){
		_movementList[_indexMovement]->UpdateMovement(time);
	}

	if(_someProjActive){
		_someProjActive = false;
		for(vu8 i = 0; i < _maxActiveMovement; ++i){
			if(_activeProjMovements[i] != NULL){
				if(_activeProjMovements[i]->isActivated()){
					_activeProjMovements[i]->UpdateMovement(time);
					if(_activeProjMovements[i]->isActivated()){
						_someProjActive = true;
					}else{
						_activeProjMovements[i] = NULL;
					}
				}
			} // end if
		}
	} // some proj Activae

	if(isPNJ()){
		checkMovementPNJ();
	}else{
		checkMovement();
	}
	
	if(_jumping != CInputs::DirStand){
		executeJump();
	}
	if(_commands[0] != CInputs::Stand){
		//printf("\n %d %d %s ",_indexMovement ,_commnads[0], CInputs::getInstance()->commandToString(_commnads[0]) );
	}
	
	

	
} // UpdateCharacter


void CCharacter::TakeHitPoints(u16 damage){
	if(damage > _health){
		_health = 0;
	}else{
		_health -= damage;
	}
} // TakeHitPoints