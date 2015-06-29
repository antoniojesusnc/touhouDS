



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
#include "Inputs.h"

#include "Debug.h"
#include "Time.h"

/*
	Metodos de la clase "CEngine"
*/

// Contructor clase CEngine
CEngine::CEngine(){

	NF_SetRootFolder("NITROFS");	
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

	// init buffer for sprite and palletes
	NF_InitSpriteBuffers();
	// init sisrym for 3d
	NF_InitSpriteSys(0,128);
	NF_InitSpriteSys(1);//,128);
	//NF_Init3dSpriteSys();

	// Init textBuffer
	NF_InitTextSys(0);
	NF_InitTextSys(1);

	// init buffers sound
	//NF_InitRawSoundBuffers();
	
	// initial Scene
	_arcade = NULL;
	_menu = NULL;
	/*
	_currentScene = MENU;
	_menu = new CMenu(this);
	*/
	

	

} // CEngine

// Destructor clase CEngine
CEngine::~CEngine(void) {
	if(_menu)
		delete _menu;

	if(_arcade)
		delete _arcade;

	NF_ResetSpriteBuffers();

} // ~ CEngine

/*
	Metodos de la clase "CEngine"
*/
void CEngine::ChangeScene(Scenes newScene){

	UnloadCurrentScene();

	_currentScene = newScene;
	
	LoadNewScene();
} // ChangeScene

void CEngine::UnloadCurrentScene(){
	switch(_currentScene){
		case MENU: 
			delete _menu;
			_menu = NULL;
			break;
		case ARCADE: 
			delete _arcade;
			_arcade = NULL;
			break;
		case VERSUS: 
			break;
		case OPTION: 
			break;
	}
	
	swiWaitForVBlank();

	NF_ResetSpriteBuffers();
	NF_ResetTiledBgBuffers();
	NF_ResetRawSoundBuffers();
	NF_VramSpriteGfxDefrag(0);
	NF_VramSpriteGfxDefrag(1);

	swiWaitForVBlank();
} // unloadCurrentScene

void CEngine::LoadNewScene(){
	switch(_currentScene){
		case MENU: 
			_menu = new CMenu(this);
			_menu->InitMenu();
			break;
		case ARCADE: 
			_arcade = new CBattle(this);
			_arcade->InitBattle();
			break;
		case VERSUS: 
			break;
		case OPTION: 
			break;
	}
	swiWaitForVBlank();
} // LoadNextScene


void CEngine::InitEngine(){

	
	_input = CInputs::getInstance();
	_time = new CTime();
	
	CDebug::getInstance();
	
	
	
	_currentScene = ARCADE;
	
	LoadNewScene();
	
	//CXMLParser *data = new CXMLParser("demo");
} // InitEngine


void CEngine::MainBucle(){
	
	while(1){
		
		_input->Update();
		_time->Update();
		
		switch(_currentScene){
			case MENU: _menu->Update(CTime::deltaTime());
				break;
			case ARCADE: _arcade->Update(CTime::deltaTime());
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
		
	}
} // Update
