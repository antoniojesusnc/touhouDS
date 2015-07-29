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
#include "Inputs.h"


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


		// Constructor de copia
		CSprite(CSprite &sprite);

		// Contructores
		CSprite(const char *sprite, u16 witdh, u16 height);
		
		// Constructor con paleta
		CSprite(const char *sprite,const char *palette, u16 witdh, u16 height);

		

		// Destructor
		virtual ~CSprite();

		void removeFromRam();

		void removeFromVRam(bool palette = true);

		void removeFromScreen();
		
		//	Metodos
		
		virtual u16 MoveSpriteToVRam(bool upScreen, bool palette, bool loadOnlyFirst = true);
		
		
		// Crea un sprite
		virtual void CreateSprite(Vector2 *position);

		// Mueve el sprite
		virtual void MoveSpriteToPos(Vector2 *newPosition);
		
		// volteo horizontal
		void FlipTo(CInputs::Direction direction);

		// Gets y sets
		u8 getIdRam(){return _idRam;}
		u8 getIdVRam(){return _idVRam;}
		u8 getIdScreen(){return _idScreen;}
		u8 getScreen(){return (_upScreen?0:1);}
		Vector2 *getPosition(){return _position;}
		CPalette* getPalette(){return _palette;}
		Vector2 *getSize(){return _size;}
		
		void setPalette(CPalette* palette){_palette = palette;}
		void setInVRam(bool inVram){_inVram = inVram;}

		void setIdVRam(u8 idVram){_idVRam = idVram;}
		void setUpScreen(bool upScreen){_upScreen = upScreen;}

		bool isUpScreen(){return _upScreen;}
		bool isInVRam(){return _inVram;}
		bool isflipped(){return _flipped;}
		
	protected:
		
		u8 _idRam;	// ID del sprite en Ram
		u8 _idVRam;	// ID del sprite en VRam
		u8 _idScreen;	// ID del sprite en VRam
		
		bool _upScreen;	// ID del sprite en VRam
		bool _inVram;
		bool _flipped;

		Vector2 *_size;

		CPalette* _palette;
		Vector2 *_position;
};



#endif
