



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
#include "Scene.h"


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
	NF_InitSpriteSys(1);
	//NF_Init3dSpriteSys();

	// Init textBuffer
	//NF_InitTextSys(0);
	//NF_InitTextSys(1);

	// init buffers sound
	//NF_InitRawSoundBuffers();
	
	// initial Scene
	_curScene = NULL;
	_newScene = SIZE;
	/*
	_currentScene = MENU;
	_menu = new CMenu(this);
	*/
	

	

} // CEngine

// Destructor clase CEngine
CEngine::~CEngine(void) {
	delete _curScene;


} // ~ CEngine

/*
	Metodos de la clase "CEngine"
*/
void CEngine::ChangeScene(Scenes newScene){

	_newScene = newScene;
}

void CEngine::ExecuteChangeScene(){
	UnloadCurrentScene();

	_currentScene = _newScene;
	_newScene = SIZE;

	LoadNewScene();
} // ChangeScene

void CEngine::UnloadCurrentScene(){
	delete _curScene;
	
	swiWaitForVBlank();

	NF_ResetTiledBgBuffers();
	NF_ResetSpriteBuffers();
	NF_ResetRawSoundBuffers();

	NF_SetRootFolder("NITROFS");
	swiWaitForVBlank();
} // unloadCurrentScene

void CEngine::LoadNewScene(){

	switch(_currentScene){
		case MENU: _curScene = new CMenu(this);		
			break;
		case OPTION: _curScene = new COptions(this);		
			break;
		case ARCADE_BATTLE: _curScene = new CBattle(this);		
			break;
		case ARCADE_CHAR_SELECT: _curScene = new CCharacterSelector(this);		
			break;
		case VERSUS_BATTLE: _curScene = new CMenu(this);		
			break;
		case VERSUS_CHAR_SELECT: _curScene = new CMenu(this);		
			break;
	}
	_curScene->InitScene();

	swiWaitForVBlank();
} // LoadNextScene


void CEngine::InitEngine(){

	
	_input = CInputs::getInstance();
	_time = new CTime();
	
	//CDebug::getInstance();
	
	//consoleDemoInit();
	
	_currentScene = MENU;
	//_currentScene = ARCADE;
	
	LoadNewScene();
	
	
} // InitEngine


void CEngine::MainBucle(){
	
	while(1){
		
		_input->Update();
		_time->Update();
		
		_curScene->Update(CTime::deltaTime());

		// update textLayers
		//NF_UpdateTextLayers();
	
		// wait for Vsinc
		NF_SpriteOamSet(0);
		NF_SpriteOamSet(1);
	
		swiWaitForVBlank();		

		oamUpdate(&oamMain);
		oamUpdate(&oamSub);
		
		if(_newScene != SIZE){
			ExecuteChangeScene();
			swiWaitForVBlank();	
		}
	}
} // Update
