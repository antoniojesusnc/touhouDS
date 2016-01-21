

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
#include "palette.h"

// static variables

u8 CPalette::MAX_ID_PALETTE_RAM = 15;
u8 CPalette::MAX_ID_PALETTE_VRAM = 15;
		
u8 CPalette::IdRam = 1;
u8 CPalette::IdVRam = 1;

std::set<u8> CPalette::ALLRamId;
std::set<u8> CPalette::ALLVRamId;

/*
	Metodos de la clase "CPalette"
*/

// Contructor clase CPalette
CPalette::CPalette(const char *palette) {
	
	_idRam = CPalette::IdRam++;
	while(ALLRamId.find(_idRam) != ALLRamId.end()) {
		if(CPalette::IdRam >= CPalette::MAX_ID_PALETTE_RAM){
			CPalette::IdRam = 1;
		}
		_idRam = CPalette::IdRam++;
	}
	ALLRamId.insert(_idRam);

	NF_LoadSpritePal(palette, _idRam);
	
	_inVram = false;
	
	if(CPalette::IdRam >= MAX_ID_PALETTE_RAM){
		CPalette::IdRam = 1;
	}
}

// Destructor clase CPalette
CPalette::~CPalette(void) {
	//NF_UnloadExBgPal(getIdRam());
	removeFromRam();
	removeFromVRam();
	if(getIdRam() > 0){
		NF_UnloadSpritePal(getIdRam()); // delete from ram
		_idRam = 0;
	}
} // ~CPalette

void CPalette::removeFromRam(){	
	ALLRamId.erase (ALLRamId.find(getIdRam()));
} // removeFromRam

void CPalette::removeFromVRam(){
	if(!isInVRam())
		return;
	
	ALLVRamId.erase (ALLVRamId.find(getIdVRam()));
} // removeFromVRam

// Crea el puntero externo a la clase
CPalette *Palette;



/*
	Metodos de la clase "CPalette"
*/

u8 CPalette::MovePaletteToVRam(bool upScreen){
	
	_upScreen = upScreen;
	_idVRam = CPalette::IdVRam++;	
	while(ALLVRamId.find(_idVRam) != ALLVRamId.end()){
		if(CPalette::IdVRam >= CPalette::MAX_ID_PALETTE_VRAM){
			CPalette::IdVRam = 1;
		}
		_idVRam = CPalette::IdVRam++;
	}
	ALLVRamId.insert(_idVRam);

	NF_VramSpritePal(getScreen(), _idRam, _idVRam);
	
	_inVram = true;
	
	if(CPalette::IdVRam >= MAX_ID_PALETTE_VRAM){
		CPalette::IdVRam = 0;
	}
	
	return _idVRam;
}
