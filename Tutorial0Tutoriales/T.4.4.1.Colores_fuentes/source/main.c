/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/

// Includes C
#include <stdio.h>

// Includes propietarios NDS
#include <nds.h>

// Includes librerias propias
#include <nf_lib.h>





/*
-------------------------------------------------
	Main() - Bloque general del programa
-------------------------------------------------
*/

int main(int argc, char **argv) {

	consoleDemoInit();		// Inicializa la consola de texto
	consoleClear();			// Borra la pantalla
	setBrightness(3, 0);	// Restaura el brillo

	NF_InitTiledBgBuffers();	// Inicializa los buffers para almacenar fondos
	NF_InitTiledBgSys(1);		// Iniciliaza los fondos Tileados para la pantalla inferior
	
	NF_SetRootFolder("NITROFS");	// Define la carpeta ROOT para usar NITROFS
	
	NF_InitTextSys(1);
	
	NF_LoadTextFont("fnt/default", "normal", 256, 256, 0);	// Carga la seccion "normal" de la fuente, tamaño del mapa 256x256
	
	
	NF_CreateTextLayer(1, 0, 0, "normal"); 	// crea una capa que contendra el texto
									// 0,1 pantalla | id de la capa | 
									// rotacion (0 ninguna, 1 derecha, 2 izquierda) | nombre de la fuente
	
	NF_DefineTextColor(1, 0, 0, 31, 0, 0);

	NF_WriteText(1, 0, 1, 1, "Hola Mundo!\n Hello World!"); 
	
	
	
	NF_SetTextColor(1, 0, 0);
	
	NF_UpdateTextLayers();
	
	// Bucle (repite para siempre)
	while(1) {
		
		
		
		swiWaitForVBlank();		// Espera al sincronismo vertical

	}

	return 0;

}
