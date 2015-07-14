



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
#include "Scene.h"
#include "Background.h"
#include "Sprite.h"
#include "Text.h"
#include "Button.h"
#include "Inputs.h"

#include "Debug.h"

/*
	Metodos de la clase "CScene"
*/


// Contructor clase CScene
CScene::CScene(CEngine* engine)  {
	_engine = engine;

	_botBackground = NULL;
	_topBackground = NULL;
} // CScene

// Destructor clase CScene
CScene::~CScene(void) {
	delete _topBackground;
	delete _botBackground;
} // ~CScene

/*
	Metodos de la clase "CScene"
*/
