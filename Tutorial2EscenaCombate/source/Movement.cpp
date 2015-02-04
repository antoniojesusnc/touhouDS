

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
#include "Movement.h"

// static variables
/*
	Metodos de la clase "CMovement"
*/

// Contructor clase CMovement
CMovement::CMovement(const char *movement) {
	
	_activated = false;
} // CMovement

// Destructor clase CMovement
CMovement::~CMovement(void) {
} // ~CMovement

/*
	Metodos de la clase "CMovement"
*/

void CMovement::Init() {
	
} // Init

void CMovement::StartMovement() {
	_activated = true;
} // StartMovement

void CMovement::CancelMovement() {
	_activated = false;
} // CancelMovement

void CMovement::UpdateMovement(vfloat32 time) {

} // UpdateMovement