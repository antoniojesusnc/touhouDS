



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




// static variables

// Contructor clase CSpriteAnimatedAnimated
CSpriteAnimated::CSpriteAnimated(const char *spriteAnimated, u16 width, u16 height, int frames)
	: CSprite (spriteAnimated,width,(height*frames)) {
	
} // CSpriteAnimated

// Contructor clase CSpriteAnimated
CSpriteAnimated::CSpriteAnimated(const char *spriteAnimated,const char *palette, u16 width, u16 height, int frames) 
	: CSprite ( spriteAnimated,palette, width, height * frames ) {
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
}



void CSpriteAnimated::CreateSprite(const Vector2 *position) {
	CSprite::CreateSprite(position);
}


// Mueve las bolas
void CSpriteAnimated::MoveSpriteToPos(const Vector2 *newPosition) {
	CSprite::MoveSpriteToPos(newPosition);
}
