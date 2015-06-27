



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

// Constructor de copia
CSpriteAnimated::CSpriteAnimated(CSpriteAnimated &sprite) : CSprite(sprite){
	_maxFrame = sprite.getMaxFrame();
	_durationPerFrame = sprite.getDurationPerFrame();

}

// Contructor clase CSpriteAnimatedAnimated
CSpriteAnimated::CSpriteAnimated(const char *spriteAnimated, u16 width, u16 height, u8 frames)
	: CSprite (spriteAnimated,width,height) {
	_maxFrame = frames;
	_durationPerFrame = new float[frames];

} // CSpriteAnimated

// Contructor clase CSpriteAnimated
CSpriteAnimated::CSpriteAnimated(const char *spriteAnimated,const char *palette, u16 width, u16 height, u8 frames) 
	: CSprite ( spriteAnimated,palette, width,height ) {
	_maxFrame = frames;
	_durationPerFrame = new float[frames];

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

void CSpriteAnimated::CreateSprite(Vector2 *position) {
	CSprite::CreateSprite(position);
	_currentFrame = 0;
} // CreateSprite

// Mueve las bolas
void CSpriteAnimated::MoveSpriteToPos(Vector2 *newPosition) {
	CSprite::MoveSpriteToPos(newPosition);
} // MoveSpriteToPos

void CSpriteAnimated::setFrame(u8 frame){
	if(_inVram)
		NF_SpriteFrame(getScreen(),_idScreen,frame);
} // setFrame

void CSpriteAnimated::UpdateAnimation(vfloat32 time){
	_currentDuration += time;
	//printf("%f", _currentDuration);
	if(_durationPerFrame[_currentFrame] < _currentDuration){
		_currentDuration = 0;
		++_currentFrame;
		if(_currentFrame >= _maxFrame){
			_currentFrame = 0;
		}
		setFrame(_currentFrame);
	}
	
} // UpdateAnimation