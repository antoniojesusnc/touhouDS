#ifndef __CHARACTER_SELECTOR_H__
#define __CHARACTER_SELECTOR_H__





/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/


// Includes propietarios NDS
#include <nds.h>
#include "Math.h"
#include "Scene.h"


// Defines
class CScene;
class CButton;
class CSpriteAnimated;

// Clase CCharacterSelector
class CCharacterSelector : public CScene {

	public:
				
		// Contructores
		CCharacterSelector(CEngine* engine);
		
		// Destructor
		~CCharacterSelector(void);

		

		//	Metodos
		void InitScene();

		void Update(vfloat32 time);

		
	private:

		void selectCharacter(u8 idCharacter);
		void selectScenario(u8 idScenario);
		


		//CSprite *_genericSprite;
		//CText *_genericText;

		CSpriteAnimated *_characters[4];

		CSpriteAnimated *_character1;
		CSpriteAnimated *_character2;


		CButton* _backButton;
		CButton* _startButton;

		CButton *_characterButtons[4];
		CButton *_scenarioButtons[4];

		bool _allSelected;
};



#endif
