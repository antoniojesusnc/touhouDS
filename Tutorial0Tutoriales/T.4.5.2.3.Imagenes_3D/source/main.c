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

#define SPRITEMAXNUM 1

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

	// Inicializa el motor 3D
	NF_Set3D(0, 0);				// Modo 3D_0 en la pantalla superior

	// Inicializa el motor 2D
	NF_Set2D(1, 0);				// Modo 2D_0 en la pantalla inferior

	// Inicializa los fondos tileados
	NF_InitTiledBgBuffers();	// Inicializa los buffers para almacenar fondos
	NF_InitTiledBgSys(0);		// Inicializa los fondos Tileados para la pantalla superior
	NF_InitTiledBgSys(1);		// Inicializa los fondos Tileados para la pantalla inferior

	// Inicializa los buffers de los Sprites
	NF_InitSpriteBuffers();		// Inicializa los buffers para almacenar sprites y paletas

	// Inicializa el sistema de Sprites en 3D y OpenGL
	NF_Init3dSpriteSys();

	// Carga los fondos tileados
	NF_LoadTiledBg("bg/nfl", "nfl", 256, 256);
	NF_LoadTiledBg("bg/bg3", "bg3", 256, 256);

	// Carga los graficos de los Sprites
	NF_LoadSpriteGfx("sprite/numbers", 0, 16, 16);
	
	NF_LoadSpritePal("sprite/numbers", 0);


	// Manda los graficos y paletas a la VRAM
	NF_Vram3dSpriteGfx(0, 0, true);
	NF_Vram3dSpritePal(0, 0);

	// Crea los fondos en ambas pantallas
	NF_CreateTiledBg(0, 3, "bg3");
	NF_CreateTiledBg(1, 3, "nfl");


	// Variables
	s16 x = 50;
	s16 y = 50;
	s8 ix = 2;
	s8 iy = 2;
	u16 timer = 0;
	u8 frame = 0;
	
	// Crea los Sprites 3D
	NF_Create3dSprite(0, 0, 0, x, y);
	NF_Set3dSpriteFrame(0, frame);
	

	// Y ordenalos en la cola segun su ID (El mas bajo tiene prioridad)
	NF_Sort3dSprites();

	// Bucle (repite para siempre)
	while(1) {

		// Mueve todos los Sprites
		x += ix;
		if ((x < 0) || (x > (255 - NF_3DSPRITE[0].width))) ix = -ix;
		y += iy;
		if ((y < 0) || (y > (191 - NF_3DSPRITE[0].height))) iy = -iy;
		timer ++;
		if (timer > 60) {
			timer = 0;
			frame ++;
			if (frame > 9) frame = 0;
		}
		NF_Move3dSprite(0, x, y);
		NF_Set3dSpriteFrame(0, frame);
		

		// Dibuja los 3D Sprites
		NF_Draw3dSprites();

		// Actualiza la escena 3D, si no lo haces, no se mostrara en pantalla
		glFlush(0);

		// Espera al sincronismo vertical
		swiWaitForVBlank();

		// Actualiza las texturas de los 3D Sprites animados con KEEPFRAMES == TRUE
		NF_Update3dSpritesGfx();


	}

	return 0;

}
