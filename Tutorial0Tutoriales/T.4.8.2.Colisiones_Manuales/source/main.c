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
	s16 bola_x[2] = {20, 70};
	s16 bola_y[2] = {20, 20};
	s8 bola_spx[2] = {2, 1};
	s8 bola_spy[2] = {2, 1};
	s8 bola_w[2] = {31, 31};
	s8 bola_h[2] = {31, 31};

	NF_CreateSprite(0, 0, 0, 0, bola_x[0], bola_y[0]);
	NF_CreateSprite(0, 1, 0, 0, bola_x[1], bola_y[1]);
	
	// Bucle (repite para siempre)
	u8 i;
	u8 otra_bola;
	while(1) {

		
		
		for(i = 0; i < 2; ++i){
			// Mueve las bolas
			bola_x[i] += bola_spx[i];
			bola_y[i] += bola_spy[i];
			
			if ((bola_x[i] < 0) || (bola_x[i] > 223)) bola_spx[i] *= -1;
			if ((bola_y[i] < 0) || (bola_y[i] > 159)) bola_spy[i] *= -1;
			
			otra_bola = i==0?1:0;
			if( (bola_x[i] <= bola_x[otra_bola] + bola_w[otra_bola]) &&
				(bola_x[i]+bola_w[i] >= bola_x[otra_bola]) && 
				(bola_y[i] <= bola_y[otra_bola] + bola_h[otra_bola]) &&
				(bola_y[i]+bola_h[i] >= bola_y[otra_bola]) ){
				
				
				
				s16 restx = (bola_x[i] - bola_x[otra_bola]);
				s16 resty = (bola_y[i] - bola_y[otra_bola]);
				if(restx < 0) restx *= -1;
				if(resty < 0) resty *= -1;
				
				s16 rest = restx - resty;
				
				if(rest <= 2 && rest >= -2){
					bola_spx[i] *= -1;
					bola_spx[otra_bola] *= -1;
					bola_spy[i] *= -1;
					bola_spy[otra_bola] *= -1;
				}else{
					if(rest > 2){
						bola_spx[i] *= -1;
						bola_spx[otra_bola] *= -1;
					}else{
						bola_spy[i] *= -1;
						bola_spy[otra_bola] *= -1;
					}
				}
							
				//NF_MoveSprite(0, i, bola_x[i], bola_y[i]);	
				//NF_MoveSprite(0, i, bola_x[otra_bola], bola_y[otra_bola]);
				//i = 2;	
			}
			
			
			
				
			
			NF_MoveSprite(0, i, bola_x[i], bola_y[i]);
			
		}		

		// Actualiza el array de OAM
		NF_SpriteOamSet(0);

		swiWaitForVBlank();		// Espera al sincronismo vertical

		// Actualiza el OAM
		oamUpdate(&oamMain);
	
	}

	return 0; 

}
