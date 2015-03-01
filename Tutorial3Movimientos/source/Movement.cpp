

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
#include "Math.h"
#include "Inputs.h"
#include "Movement.h"
#include "Character.h"
#include "SpriteAnimated.h"
#include "Sprite.h"

// static variables
/*
	Metodos de la clase "CMovement"
*/

CMovement *Movement;

// Contructor clase CMovement
CMovement::CMovement() {
	
	_activated = false;

	
} // CMovement

// Destructor clase CMovement
CMovement::~CMovement(void) {
} // ~CMovement

/*
	Metodos de la clase "CMovement"
*/

void CMovement::Init(CXMLParser::TXML* movementData, CCharacter *owner) {
	_owner = owner;
	_characterPosition = owner->getPosition();
	_position = new Vector2(*_characterPosition);

	char *auxTag;
	for(vu8 i = 0; i < movementData->numChilds; ++i){
		auxTag = movementData->childs[i]->tag;
		
		if(strcmp(auxTag, "name") == 0){
			strcpy(_name, movementData->childs[i]->value);
		}else if(strcmp(auxTag, "command") == 0){
			_command = CInputs::getInstance()->stringToCommand(movementData->childs[i]->value);
		}else if(strcmp(auxTag, "priority") == 0){
			_priority = atoi(movementData->childs[i]->value);
		}else if(strcmp(auxTag, "sprite") == 0){
			initSprite(movementData->childs[i]);
		}else if(strcmp(auxTag, "totalDuration") == 0){
			_totalDuration = atof(movementData->childs[i]->value);
		}else if(strcmp(auxTag, "loopable") == 0){
			_loopeable = strcmp(movementData->childs[i]->value, "true") == 0?true:false;
		}else if(strcmp(auxTag, "canBeBlocked") == 0){
			_canBeBlock = strcmp(movementData->childs[i]->value, "true") == 0?true:false;
		}else if(strcmp(auxTag, "movementData") == 0){
			
			initFrames(movementData->childs[i]);
		} // end if

	} // end for
		
	_sprite->setDurationPerFrame(_durationPerFrame);
} // Init

void CMovement::initSprite(CXMLParser::TXML* spriteData) {

	vu8 width;
	vu8 height;
	vu8 numFrames;
	char path[100];

	char *auxTag;
	for(vu8 i = 0; i < spriteData->numChilds; ++i){
		auxTag = spriteData->childs[i]->tag;

		if(strcmp(auxTag, "nameSprite") == 0){
			strcpy(path,"sprite/characters/");
			strcat(path, _owner->getName());
			strcat(path, "/");
			strcat(path, spriteData->childs[i]->value);
		}else if(strcmp(auxTag, "width") == 0){
			width = atoi(spriteData->childs[i]->value);
		}else if(strcmp(auxTag, "height") == 0){
			height = atoi(spriteData->childs[i]->value);
		}else if(strcmp(auxTag, "numFrames") == 0){
			numFrames = atoi(spriteData->childs[i]->value);
		}
	}
	//_sprite = new CSpriteAnimated(path,"sprite/characters/sakuya/sakuya",width,height,numFrames);
	_sprite = new CSpriteAnimated(path,width,height,numFrames);
	//printf("\n %s %d %d %d", path, width, height, numFrames);
	_sprite->setDurationPerFrame(_durationPerFrame);
	//free(path);
}

