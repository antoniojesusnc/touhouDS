



/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/

// Includes C/C++
#include <stdio.h>

// Includes propietarios NDS
#include <nds.h>

// Includes librerias propias
#include <nf_lib.h>

// Includes del programa

#include "FSMStateTransition.h"
#include "FSMState.h"
#include "Inputs.h"
/*
	Metodos de la clase "CFSMStateTransition"
*/


// Contructor clase CFSMStateTransition
CFSMStateTransition::CFSMStateTransition(CFSMState *nextState) {
	_nextState = nextState;
} // CFSMStateTransition


// Destructor clase CFSMStateTransition
CFSMStateTransition::~CFSMStateTransition(void) {

} // ~CFSMStateTransition