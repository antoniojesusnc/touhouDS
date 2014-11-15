#ifndef __PALETTE_H__
#define __PALETTE_H__




/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/



// Includes propietarios NDS
#include <nds.h>

// Defines


// Clase CPalette
class CPalette {

	public:
		
		static u8 MAX_ID_PALETTE_RAM;
		static u8 MAX_ID_PALETTE_VRAM;

		static u8 IdRam;
		static u8 IdVRam;

		// Contructores
		CPalette(char *palette);
		
		// Destructor
		~CPalette(void);

		
		//	Metodos
		
		u8 MovePaletteToVRam(bool upScreen);
		
		// Gets y sets
		u8 getIdRam(){return _idRam;}
		u8 getIdVRam(){return _idVRam;}
		u8 getScreen(){return (_upScreen?1:0);}
		bool isUpScreen(){return _upScreen;}
		bool isInVRam(){return _inVram;}	
		
	private:
		
		u8 _idRam;	// ID del palette en Ram
		u8 _idVRam;	// ID del palette en VRam
		bool _upScreen;

		bool _inVram;	
	
};



#endif
