



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
#include "Inputs.h"


/*
	Metodos de la clase "CInput"
*/

// Contructor clase CInput
CInputs::CInputs() {
	_keys = 0;
} // CInput

// Destructor clase CInput
CInputs::~CInputs(void) {
	delete &_touchPos;
	delete &_touchScreen;
} // ~CInput

CInputs *CInputs::_instance = 0;

CInputs* CInputs::getInstance(){
	if(!_instance){
		_instance = new CInputs();
	}
	return _instance;
} // getPtr

/*
	Metodos de la clase "CInput"
*/
void CInputs::checkDirections(){
	resetDirections();

	if(_keys & KEY_RIGHT){
		if(_keys & KEY_UP){
			_directions[_directionIndex] = DirFrontUp;
			incrementDirectionIndex();
		}else if(_keys & KEY_DOWN){
			_directions[_directionIndex] = DirFrontDown;
			incrementDirectionIndex();
		}else{
			_directions[_directionIndex] = DirFront;
			incrementDirectionIndex();
		}
	}else if(_keys & KEY_LEFT){
		if(_keys & KEY_UP){
			_directions[_directionIndex] = DirBackUp;
			incrementDirectionIndex();
		}else if(_keys & KEY_DOWN){
			_directions[_directionIndex] = DirBackDown;
			incrementDirectionIndex();
		}else{
			_directions[_directionIndex] = DirBack;
			incrementDirectionIndex();
		}
	} else if(_keys & KEY_UP){
		_directions[_directionIndex] = DirUp;
		incrementDirectionIndex();
	} else if(_keys & KEY_DOWN){
		_directions[_directionIndex] = DirDown;
		incrementDirectionIndex();
	} else {
		_directions[_directionIndex] = DirStand;
		incrementDirectionIndex();
	}
	
} // checkDirections

void CInputs::incrementDirectionIndex(){
	++_directionIndex;
	if(_directionIndex > 2){
		_directionIndex = 0;
	}
} // incrementDirectionIndex

void CInputs::resetDirections(){
	for(vu8 i = 0; i < 2; ++i){
		_directions[_directionIndex] = DirStand;
	}
	_directionIndex = 0;
} // incrementDirectionIndex

void CInputs::checkCombos(){
	
	if(_keys & KEY_B){
		_commnads[_commnadsIndex] = (Commands)( ((u16)_directions[0])+(9*1) );
	} else if(_keys & KEY_A){
		_commnads[_commnadsIndex] = (Commands)( ((u16)_directions[0])+(9*2) );
	} else if(_keys & KEY_Y){
		_commnads[_commnadsIndex] = (Commands)( ((u16)_directions[0])+(9*3) );
	} else if(_keys & KEY_X){
		_commnads[_commnadsIndex] = (Commands)( ((u16)_directions[0])+(9*4) );
	} else {
		_commnads[_commnadsIndex] = (Commands)( ((u16)_directions[0])+(9*0) );
	}

} // checkCombos

void CInputs::incrementInputsIndex(){
	++_commnadsIndex;
	if(_commnadsIndex > 4){
		_commnadsIndex = 0;
	}
} // incrementInputsIndex
		

		
void CInputs::Update(){

	checkDirections();
	checkCombos();

	scanKeys();
	//_keys = keysDown();
	

	_keys = keysHeld();

	touchRead(&_touchScreen);
	_touchPos.x = _touchScreen.px;
	_touchPos.y = _touchScreen.py;
	
	

	//_keys = keysUp();
	
	_keys = keysCurrent ();
	
	
} // Update



