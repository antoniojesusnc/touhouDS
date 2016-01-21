#ifndef __FSMSTATE_H__
#define __FSMSTATE_H__





/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/


// Includes propietarios NDS
#include <nds.h>

class CCharacter;
class CFSMStateTransition;

// Clase CFSMState
class CFSMState {

	public:
				
		// Contructores
		CFSMState(CCharacter *player, CCharacter *enemy);
		// Destructor
		~CFSMState(void);

		virtual void Enter(){};
		virtual void Update(float time){};
		virtual void Exit(){};
		CFSMStateTransition **transitions;
		
	private:

		CCharacter *_player;
		CCharacter *_enemy;
};



#endif
