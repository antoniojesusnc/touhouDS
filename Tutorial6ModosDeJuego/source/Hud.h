#ifndef __HUD_H__
#define __HUD_H__





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
class CSpriteAnimated;
class CCharacter;
class CButton;
class CSprite;


// Clase CHud
class CHud {

	public:
				
		// Contructores
		CHud();
		
		// Destructor
		~CHud(void);

		

		//	Metodos
		void InitHud(CCharacter * player1, CCharacter * player2, u8 initialTime);

		void Update(CCharacter * player1, CCharacter * player2, u8 time);
		

		void ShowPause(bool pause);
		void UpdatePause();

		u8 getButtonPressed(){return _buttonPressed;}

	private:
		
		CSpriteAnimated *_healthBarPlayer1;
		CSpriteAnimated *_healthBarPlayer2;
		CSpriteAnimated *_timeTems;
		CSpriteAnimated *_timeUnits;

		u8 temp1;
		u8 temp2;

		// Pause menu
		CSprite *_pauseBackground;
		CSprite *_pauseText;
		CButton *_pauseResumeButton;
		CButton *_pauseExitButton;
		u8 _buttonPressed;

		// victory and Loose menu
		CSprite *_victoryText;
		CSprite *_looseText;

};



#endif
