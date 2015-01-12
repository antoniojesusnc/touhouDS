
/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/


// Includes del programa


// Includes C/C++
#include <stdio.h>
#include <vector>

// Includes propietarios NDS
#include <nds.h>

// Includes librerias propias
#include <nf_lib.h>


#include "Includes.h"
//#include "Scenes/MainEngine.h"



/*
-------------------------------------------------
	Main() - Bloque general del programa
-------------------------------------------------
*/

int main(int argc, char **argv) {


	// Pantalla de espera inicializando NitroFS
	NF_Set2D(0, 0);
	NF_Set2D(1, 0);	
	consoleDemoInit();
	iprintf("\n NitroFS init. Please wait.\n\n");
	iprintf(" Iniciando NitroFS,\n por favor, espere.\n\n");
	swiWaitForVBlank();
	
	

	// Define el ROOT e inicializa el sistema de archivos
	NF_SetRootFolder("NITROFS");	// Define la carpeta ROOT para usar NITROFS

	
	
	// initialize el engine
	CEngine *engine = new CEngine();
	CInput *input = CInput::getInstance();

	//just in case
	CDebug::getInstance();

	engine->InitEngine();

	/*
NF_LoadSpriteGfx("sprite/bola", 10, 32, 32);			// Bola azul
NF_LoadSpritePal("sprite/bola", 10);

NF_VramSpriteGfx(1, 10, 10, false);	// Personaje, copia todos los frames a la VRAM
NF_VramSpritePal(1, 10, 10);

NF_CreateSprite(1, 10, 10, 10, 0, 0);
*/
	// Bucle (repite para siempre)
	while(1) {

		input->Update();
		engine->Update();

		swiWaitForVBlank();
	}

	

	// Devuelve 0
	return 0;

}

