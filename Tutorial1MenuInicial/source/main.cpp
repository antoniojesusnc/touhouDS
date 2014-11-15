
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

/*
	// Pantalla de espera inicializando NitroFS
	NF_Set2D(0, 0);
	NF_Set2D(1, 0);	
	consoleDemoInit();
	iprintf("\n NitroFS init. Please wait.\n\n");
	iprintf(" Iniciando NitroFS,\n por favor, espere.\n\n");
	swiWaitForVBlank();
	consoleClear();
	*/

	// Define el ROOT e inicializa el sistema de archivos
	NF_SetRootFolder("NITROFS");	// Define la carpeta ROOT para usar NITROFS
	
	// initialize el engine
	CEngine *engine = new CEngine();

	// Debug por la consola
	iprintf("\n Hello World");
	
	// Bucle (repite para siempre)
	while(1) {

		
		engine->Update();

		swiWaitForVBlank();
	}

	

	// Devuelve 0
	return 0;

}

