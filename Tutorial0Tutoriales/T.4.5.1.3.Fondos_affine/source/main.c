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

	// Pantalla de espera inicializando NitroFS
	NF_Set2D(0, 0);
	NF_Set2D(1, 0);	
	consoleDemoInit();
	iprintf("\n NitroFS init. Please wait.\n\n");
	iprintf(" Iniciando NitroFS,\n por favor, espere.\n\n");
	swiWaitForVBlank();

	// Define el ROOT e inicializa el sistema de archivos
	NF_SetRootFolder("NITROFS");	// Define la carpeta ROOT para usar NITROFS

	// Inicializa el motor 2D
	NF_Set2D(0, 2);				// Modo 2D_2 en la pantalla superior
	NF_Set2D(1, 2);				// Modo 2D_2 en la pantalla inferior

	// Inicializa los fondos tileados
	NF_InitTiledBgBuffers();	// Inicializa los buffers para almacenar fondos
	NF_InitAffineBgSys(0);		// Inicializa los fondos affine para la pantalla superior
	NF_InitAffineBgSys(1);		// Iniciliaza los fondos affine para la pantalla inferior

	// Carga los archivos de fondo desde NitroFS a la RAM
	NF_LoadAffineBg("bg/waves512", "waves", 512, 512);		// Carga el fondo para la capa 3, pantalla superior
	NF_LoadAffineBg("bg/navygrid", "grid", 256, 256);		// Carga el fondo para la capa 2, pantalla superior
	NF_LoadAffineBg("bg/flag512", "flag", 512, 512);		// Carga el fondo para la capa 3, pantalla inferior

	// Crea los fondos de la pantalla Superior
	NF_CreateAffineBg(0, 3, "waves", 1);
	NF_CreateAffineBg(0, 2, "grid", 0);

	// Crea los fondos de la pantalla Inferior
	NF_CreateAffineBg(1, 3, "flag", 1);

	// Variable para la lectura del keypad
	u16 keys = 0;

	// Variables para el control de movimiento
	s32 x = 0;
	s32 y = 0;
	s32 angle = 0;
	s32 zoom = 256;
	u8 n = 0;


	// Bucle (repite para siempre)
	while(1) {

		// Lee el teclado
		scanKeys();
		keys = keysHeld();

		// Calcula el desplazamiento del centro
		if (keys & KEY_UP) y -= 2;
		if (y < 0) y = 0;
		if (keys & KEY_DOWN) y += 2;
		if (y > 512) y = 512;
		if (keys & KEY_LEFT) x -= 2;
		if (x < 0) x = 0;
		if (keys & KEY_RIGHT) x += 2;
		if (x > 512) x = 512;

		// Calcula el Zoom
		if (keys & KEY_A) zoom -= 2;
		if (zoom < 0) zoom = 0;
		if (keys & KEY_B) zoom += 2;
		if (zoom > 512) zoom = 512;

		// Calcula el angulo
		if (keys & KEY_X) angle -= 2;
		if (angle < 0) angle += 2048;
		if (keys & KEY_Y) angle += 2;
		if (angle > 2048) angle -= 2048;

		swiWaitForVBlank();				// Espera al sincronismo vertical

		// Modifica los parametros del fondo Affine
		for (n = 0; n < 2; n ++) {
			// Zoom
			NF_AffineBgTransform(n, 3, zoom, zoom, 0, 0);
			// Posicion del centro
			NF_AffineBgCenter(n, 3, x, y);
			// Rotacion
			NF_AffineBgMove(n, 3, 0, 0, angle);
		}

	}

	return 0; 

}
