



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

#include "FSMState.h"
#include "Inputs.h"
#include "Character.h"


/*
	Metodos de la clase "CFSMState"
*/


// Contructor clase CFSMState
CFSMState::CFSMState(CCharacter *player, CCharacter *enemy) {
	_player = player;
	_enemy = enemy;
} // CFSMState


// Destructor clase CFSMState
CFSMState::~CFSMState(void) {

} // ~CFSMState