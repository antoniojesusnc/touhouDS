



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
#include "sprite.h"


#include "Debug.h"


// static variables

u8 CSprite::MAX_ID_SPRITE_RAM = 126;
u8 CSprite::MAX_ID_SPRITE_VRAM = 64;
u8 CSprite::MAX_ID_SPRITE_SCREEN = 126;

u8 CSprite::IdRam = 1;
u8 CSprite::IdVRam = 1;
u8 CSprite::IdScreen = 1;

std::set<u8> CSprite::ALLRamId;
std::set<u8> CSprite::ALLVRamId;
std::set<u8> CSprite::ALLScreenId;

/*
	Metodos de la clase "CSprite"
*/

CSprite::CSprite(CSprite &sprite){
	_externPalette = false;
	_idRam = sprite.getIdRam();
	_size = new Vector2(*sprite.getSize());

	_palette = sprite.getPalette();
	
	if(sprite.isInVRam()){
		
		_inVram = true;
		_idVRam = sprite.getIdVRam();
		_position = new Vector2(*sprite.getPosition());
		_upScreen = sprite.isUpScreen();

	}else{
		_inVram = false;
	}
}

// Contructor clase CSprite
CSprite::CSprite(const char *sprite, u16 width, u16 height) {
	_externPalette = false;

	_idVRam = 0;
	_idScreen= 0;

	_idRam = CSprite::IdRam++;
	while(ALLRamId.find(_idRam) != ALLRamId.end()){
		if(CSprite::IdRam >= CSprite::MAX_ID_SPRITE_RAM){
			CSprite::IdRam = 1;
		}
		_idRam = CSprite::IdRam++;
	}
	ALLRamId.insert(_idRam);

	NF_LoadSpriteGfx(sprite, _idRam, width, height);
	_size = new Vector2(width,height);
	_inVram = false;
	
	if(CSprite::IdRam >= MAX_ID_SPRITE_RAM){
		CSprite::IdRam = 1;
	}

	_position = new Vector2();
} // CSprite

// Contructor clase CSprite
CSprite::CSprite(const char *sprite,const char *palette, u16 width, u16 height) {
	_externPalette = false;
	
	_idVRam = 0;
	_idScreen= 0;
	
	_idRam = CSprite::IdRam++;
	
	while(ALLRamId.find(_idRam) != ALLRamId.end()){
		if(CSprite::IdRam >= CSprite::MAX_ID_SPRITE_RAM){
			CSprite::IdRam = 1;
		}
		_idRam = CSprite::IdRam++;
	}
	ALLRamId.insert(_idRam);

	NF_LoadSpriteGfx(sprite, _idRam, width, height);
	_size = new Vector2(width,height);
	_inVram = false;
	if(CSprite::IdRam >= MAX_ID_SPRITE_RAM){
		CSprite::IdRam = 1;
	}
	_palette = new CPalette(palette);
	
	_position = new Vector2();

} // CSprite



// Destructor clase CSprite
CSprite::~CSprite() {


	if(_idVRam > 0)
		removeFromVRam(false);

	if(_idScreen > 0)
		removeFromScreen();
	
	if(_idRam > 0)
		removeFromRam();

	//NF_DeleteSprite(getScreen(), getIdScreen()); // delete from screen
	//NF_FreeSpriteGfx(getScreen(), getIdVRam()); // delete from vRam
	//NF_UnloadSpriteGfx(getIdRam()); // delete from ram
	
	if(!_externPalette){
		delete _palette;
	}
	_palette = NULL;
	//delete _size;
	//delete _position;
}

void CSprite::removeFromRam(){

	NF_UnloadSpriteGfx(getIdRam());
	
	ALLRamId.erase (ALLRamId.find(getIdRam()));

	_idRam = 0;
} // removeFromRam

void CSprite::removeFromVRam(bool palette){
	if(!isInVRam())
		return;

	NF_FreeSpriteGfx(getScreen(), getIdVRam());
	
	ALLVRamId.erase (ALLVRamId.find(getIdVRam()));
	
	_inVram = false;
	_idVRam = 0;
	
	if(palette){
		if(_palette)
			_palette->removeFromVRam();
	}
} // removeFromVRam

void CSprite::removeFromScreen(){
	_flipped = false;

	NF_DeleteSprite(getScreen(), getIdScreen());
	//NF_Error(getIdScreen(),"",getIdScreen());
	ALLScreenId.erase (ALLScreenId.find(getIdScreen()));
	
	_idScreen = 0;
} // removeFromScreen

// Crea el puntero externo a la clase
CSprite *Sprite;



/*
	Metodos de la clase "CSprite"
*/
u16 CSprite::MoveSpriteToVRam(bool upScreen, bool palette, bool loadOnlyFirst){
	
	_upScreen = upScreen;
	
	_idVRam = CSprite::IdVRam++;

	
	while(ALLVRamId.find(_idVRam) != ALLVRamId.end()){
		if(CSprite::IdVRam >= CSprite::MAX_ID_SPRITE_VRAM){
			CSprite::IdVRam = 1;
		}
		_idVRam = CSprite::IdVRam++;
	}
	ALLVRamId.insert(_idVRam);
	
	NF_VramSpriteGfx(getScreen(), _idRam, _idVRam, loadOnlyFirst);
	
	_inVram = true;
	
	
	
	if(palette){
		_palette->MovePaletteToVRam(upScreen);
	}
	
	return _idVRam;
}



void CSprite::CreateSprite(Vector2 *position) {
	if(!_inVram){
		MoveSpriteToVRam(_upScreen,true);
	}

	
	_position->setXY(*position);
	
	_idScreen = CSprite::IdScreen++;
	while(ALLScreenId.find(_idScreen) != ALLScreenId.end()){
		if(CSprite::IdScreen >= CSprite::MAX_ID_SPRITE_SCREEN){
			CSprite::IdScreen = 1;
		}
		_idScreen = CSprite::IdScreen++;
	}
	// Crea el Sprite
	ALLScreenId.insert(_idScreen);
	NF_CreateSprite(getScreen(),_idScreen, _idVRam, _palette->getIdVRam(), _position->getX(), _position->getY());

	if(CSprite::IdScreen >= MAX_ID_SPRITE_SCREEN){
		CSprite::IdScreen = 1;
	}

} // CreateSprite


// Mueve las bolas
void CSprite::MoveSpriteToPos(Vector2 *newPosition) {
	if(newPosition == _position)
		return;

	//delete _position;
	//_position = new Vector2(*newPosition);
	_position->setXY(newPosition->getX(), newPosition->getY());
	// Mueve el sprite
	NF_MoveSprite(getScreen(), _idScreen, _position->getX(), _position->getY());
	
}

void CSprite::FlipTo(CInputs::Direction direction){
	if(direction == CInputs::DirFront && isflipped()){
		_flipped = false;
		NF_HflipSprite(getScreen(), _idScreen, _flipped);
	}else{
		if(direction == CInputs::DirBack && !isflipped()){
			_flipped = true;
			NF_HflipSprite(getScreen(), _idScreen, _flipped);
		}
	}
} // FlipTo

void CSprite::setOrder(u8 layer){
	NF_SpriteLayer(getScreen(),getIdScreen(),layer);
}