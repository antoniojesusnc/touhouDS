#ifndef __OPTIONS_H__
#define __OPTIONS_H__





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
class CText;
class CSprite;
class CBackground;

// Clase COptions
class COptions : public CScene {

	public:
				
		// Contructores
		COptions(CEngine* engine);
		
		// Destructor
		~COptions(void);

		

		//	Metodos
		void InitScene();

		void Update(vfloat32 time);

		
	private:
		CButton* _backButton;

		CButton* _brightnessButton;

		CButton* _30SecondButton;
		CButton* _60SecondButton;
		CButton* _90SecondButton;
};



#endif
