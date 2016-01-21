/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/

// Includes C
#include <stdio.h>
#include <string.h>
#include <unistd.h>

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

	// Pantalla de espera inicializando NitroFS
	NF_Set2D(0, 0);
	NF_Set2D(1, 0);	
	consoleDemoInit();
	
	swiWaitForVBlank();

	// Define el ROOT e inicializa el sistema de archivos
	NF_SetRootFolder("NITROFS");	// Define la carpeta ROOT para usar NITROFS

	// Inicializa el motor 2D en modo BITMAP
	NF_Set2D(0, 5);				// Modo 2D_5 en ambas pantallas
	NF_Set2D(1, 5);

	// Inicializa los fondos en modo "BITMAP"
	NF_InitBitmapBgSys(0, 1);
	NF_InitBitmapBgSys(1, 1);

	// Inicializa los buffers para guardar fondos en formato BITMAP
	NF_Init16bitsBgBuffers();

	// Inicializa el BackBuffer de 16 bits
	// Usalo solo una vez antes de habilitarlo
	NF_Init16bitsBackBuffer(1);

	// Habilita el backbuffer en la pantalla superior
	NF_Enable16bitsBackBuffer(1);

	// Carga el archivo BITMAP de imagen en formato RAW a la RAM
	NF_Load16bitsBg("bmp/bitmap16", 0);

	// Tranfiere la imagen a la VRAM de la pantalla superior
	NF_Copy16bitsBuffer(0, 0, 0);
	// Tranfiere la imagen al BackBuffer de la pantalla inferior
	NF_Copy16bitsBuffer(1, 1, 0);

	// Copia el contenido del Backbuffer a la VRAM
	NF_Flip16bitsBackBuffer(1);
	
	
	while (1) {
		// Sincronismo Vertical
		swiWaitForVBlank();

	}


	return 0; 

}