CInputs::Commands CInputs::stringToCommand(char *string){
// movements
	if(strcmp(string, "BackDown") == 0){
		return BackDown;
	}else if(strcmp(string, "Down") == 0){
		return Down;
	}else if(strcmp(string, "FrontDown") == 0){
		return FrontDown;
	}else if(strcmp(string, "Back") == 0){
		return Back;
	}else if(strcmp(string, "Stand") == 0){
		return Stand;
	}else if(strcmp(string, "Front") == 0){
		return Front;
	}else if(strcmp(string, "BackUp") == 0){
		return BackUp;
	}else if(strcmp(string, "Up") == 0){
		return Up;
	}else if(strcmp(string, "FrontUp") == 0){
		return FrontUp;
// attacks
	}else if(strcmp(string, "AttackBackDown") == 0){
		return AttackBackDown;
	}else if(strcmp(string, "AttackDown") == 0){
		return AttackDown;
	}else if(strcmp(string, "AttackFrontDown") == 0){
		return AttackFrontDown;
	}else if(strcmp(string, "AttackBack") == 0){
		return AttackBack;
	}else if(strcmp(string, "AttackStand") == 0){
		return AttackStand;
	}else if(strcmp(string, "AttackFront") == 0){
		return AttackFront;
	}else if(strcmp(string, "AttackBackUp") == 0){
		return AttackBackUp;
	}else if(strcmp(string, "AttackUp") == 0){
		return AttackUp;
	}else if(strcmp(string, "AttackFrontUp") == 0){
		return AttackFrontUp;
// proj
	}else if(strcmp(string, "ProjBackDown") == 0){
		return ProjBackDown;
	}else if(strcmp(string, "ProjDown") == 0){
		return ProjDown;
	}else if(strcmp(string, "ProjFrontDown") == 0){
		return ProjFrontDown;
	}else if(strcmp(string, "ProjBack") == 0){
		return ProjBack;
	}else if(strcmp(string, "ProjStand") == 0){
		return ProjStand;
	}else if(strcmp(string, "ProjFront") == 0){
		return ProjFront;
	}else if(strcmp(string, "ProjBackUp") == 0){
		return ProjBackUp;
	}else if(strcmp(string, "ProjUp") == 0){
		return ProjUp;
	}else if(strcmp(string, "ProjFrontUp") == 0){
		return ProjFrontUp;
// strong proj
	}else if(strcmp(string, "StrongProjBackDown") == 0){
		return StrongProjBackDown;
	}else if(strcmp(string, "StrongProjDown") == 0){
		return StrongProjDown;
	}else if(strcmp(string, "StrongProjFrontDown") == 0){
		return StrongProjFrontDown;
	}else if(strcmp(string, "StrongProjBack") == 0){
		return StrongProjBack;
	}else if(strcmp(string, "StrongProjStand") == 0){
		return StrongProjStand;
	}else if(strcmp(string, "StrongProjFront") == 0){
		return StrongProjFront;
	}else if(strcmp(string, "StrongProjBackUp") == 0){
		return StrongProjBackUp;
	}else if(strcmp(string, "StrongProjUp") == 0){
		return StrongProjUp;
	}else if(strcmp(string, "StrongProjFrontUp") == 0){
		return StrongProjFrontUp;
// dash
	}else if(strcmp(string, "DashBackDown") == 0){
		return DashBackDown;
	}else if(strcmp(string, "DashDown") == 0){
		return DashDown;
	}else if(strcmp(string, "DashFrontDown") == 0){
		return DashFrontDown;
	}else if(strcmp(string, "DashBack") == 0){
		return DashBack;
	}else if(strcmp(string, "DashStand") == 0){
		return DashStand;
	}else if(strcmp(string, "DashFront") == 0){
		return DashFront;
	}else if(strcmp(string, "DashBackUp") == 0){
		return DashBackUp;
	}else if(strcmp(string, "DashUp") == 0){
		return DashUp;
	}else if(strcmp(string, "DashFrontUp") == 0){
		return DashFrontUp;
// hits
	}else if(strcmp(string, "Hit") == 0){
		return Hit;
	}else if(strcmp(string, "HitAir") == 0){
		return HitAir;
	}else if(strcmp(string, "HitGround") == 0){
		return HitGround;
// others
	}else if(strcmp(string, "Start") == 0){
		return Start;
	}else if(strcmp(string, "Select") == 0){
		return Select;
	}else{
		return NoCommand;
	}

}

char *CInputs::commandToString(CInputs::Commands command){
	switch(command){
		case BackDown:
			return "BackDown";
		case  Down:
			return "Down";
		case  FrontDown:
			return "FrontDown";
		case  Back:
			return "Back";
		case  Stand:
			return "Stand";
		case  Front:
			return "Front";
		case  BackUp:
			return "BackUp";
		case  Up:
			return "Up";
		case  FrontUp:
			return "FrontUp";

		case AttackBackDown:
			return "AttackBackDown";
		case  AttackDown:
			return "AttackDown";
		case  AttackFrontDown:
			return "AttackFrontDown";
		case  AttackBack:
			return "AttackBack";
		case  AttackStand:
			return "AttackStand";
		case  AttackFront:
			return "AttackFront";
		case  AttackBackUp:
			return "AttackBackUp";
		case  AttackUp:
			return "AttackUp";
		case  AttackFrontUp:
			return "AttackFrontUp";

		case ProjBackDown:
			return "ProjBackDown";
		case  ProjDown:
			return "ProjDown";
		case  ProjFrontDown:
			return "ProjFrontDown";
		case  ProjBack:
			return "ProjBack";
		case  ProjStand:
			return "ProjStand";
		case  ProjFront:
			return "ProjFront";
		case  ProjBackUp:
			return "ProjBackUp";
		case  ProjUp:
			return "ProjUp";
		case  ProjFrontUp:
			return "ProjFrontUp";
		
		case StrongProjBackDown:
			return "StrongProjBackDown";
		case  StrongProjDown:
			return "StrongProjDown";
		case  StrongProjFrontDown:
			return "StrongProjFrontDown";
		case  StrongProjBack:
			return "StrongProjBack";
		case  StrongProjStand:
			return "StrongProjStand";
		case  StrongProjFront:
			return "StrongProjFront";
		case  StrongProjBackUp:
			return "StrongProjBackUp";
		case  StrongProjUp:
			return "StrongProjUp";
		case  StrongProjFrontUp:
			return "StrongProjFrontUp";
			
		case DashBackDown:
			return "DashBackDown";
		case  DashDown:
			return "DashDown";
		case  DashFrontDown:
			return "DashFrontDown";
		case  DashBack:
			return "DashBack";
		case  DashStand:
			return "DashStand";
		case  DashFront:
			return "DashFront";
		case  DashBackUp:
			return "DashBackUp";
		case  DashUp:
			return "DashUp";
		case  DashFrontUp:
			return "DashFrontUp";
		
		case Hit:
			return "Hit";
		case  HitAir:
			return "HitAir";
		case  HitGround:
			return "HitGround";
		
		case Start:
			return "Start";
		case  Select:
			return "Select";
		case  NoCommand:
			return "NoCommand";

		default:
			return "Error";
	}
}