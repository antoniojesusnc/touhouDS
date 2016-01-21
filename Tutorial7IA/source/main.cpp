
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
	
	
	// initialize el engine
	CEngine *engine = new CEngine();

	engine->InitEngine();
	
	engine->MainBucle();
	

	swiWaitForVBlank();		
	// Devuelve 0
	return 0;

}

