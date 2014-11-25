



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
#include "Engine.h"
/*
	Metodos de la clase "CEngine"
*/

// Contructor clase CEngine
CEngine::CEngine(){

	// 3d up screen
	//NF_Set3D(0,0);
	NF_Set2D(0,0);
	// 2d down screen
	NF_Set2D(1,0);

	// init buffer for bg
	NF_InitTiledBgBuffers();
	// init tiled bg
	NF_InitTiledBgSys(0);
	NF_InitTiledBgSys(1);

	// Init textBuffer
	NF_InitTextSys(0);
	NF_InitTextSys(1);

	// init buffer for sprite and palletes
	NF_InitSpriteBuffers();
	// init sisrym for 3d
	NF_Init3dSpriteSys();

	
	

	_menu = new CMenu(this);
} // CEngine

// Destructor clase CEngine
CEngine::~CEngine(void) {
}

/*
	Metodos de la clase "CEngine"
*/
void CEngine::ChangeScene(Scenes newScene){

	
} // ChangeScene

// Mueve las bolas
void CEngine::Update(){
	
	// update textLayers
	NF_UpdateTextLayers();

	// wait for Vsinc
	swiWaitForVBlank();
} // Update
