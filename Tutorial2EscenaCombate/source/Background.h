#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__





/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/


// Includes propietarios NDS
#include <nds.h>
#include "Math.h"


// Defines


// Clase CBackground
class CBackground {

	public:
		
		static u8 MAX_LAYER_BACKGROUND;

		static u8 Layer;

		static void ResetLayer(){Layer = MAX_LAYER_BACKGROUND-1;}
		// Contructores
		CBackground(const char *background, u16 witdh, u16 height);

		// Destructor
		~CBackground(void);

		
		//	Metodos
		// Crea un background
		u8 CreateBackground(bool upScreen = false);

		// Mueve el background
		void MoveBackgroundOffset(const Vector2 &offset);
		
		// Gets y sets
		const char* getName(){return _name;}
		u8 getLayer(){return _layer;}
		u8 getScreen(){return (_upScreen?0:1);}
		bool isUpScreen(){return _upScreen;}
		Vector2* getPosition(){return _position;}
	
		
	private:
		
		char _name[50];
		u8 _layer;
		bool _upScreen;
		Vector2 *_position;	
};



#endif
