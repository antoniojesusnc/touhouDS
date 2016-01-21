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

char* keysToString(u16 key);

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
	

	NF_WriteText(1, 0, 1, 1, "Hola Mundo!\n Hello World!"); 
	
	NF_UpdateTextLayers();
	
	// Variable para la lectura del keypad
	u16 keys = 0;
	char mytext[32];
	
	// variable para detectar la pantalla tactil
	touchPosition touchscreen;
	// Bucle (repite para siempre)
	while(1) {
		
		// Lee el teclado
		scanKeys();
		keys = keysDown();
		
		
		stpcpy(mytext,keysToString(keys));
		//mytext = stpcpy(keysToString(keys),mytext);
		//sprintf(mytext,"Contador: %d", keys);
		NF_WriteText(1, 0, 1, 1, "Hola Mundo!\n Hello World!"); 
		NF_WriteText(1, 0, 1, 2, mytext); 
		
		keys = keysHeld();
		touchRead(&touchscreen); 
		
		if(keys == KEY_TOUCH){
			sprintf(mytext,"Posiciones: %d - %d  ", touchscreen.px, touchscreen.py);
			NF_WriteText(1, 0, 1, 3, mytext); 
		}
		
		NF_UpdateTextLayers();
		
		swiWaitForVBlank();		// Espera al sincronismo vertical

	}

	return 0;

}

char* keysToString(u16 key){
	if(key){
		switch(key){
			case KEY_A: return "A      ";
			case KEY_B: return "B      ";
			case KEY_X: return "X      ";
			case KEY_Y: return "Y      ";
			case KEY_DOWN: return "DOWN  ";
			case KEY_LEFT: return "LEFT ";
			case KEY_RIGHT: return "RIGHT  ";
			case KEY_UP: return "UP      ";
			case KEY_L: return "L      ";
			case KEY_R: return "R     ";
			case KEY_START: return "START   ";
			case KEY_SELECT: return "SELECT   ";
			case KEY_TOUCH: return "TOUCH   ";
		}
	}
	//return "Ninguna Tecla";
}
