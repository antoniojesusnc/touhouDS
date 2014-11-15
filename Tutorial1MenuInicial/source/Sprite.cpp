



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
#include "sprite.h"


// static variables

u8 CSprite::MAX_ID_SPRITE_RAM = 255;
u8 CSprite::MAX_ID_SPRITE_VRAM = 64;
u8 CSprite::MAX_ID_SPRITE_SCREEN = 255;

u8 CSprite::IdRam = 0;
u8 CSprite::IdVRam = 0;
u8 CSprite::IdScreen = 0;

/*
	Metodos de la clase "CSprite"
*/

// Contructor clase CSprite
CSprite::CSprite(char *sprite, u8 width, u8 height) {
	
	_idRam = ++IdRam;
	NF_LoadSpriteGfx(sprite, _idRam, width, height);
	
	_inVram = false;
	
	if(IdRam >= MAX_ID_SPRITE_RAM){
		IdRam = 0;
	}
	
}

// Contructor clase CSprite
CSprite::CSprite(char *sprite, char *pallete, u8 width, u8 height) {
	CSprite(sprite, width, height);
	NF_LoadSpritePal(pallete, 0);
}

// Destructor clase CSprite
CSprite::~CSprite(void) {
}

// Crea el puntero externo a la clase
CSprite *Sprite;



/*
	Metodos de la clase "CSprite"
*/
u8 CSprite::MoveSpriteToVRam(bool upScreen, bool palette){
	_idVRam = ++IdVRam;
	_upScreen = upScreen;
	
	NF_VramSpriteGfx(getScreen(), _idRam, _idVRam, false);
	
	_inVram = true;
	
	
	if(IdVRam >= MAX_ID_SPRITE_VRAM){
		IdVRam = 0;
	}
	
	if(palette){
		_palette->MovePaletteToVRam(upScreen);
	}
	
	return _idVRam;
}



void CSprite::CreateSprite(Vector2 position, bool upScreen, bool palette) {
	if(!_inVram)
		MoveSpriteToVRam(upScreen,palette);
		
	_idScreen = ++IdScreen;
	_position = position;
	
	// Crea el Sprite
	NF_CreateSprite(getScreen(),_idScreen, _idVRam, _palette->getIdVRam(), position.x, position.y);

	if(IdScreen >= MAX_ID_SPRITE_SCREEN){
		IdScreen = 0;
	}
}


// Mueve las bolas
void CSprite::MoveSpriteToPos(Vector2 newPosition) {

	_position = newPosition;
	// Mueve el sprite
	NF_MoveSprite(getScreen(), _idScreen, _position.x, _position.y);
	
}
