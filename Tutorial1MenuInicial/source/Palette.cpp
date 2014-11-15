/*
-------------------------------------------------

	Ejemplo de gestion dinamica de objetos

	Clase de los palettes de las bolas

	Requiere DevkitARM
	Requiere NightFox's Lib

	Codigo por NightFox
	http://www.nightfoxandco.com

	(c)2013 NightFox & Co.

-------------------------------------------------
*/



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

u8 CPalette::MAX_ID_PALETTE_RAM;
u8 CPalette::MAX_ID_PALETTE_VRAM;
		
u8 CPalette::IdRam = 0;
u8 CPalette::IdVRam = 0;

/*
	Metodos de la clase "CPalette"
*/

// Contructor clase CPalette
CPalette::CPalette(char *palette) {
	
	_idRam = ++IdRam;
	NF_LoadSpritePal(palette, _idRam);
	
	_inVram = false;
	
	if(IdRam >= MAX_ID_PALETTE_RAM){
		IdRam = 0;
	}
}

// Destructor clase CPalette
CPalette::~CPalette(void) {
}

// Crea el puntero externo a la clase
CPalette *Palette;



/*
	Metodos de la clase "CPalette"
*/

u8 CPalette::MovePaletteToVRam(bool upScreen){
	_idVRam = ++IdVRam;
	_upScreen = upScreen;
	
	NF_VramSpritePal(getScreen(), _idRam, _idVRam);
	
	_inVram = true;
	
	if(IdVRam >= MAX_ID_PALETTE_VRAM){
		IdVRam = 0;
	}
	
	return _idVRam;
}
