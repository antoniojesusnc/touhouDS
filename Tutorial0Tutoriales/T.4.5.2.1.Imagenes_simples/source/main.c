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
	NF_Set2D(0, 0);				// Modo 2D_0 en ambas pantallas
	NF_Set2D(1, 0);

	// Inicializa los Sprites
	NF_InitSpriteBuffers();		// Inicializa los buffers para almacenar sprites y paletas
	NF_InitSpriteSys(0);		// Inicializa los sprites para la pantalla superior
	NF_InitSpriteSys(1);		// Inicializa los sprites para la pantalla inferior

	// Carga los archivos de sprites desde la FAT / NitroFS a la RAM
	NF_LoadSpriteGfx("sprite/bola", 1, 32, 32);			
	NF_LoadSpritePal("sprite/bola", 1);

	// Transfiere a la VRAM los sprites necesarios
	NF_VramSpriteGfx(0, 1, 0, true);
	NF_VramSpritePal(0, 1, 0);


	// Crea las bolas en la pantalla superior
	s16 bola_x = 20;
	s16 bola_y = 20;
	s8 bola_spx = 3;
	s8 bola_spy = 3;
	NF_CreateSprite(0, 0, 0, 0, bola_x, bola_y);
	
	// Bucle (repite para siempre)
	while(1) {


		// Mueve las bolas
		bola_x += bola_spx;
		if ((bola_x < 0) || (bola_x > 223)) bola_spx *= -1;
		bola_y += bola_spy;
		if ((bola_y < 0) || (bola_y > 159)) bola_spy *= -1;
		NF_MoveSprite(0, 0, bola_x, bola_y);
		

		// Actualiza el array de OAM
		NF_SpriteOamSet(0);

		swiWaitForVBlank();		// Espera al sincronismo vertical

		// Actualiza el OAM
		oamUpdate(&oamMain);
	
	}

	return 0; 

}
