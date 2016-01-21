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

	NF_Set2D(0, 0);				// Modo 2D_0 en ambas pantallas
	NF_Set2D(1, 0);
	
	NF_InitTiledBgBuffers();	// Inicializa los buffers para almacenar fondos
	NF_InitTiledBgSys(0);		// Iniciliaza los fondos Tileados para la pantalla superior
	NF_InitTiledBgSys(1);		// Iniciliaza los fondos Tileados para la pantalla inferior
	
	NF_SetRootFolder("NITROFS");	// Define la carpeta ROOT para usar NITROFS

	// Carga los archivos de fondo desde la FAT / NitroFS a la RAM
	NF_LoadTiledBg("bg/layer3", "moon", 256, 256);		// Carga el fondo para la capa 3, pantalla inferior
	// archivo | nombre asignado al fondo | ancho | alto
	
	NF_CreateTiledBg(0, 3, "moon"); 
	
	// Bucle (repite para siempre)
	while(1) {
		
		
		
		swiWaitForVBlank();		// Espera al sincronismo vertical

	}

	return 0;

}
