#ifndef __FSMSTATE_TRANSITION_H__
#define __FSMSTATE_TRANSITION_H__





/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/


// Includes propietarios NDS
#include <nds.h>

class CCharacter;
class CFSMState;

// Clase CFSMStateTransition
class CFSMStateTransition {

	public:
				
		// Contructores
		CFSMStateTransition(CFSMState *nextState);
		// Destructor
		~CFSMStateTransition(void);

		virtual bool isValid(CCharacter *player, CCharacter *enemy){};
		virtual void Transition(){};
		
		CFSMState *getNextState(){return _nextState;};
	private:

		CFSMState *_nextState;
		
};



#endif
