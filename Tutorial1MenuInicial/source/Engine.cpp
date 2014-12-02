



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


// debug
#include "Text.h"
#include "Input.h"

#include "Debug.h"
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
	NF_InitSpriteSys(0);
	NF_InitSpriteSys(1);
	//NF_Init3dSpriteSys();

	// init buffers sound
	//NF_InitRawSoundBuffers();
	
	_currentScene = MENU;

	_menu = new CMenu(this);
} // CEngine

// Destructor clase CEngine
CEngine::~CEngine(void) {
	delete _menu;

	NF_ResetSpriteBuffers();

} // ~ CEngine

/*
	Metodos de la clase "CEngine"
*/
void CEngine::ChangeScene(Scenes newScene){
	
	switch(_currentScene){
		case MENU: delete _menu;
			break;
		case ARCADE: 
			break;
		case VERSUS: 
			break;
		case OPTION: 
			break;
	}
	
	_currentScene = newScene;
	
	/*
	NF_ResetSpriteBuffers();
	NF_ResetTiledBgBuffers();
	NF_ResetRawSoundBuffers();
	*/
	switch(_currentScene){
		case MENU: _menu->InitMenu();
			break;
		case ARCADE: 
			break;
		case VERSUS: 
			break;
		case OPTION: 
			break;
	}
} // ChangeScene

void CEngine::InitEngine(){

	_currentScene = MENU;

	_menu->InitMenu();

	
} // InitEngine


void CEngine::Update(){
	
	switch(_currentScene){
		case MENU: _menu->Update();
			break;
		case ARCADE: 
			break;
		case VERSUS: 
			break;
		case OPTION: 
			break;
	}
	


	// update textLayers
	NF_UpdateTextLayers();

	// wait for Vsinc
	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);

	swiWaitForVBlank();		

	oamUpdate(&oamMain);
	oamUpdate(&oamSub);
} // Update
