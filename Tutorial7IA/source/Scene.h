#ifndef __SCENE_H__
#define __SCENE_H__





/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/


// Includes propietarios NDS
#include <nds.h>

// Defines
class CEngine;
class CBackground;

// Clase CScene
class CScene {

	public:
				
		// Contructores
		CScene(CEngine* engine);
		
		// Destructor
		virtual ~CScene(void);

		

		//	Metodos
		virtual void InitScene() = 0;

		virtual void Update(vfloat32 time) = 0;

		
	protected:
		
		CBackground *_topBackground;
		CBackground *_botBackground;


		//CSprite *_genericSprite;
		//CText *_genericText;

		CEngine* _engine;
};



#endif
