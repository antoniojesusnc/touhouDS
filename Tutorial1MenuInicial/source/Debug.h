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
		

		// singleton
		static CDebug* getInstance();
		

		void WriteText(const char* text);

		void WriteText(const char* text, u16 number);

		void WriteText(const char* text, Vector2 *vector);
	private:

		
		
		CText *_text;

		// singleton
		// private constructor
		CDebug();

		static CDebug *_instance;
};



#endif
