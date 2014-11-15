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

		// Contructores
		CBackground(char *background, u8 witdh, u8 height);

		// Destructor
		~CBackground(void);

		
		//	Metodos
		// Crea un background
		u8 CreateBackground(bool upScreen = false);

		// Mueve el background
		void MoveBackgroundToPos(Vector2 newPosition);
		
		// Gets y sets
		u8 getLayer(){return _layer;}
		u8 getScreen(){return (_upScreen?1:0);}
		bool isUpScreen(){return _upScreen;}
		Vector2 getPosition(){return _position;}
	
		
	private:
		
		char* _name;
		u8 _layer;
		bool _upScreen;
		Vector2 _position;	
};



#endif
