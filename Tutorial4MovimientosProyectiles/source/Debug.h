#ifndef __DEBUG_H__
#define __DEBUG_H__





/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/


// Includes propietarios NDS
#include <nds.h>
#include "Math.h"


// Defines
class CText;

// Clase CDebug
class CDebug {

	public:
		
		// Destructor
		~CDebug(void);

		//	Metodos
		void Update();
		
		int getIntSaved(){return _intSaved;}
		void setIntSaved(u8 var){_intSaved = var;}

		// singleton
		static CDebug* getInstance();
		

		void WriteText(const char* text);

		void WriteText(const char* text, u16 number);

		void WriteText(const char* text, double number);

		void WriteText(const char* text, Vector2 *vector);
	private:

		CText *_text;
		Vector2 *_position;
		int _intSaved;
		// singleton
		// private constructor
		CDebug();

		static CDebug *_instance;
		
};



#endif