void CMovement::initFrames(CXMLParser::TXML* movementData) {
	
	vu8 numFrames = movementData->numChilds;
	
	
	_durationPerFrame = (float*)malloc(sizeof(float)*numFrames);
	_damagePerFrame = (u8*)malloc(sizeof(u8)*numFrames);
	_positionPerFrame = (Vector2**)malloc(sizeof(Vector2*)*numFrames);
	_offsetPerFrame = (Vector2**)malloc(sizeof(Vector2*)*numFrames);
	
	for(vu8 i = 0; i < numFrames; ++i){
		_positionPerFrame[i] = new Vector2(0,0);
		_offsetPerFrame[i] = new Vector2(0,0);
	}
	
	
	char* auxTagFrame;
	for(vu8 i = 0; i < numFrames; ++i){
		for(vu8 k = 0; k < movementData->childs[k]->numChilds; ++k){
			auxTagFrame = movementData->childs[i]->childs[k]->tag;
			if(strcmp(auxTagFrame, "duration") == 0){
				_durationPerFrame[i] = atof(movementData->childs[i]->childs[k]->value);
			}else if(strcmp(auxTagFrame, "damage") == 0){
				_damagePerFrame[i] = atoi(movementData->childs[i]->childs[k]->value);
			}else if(strcmp(auxTagFrame, "positionX") == 0){
				_positionPerFrame[i]->setX(atoi(movementData->childs[i]->childs[k]->value));
			}else if(strcmp(auxTagFrame, "positionY") == 0){
				_positionPerFrame[i]->setX(atoi(movementData->childs[i]->childs[k]->value));
			}else if(strcmp(auxTagFrame, "offsetX") == 0){
				_offsetPerFrame[i]->setX(atoi(movementData->childs[i]->childs[k]->value));
				//_offsetPerFrame[i]->x = atoi(movementData->childs[i]->childs[k]->value);
				//printf("\n 1 %d ",atoi(movementData->childs[i]->childs[k]->value));
				//printf("\n 1 %d %d",_offsetPerFrame[i]->getX(), _offsetPerFrame[i]->getY());
			}else if(strcmp(auxTagFrame, "offsetY") == 0){
				_offsetPerFrame[i]->setY(atoi(movementData->childs[i]->childs[k]->value));
				//_offsetPerFrame[i]->y = atoi(movementData->childs[i]->childs[k]->value);
				//printf("\n 2 %d %d",_offsetPerFrame[i]->getX(), _offsetPerFrame[i]->getY());
				//printf("\n 2 %d ",atoi(movementData->childs[i]->childs[k]->value));
				//printf("\n 2 %s ",movementData->childs[i]->childs[k]->value);
				//printf("\n 2 %d %d",_offsetPerFrame[i]->getX(), _offsetPerFrame[i]->getY());
			}
		}
	} // end for frames
}
void CMovement::StartMovement() {

	_activated = true;
	
	
	_frame = 0;
	//_position = _position + *position;
	_sprite->MoveSpriteToVRam(true,true);

	//printf("\n01 %d %d",_characterPosition->getX(), _characterPosition->getY());
	*_characterPosition += *_offsetPerFrame[_frame];
	_position->setXY(*_characterPosition);
	//printf("\n02 %d %d",_position->getX(), _position->getY());
	*_position += *_positionPerFrame[_sprite->getFrame()];

	_sprite->CreateSprite(_position);
	_sprite->FlipTo(_lookDirection);
	//_sprite->CreateSprite( _offsetPerFrame[0] + _characterPosition);

} // StartMovement

void CMovement::CancelMovement() {
	_activated = false;
	//delete _position;
	//_position = NULL;
	//*_characterPosition += *_offsetPerFrame[_frame];

	_sprite->removeFromScreen();
	_sprite->removeFromVRam();

} // CancelMovement

void CMovement::UpdateMovement(vfloat32 time) {
	if(!isActivated())
		return;
	
	_sprite->UpdateAnimation(time);
	
	if(_frame != _sprite->getFrame()){
		_frame = _sprite->getFrame();

		//printf("\n 1 %d %d",_characterPosition->getX(), _characterPosition->getY());
		//printf("\n 2 %d %d %d",_frame, _offsetPerFrame[_frame]->getX(), _offsetPerFrame[_frame]->getY());
		*_characterPosition += *_offsetPerFrame[_frame];
		//printf("\n 3 %d %d",_characterPosition->getX(), _characterPosition->getY());
		_position->setXY(*_characterPosition);
		//printf("\n 4 %d %d",_characterPosition->getX(), _characterPosition->getY());
		*_position += *_positionPerFrame[_sprite->getFrame()];

		_sprite->MoveSpriteToPos(_position);
	}
	

	_currentDuration += time;
	
	if(!_loopeable && _currentDuration >= _totalDuration){
		if(_loopeable){
			_currentDuration = 0;
		}else{
			setActivated(false);
		}
	}
} // UpdateMovement