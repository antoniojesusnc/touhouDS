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
class CCollision;


// Clase CBattle
class CBattle {

	public:
				
		// Contructores
		CBattle(CEngine* engine);
		
		// Destructor
		~CBattle(void);

		

		//	Metodos
		void InitBattle();

		void Update(vfloat32 time);


		CCharacter *getPlayerCharacter(u8 player){return _characters[player];}
		
	private:
		
		CBackground *_topBackground;
		CBackground *_botBackground;

		CText *_time;
		CCharacter *_characters[2];

		//CSprite *_genericSprite;
		//CText *_genericText;

		CEngine* _engine;

		CCollision *_collision;
};



#endif