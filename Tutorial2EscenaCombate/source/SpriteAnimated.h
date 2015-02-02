#ifndef __SPRITE_ANIMATED_H__
#define __SPRITE_ANIMATED_H__





/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/




// Includes propietarios NDS
#include <nds.h>
#include "Math.h"
#include "Sprite.h"


// Defines


// Clase CSpriteAnimatedAnimated
class CSpriteAnimated : public CSprite {

	public:
		
		// Contructores
		CSpriteAnimated(const char *spriteAnimated, u16 witdh, u16 height, int frames);
		
		// Constructor con paleta
		CSpriteAnimated(const char *spriteAnimated,const char *palette, u16 witdh, u16 height, int frames);

		// Destructor
		~CSpriteAnimated(void);
		
		//	Metodos
		
		u16 MoveSpriteToVRam(bool upScreen, bool palette, bool loadOnlyFirst = true);
		
		
		// Crea un spriteAnimated
		void CreateSprite(const Vector2 *position);

		// Mueve el spriteAnimated
		void MoveSpriteToPos(const Vector2 *newPosition);
		
	private:	
	
};



#endif
