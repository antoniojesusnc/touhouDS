



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


#include "Debug.h"


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
CSprite::CSprite(const char *sprite, u16 width, u16 height) {
	
	_idRam = CSprite::IdRam++;
	NF_LoadSpriteGfx(sprite, _idRam, width, height);
	
	_size = new Vector2(width,height);

	//CDebug::getInstance()->WriteText("a ver: ", &_size );

	_inVram = false;
	
	if(CSprite::IdRam >= MAX_ID_SPRITE_RAM){
		CSprite::IdRam = 0;
	}
} // CSprite

// Contructor clase CSprite
CSprite::CSprite(const char *sprite,const char *palette, u16 width, u16 height) {
	
	_idRam = CSprite::IdRam++;
	NF_LoadSpriteGfx(sprite, _idRam, width, height);
	
	_size = new Vector2(width,height);
	_inVram = false;
	
	if(CSprite::IdRam >= MAX_ID_SPRITE_RAM){
		CSprite::IdRam = 0;
	}

	_palette = new CPalette(palette);
} // CSprite

// Destructor clase CSprite
CSprite::~CSprite(void) {

	

	NF_DeleteSprite(getScreen(), getIdScreen()); // delete from screen
	NF_FreeSpriteGfx(getScreen(), getIdVRam()); // delete from vRam
	NF_UnloadSpriteGfx(getIdRam()); // delete from ram
	
	//NF_Error(getIdRam(),"a",54);
	
	/* */
	
	delete _palette;
	delete _size;
	delete _position;

}

// Crea el puntero externo a la clase
CSprite *Sprite;



/*
	Metodos de la clase "CSprite"
*/
u16 CSprite::MoveSpriteToVRam(bool upScreen, bool palette){
	_idVRam = CSprite::IdVRam++;
	_upScreen = upScreen;
	
	NF_VramSpriteGfx(getScreen(), _idRam, _idVRam, true);
	
	_inVram = true;
	
	
	if(CSprite::IdVRam >= CSprite::MAX_ID_SPRITE_VRAM){
		CSprite::IdVRam = 0;
	}
	
	if(palette){
		_palette->MovePaletteToVRam(upScreen);
	}
	
	return _idVRam;
}



void CSprite::CreateSprite(const Vector2 *position) {
	if(!_inVram)
		MoveSpriteToVRam(_upScreen,true);
		
	_idScreen = CSprite::IdScreen++;
	_position = new Vector2 (*position);
	
	// Crea el Sprite
	NF_CreateSprite(getScreen(),_idScreen, _idVRam, _palette->getIdVRam(), (*_position).x, (*_position).y);

	if(CSprite::IdScreen >= MAX_ID_SPRITE_SCREEN){
		CSprite::IdScreen = 0;
	}

}


// Mueve las bolas
void CSprite::MoveSpriteToPos(const Vector2 *newPosition) {

	delete _position;
	_position = new Vector2(*newPosition);
	// Mueve el sprite
	NF_MoveSprite(getScreen(), _idScreen, _position->getX(), _position->getY());
	
}
