



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
#include "SpriteAnimated.h"

#include "Debug.h"


// static variables

// Contructor clase CSpriteAnimatedAnimated
CSpriteAnimated::CSpriteAnimated(const char *spriteAnimated, u16 width, u16 height, u8 frames)
	: CSprite (spriteAnimated,width,height) {
	_maxFrame = frames;
	_durationPerFrame = new float[frames];

	for(vu8 i = 0; i < frames; ++i){
		_durationPerFrame[i] = 0.1f;
	}
} // CSpriteAnimated

// Contructor clase CSpriteAnimated
CSpriteAnimated::CSpriteAnimated(const char *spriteAnimated,const char *palette, u16 width, u16 height, u8 frames) 
	: CSprite ( spriteAnimated,palette, width,height ) {
	_maxFrame = frames;
	_durationPerFrame = new float[frames];

	for(vu8 i = 0; i < frames; ++i){
		_durationPerFrame[i] = 0.1f;
	}
} // CSpriteAnimated

// Destructor clase CSpriteAnimated
CSpriteAnimated::~CSpriteAnimated(void) {

}

// Crea el puntero externo a la clase
CSpriteAnimated *SpriteAnimated;



/*
	Metodos de la clase "CSpriteAnimated"
*/
 u16 CSpriteAnimated::MoveSpriteToVRam(bool upScreen, bool palette, bool loadOnlyFirst ){
	return CSprite::MoveSpriteToVRam(upScreen, palette, false);
} // MoveSpriteToVRam

void CSpriteAnimated::CreateSprite(const Vector2 *position) {
	CSprite::CreateSprite(position);
	_currentFrame = 0;
} // CreateSprite

// Mueve las bolas
void CSpriteAnimated::MoveSpriteToPos(const Vector2 *newPosition) {
	CSprite::MoveSpriteToPos(newPosition);
} // MoveSpriteToPos

void CSpriteAnimated::setFrame(u8 frame){
	NF_SpriteFrame(getScreen(),_idScreen,frame);
} // setFrame

void CSpriteAnimated::UpdateAnimation(vfloat32 time){
	_currentDuration += time;
	
	if(_durationPerFrame[_currentFrame] < _currentDuration){
		_currentDuration = 0;
		++_currentFrame;
		if(_currentFrame >= _maxFrame){
			_currentFrame = 0;
		}
		setFrame(_currentFrame);
	}
	
} // UpdateAnimation