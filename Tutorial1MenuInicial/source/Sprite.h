#ifndef __SPRITE_H__
#define __SPRITE_H__





/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/




// Includes propietarios NDS
#include <nds.h>
#include "Math.h"
#include "Palette.h"


// Defines


// Clase CSprite
class CSprite {

	public:
		
		static u8 MAX_ID_SPRITE_RAM ;
		static u8 MAX_ID_SPRITE_VRAM ;
		static u8 MAX_ID_SPRITE_SCREEN ;

		static u8 IdRam;
		static u8 IdVRam;
		static u8 IdScreen;

		// Contructores
		CSprite(const char *sprite, u16 witdh, u16 height);
		
		// Constructor con paleta
		CSprite(const char *sprite,const char *palette, u16 witdh, u16 height);

		// Destructor
		~CSprite(void);

		
		//	Metodos
		
		u16 MoveSpriteToVRam(bool upScreen, bool palette);
		
		
		// Crea un sprite
		void CreateSprite(const Vector2 *position);

		// Mueve el sprite
		void MoveSpriteToPos(const Vector2 *newPosition);
		
		// Gets y sets
		u8 getIdRam(){return _idRam;}
		u8 getIdVRam(){return _idVRam;}
		u8 getIdScreen(){return _idScreen;}
		u8 getScreen(){return (_upScreen?0:1);}
		Vector2 *getPosition(){return _position;}
		CPalette* getPalette(){return _palette;}
		Vector2 *getSize(){return _size;}
		
		void setPalette(const CPalette& palette){_palette = new CPalette(palette);}
		bool isUpScreen(){return _upScreen;}
		bool isInVRam(){return _inVram;}
		
	private:
		
		u8 _idRam;	// ID del sprite en Ram
		u8 _idVRam;	// ID del sprite en VRam
		u8 _idScreen;	// ID del sprite en VRam
		bool _upScreen;	// ID del sprite en VRam

		bool _inVram;
		Vector2 *_size;

		CPalette* _palette;
		Vector2 *_position;
	
	
};



#endif
