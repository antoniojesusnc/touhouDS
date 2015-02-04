#ifndef __SPRITE_ANIMATED_H__
#define __SPRITE_ANIMATED_H__





/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/




// Includes propietarios NDS
#include <nds.h>
#include <cstdlib>
#include "Math.h"
#include "Sprite.h"


// Defines


// Clase CSpriteAnimatedAnimated
class CSpriteAnimated : public CSprite {

	public:
		
		// Contructores
		CSpriteAnimated(const char *spriteAnimated, u16 witdh, u16 height, u8 frames);
		
		// Constructor con paleta
		CSpriteAnimated(const char *spriteAnimated,const char *palette, u16 witdh, u16 height, u8 frames);

		// Destructor
		~CSpriteAnimated(void);
		
		//	Metodos
		u16 MoveSpriteToVRam(bool upScreen, bool palette, bool loadOnlyFirst = true);
		
		// Crea un spriteAnimated
		void CreateSprite(const Vector2 *position);

		// Mueve el spriteAnimated
		void MoveSpriteToPos(const Vector2 *newPosition);
		
		// actalizacion del sprite
		void UpdateAnimation(u16 time);

		void setFrame(u8 frame);

	private:	
	
		u8 *_durationPerFrame;
		
		u8 _currentDuration;

		u8 _currentFrame;
		u8 _maxFrame;
};



#endif
