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
#include "Background.h"


// Defines


// Clase CText
class CText {

	public:
		
		static u8 MAX_COLOR_TEXT;

		static u8 Color;

		// Contructores
		CText(const char *text, u16 witdh, u16 height);
		
		CText(CText &text);

		// Destructor
		~CText(void);

		//	Metodos
		// Crea un text
		u8 CreateLayer(bool upScreen = false);

		// Create color
		u8 CreateColor(u8 red, u8 green, u8 blue);

		// Escribe el text
		void WriteText(const Vector2 &newPosition, const char* text, ...);
		
		// Gets y sets
		const char* getName(){return _name;}
		u8 getLayer(){return _layer;}
		void setLayer(u8 layer){_layer = layer;}
		bool isLayerCreated(){return _layerCreated;}
		u8 getScreen(){return (_upScreen?0:1);}
		bool isUpScreen(){return _upScreen;}
		Vector2 getPosition(){return _position;}
		u8 getColor(){return _color;}
		void setColor(u8 newColor);

		
	private:
		
		const char* _name;
		bool _layerCreated;
		u8 _layer;
		bool _upScreen;
		Vector2 _position;

		// colors
		u8 _color;
};



#endif
