#ifndef __BATTLE_H__
#define __BATTLE_H__





/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/


// Includes propietarios NDS
#include <nds.h>
#include "Math.h"
#include "Engine.h"


// Defines
class CEngine;
class CButton;
class CText;
class CSprite;
class CBackground;

class CCharacter;

// Clase CBattle
class CBattle {

	public:
				
		// Contructores
		CBattle(CEngine* engine);
		
		// Destructor
		~CBattle(void);

		

		//	Metodos
		void InitBattle();

		void Update(u16 time);

		
	private:
		
		CBackground *_topBackground;
		CBackground *_botBackground;

		CText *_time;
		CCharacter *_characters[2];

		//CSprite *_genericSprite;
		//CText *_genericText;

		CEngine* _engine;
};



#endif
