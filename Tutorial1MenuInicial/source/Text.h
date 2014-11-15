#ifndef __TEXT_H__
#define __TEXT_H__





/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/


// Includes propietarios NDS
#include <nds.h>
#include "Math.h"


// Defines


// Clase CText
class CText {

	public:
		
		static u8 MAX_LAYER_TEXT;

		static u8 Layer;

		// Contructores
		CText(char *text, u8 witdh, u8 height);
		
		CText(CText &text);

		// Destructor
		~CText(void);

		
		//	Metodos
		// Crea un text
		u8 CreateLayer(bool upScreen = false);

		// Mueve el text
		void WriteText(Vector2 &newPosition, char* text, ...);
		
		// Gets y sets
		char* getName(){return _name;}
		u8 getLayer(){return _layer;}
		void setLayer(u8 layer){_layer = layer;}
		bool isLayerCreated(){return _layerCreated;}
		u8 getScreen(){return (_upScreen?1:0);}
		bool isUpScreen(){return _upScreen;}
		Vector2 getPosition(){return _position;}
	
		
	private:
		
		char* _name;
		bool _layerCreated;
		u8 _layer;
		bool _upScreen;
		Vector2 _position;	
};



#endif
