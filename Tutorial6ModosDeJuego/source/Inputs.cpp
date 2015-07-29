



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
		_commands[_commandsIndex] = (Commands)( ((u16)_directions[0])+(9*1) );
	} else if(_keys & KEY_A){
		_commands[_commandsIndex] = (Commands)( ((u16)_directions[0])+(9*2) );
	} else if(_keys & KEY_Y){
		_commands[_commandsIndex] = (Commands)( ((u16)_directions[0])+(9*3) );
	} else if(_keys & KEY_X){
		_commands[_commandsIndex] = (Commands)( ((u16)_directions[0])+(9*4) );
	} else if(_keys & KEY_START){
		_commands[_commandsIndex] = CInputs::Start;
	} else {
		_commands[_commandsIndex] = CInputs::Stand;
	}

} // checkCombos

void CInputs::incrementInputsIndex(){
	++_commandsIndex;
	if(_commandsIndex > 4){
		_commandsIndex = 0;
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

// jumping
	}else if(strcmp(string, "JumpBackDown") == 0){
		return JumpBackDown;
	}else if(strcmp(string, "JumpDown") == 0){
		return JumpDown;
	}else if(strcmp(string, "JumpFrontDown") == 0){
		return JumpFrontDown;
	}else if(strcmp(string, "JumpBack") == 0){
		return JumpBack;
	}else if(strcmp(string, "JumpStand") == 0){
		return JumpStand;
	}else if(strcmp(string, "JumpFront") == 0){
		return JumpFront;
	}else if(strcmp(string, "JumpBackUp") == 0){
		return JumpBackUp;
	}else if(strcmp(string, "JumpUp") == 0){
		return JumpUp;
	}else if(strcmp(string, "JumpFrontUp") == 0){
		return JumpFrontUp;
// attacks
	}else if(strcmp(string, "JumpAttackBackDown") == 0){
		return JumpAttackBackDown;
	}else if(strcmp(string, "JumpAttackDown") == 0){
		return JumpAttackDown;
	}else if(strcmp(string, "JumpAttackFrontDown") == 0){
		return JumpAttackFrontDown;
	}else if(strcmp(string, "JumpAttackBack") == 0){
		return JumpAttackBack;
	}else if(strcmp(string, "JumpAttackStand") == 0){
		return JumpAttackStand;
	}else if(strcmp(string, "JumpAttackFront") == 0){
		return JumpAttackFront;
	}else if(strcmp(string, "JumpAttackBackUp") == 0){
		return JumpAttackBackUp;
	}else if(strcmp(string, "JumpAttackUp") == 0){
		return JumpAttackUp;
	}else if(strcmp(string, "JumpAttackFrontUp") == 0){
		return JumpAttackFrontUp;
// proj
	}else if(strcmp(string, "JumpProjBackDown") == 0){
		return JumpProjBackDown;
	}else if(strcmp(string, "JumpProjDown") == 0){
		return JumpProjDown;
	}else if(strcmp(string, "JumpProjFrontDown") == 0){
		return JumpProjFrontDown;
	}else if(strcmp(string, "JumpProjBack") == 0){
		return JumpProjBack;
	}else if(strcmp(string, "JumpProjStand") == 0){
		return JumpProjStand;
	}else if(strcmp(string, "JumpProjFront") == 0){
		return JumpProjFront;
	}else if(strcmp(string, "JumpProjBackUp") == 0){
		return JumpProjBackUp;
	}else if(strcmp(string, "JumpProjUp") == 0){
		return JumpProjUp;
	}else if(strcmp(string, "JumpProjFrontUp") == 0){
		return JumpProjFrontUp;
// strong proj
	}else if(strcmp(string, "JumpStrongProjBackDown") == 0){
		return JumpStrongProjBackDown;
	}else if(strcmp(string, "JumpStrongProjDown") == 0){
		return JumpStrongProjDown;
	}else if(strcmp(string, "JumpStrongProjFrontDown") == 0){
		return JumpStrongProjFrontDown;
	}else if(strcmp(string, "JumpStrongProjBack") == 0){
		return JumpStrongProjBack;
	}else if(strcmp(string, "JumpStrongProjStand") == 0){
		return JumpStrongProjStand;
	}else if(strcmp(string, "JumpStrongProjFront") == 0){
		return JumpStrongProjFront;
	}else if(strcmp(string, "JumpStrongProjBackUp") == 0){
		return JumpStrongProjBackUp;
	}else if(strcmp(string, "JumpStrongProjUp") == 0){
		return JumpStrongProjUp;
	}else if(strcmp(string, "JumpStrongProjFrontUp") == 0){
		return JumpStrongProjFrontUp;
// dash
	}else if(strcmp(string, "JumpDashBackDown") == 0){
		return JumpDashBackDown;
	}else if(strcmp(string, "JumpDashDown") == 0){
		return JumpDashDown;
	}else if(strcmp(string, "JumpDashFrontDown") == 0){
		return JumpDashFrontDown;
	}else if(strcmp(string, "JumpDashBack") == 0){
		return JumpDashBack;
	}else if(strcmp(string, "JumpDashStand") == 0){
		return JumpDashStand;
	}else if(strcmp(string, "JumpDashFront") == 0){
		return JumpDashFront;
	}else if(strcmp(string, "JumpDashBackUp") == 0){
		return JumpDashBackUp;
	}else if(strcmp(string, "JumpDashUp") == 0){
		return JumpDashUp;
	}else if(strcmp(string, "JumpDashFrontUp") == 0){
		return JumpDashFrontUp;
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
	// dirs
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
	
	// attack
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
	
	// proj
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
		
	// strong proj
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
			
	// dash
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
		
			// dirs
		case JumpBackDown:
			return "JumpBackDown";
		case JumpDown:
			return "JumpDown";
		case JumpFrontDown:
			return "JumpFrontDown";
		case JumpBack:
			return "JumpBack";
		case JumpStand:
			return "JumpStand";
		case JumpFront:
			return "JumpFront";
		case JumpBackUp:
			return "JumpBackUp";
		case JumpUp:
			return "JumpUp";
		case JumpFrontUp:
			return "JumpFrontUp";
	
	// attack
		case JumpAttackBackDown:
			return "JumpAttackBackDown";
		case JumpAttackDown:
			return "JumpAttackDown";
		case JumpAttackFrontDown:
			return "JumpAttackFrontDown";
		case JumpAttackBack:
			return "JumpAttackBack";
		case JumpAttackStand:
			return "JumpAttackStand";
		case JumpAttackFront:
			return "JumpAttackFront";
		case JumpAttackBackUp:
			return "JumpAttackBackUp";
		case JumpAttackUp:
			return "JumpAttackUp";
		case JumpAttackFrontUp:
			return "JumpAttackFrontUp";
	
	// proj
		case JumpProjBackDown:
			return "JumpProjBackDown";
		case JumpProjDown:
			return "JumpProjDown";
		case JumpProjFrontDown:
			return "JumpProjFrontDown";
		case JumpProjBack:
			return "JumpProjBack";
		case JumpProjStand:
			return "JumpProjStand";
		case JumpProjFront:
			return "JumpProjFront";
		case JumpProjBackUp:
			return "JumpProjBackUp";
		case JumpProjUp:
			return "JumpProjUp";
		case JumpProjFrontUp:
			return "JumpProjFrontUp";
	
		// strong proj
		case JumpStrongProjBackDown:
			return "JumpStrongProjBackDown";
		case JumpStrongProjDown:
			return "JumpStrongProjDown";
		case JumpStrongProjFrontDown:
			return "JumpStrongProjFrontDown";
		case JumpStrongProjBack:
			return "JumpStrongProjBack";
		case JumpStrongProjStand:
			return "JumpStrongProjStand";
		case JumpStrongProjFront:
			return "JumpStrongProjFront";
		case JumpStrongProjBackUp:
			return "JumpStrongProjBackUp";
		case JumpStrongProjUp:
			return "JumpStrongProjUp";
		case JumpStrongProjFrontUp:
			return "JumpStrongProjFrontUp";
			
	// dash
		case JumpDashBackDown:
			return "JumpDashBackDown";
		case JumpDashDown:
			return "JumpDashDown";
		case JumpDashFrontDown:
			return "JumpDashFrontDown";
		case JumpDashBack:
			return "JumpDashBack";
		case JumpDashStand:
			return "JumpDashStand";
		case JumpDashFront:
			return "JumpDashFront";
		case JumpDashBackUp:
			return "JumpDashBackUp";
		case JumpDashUp:
			return "JumpDashUp";
		case JumpDashFrontUp:
			return "JumpDashFrontUp";

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

char *CInputs::directionToString(CInputs::Direction dir){
	switch(dir){
		case DirBackDown:
			return "BackDown";
		case DirDown:
			return "Down";
		case DirFrontDown:
			return "FrontDown";
		case DirBack:
			return "Back";
		case DirStand:
			return "Stand";
		case DirFront:
			return "Front";
		case DirBackUp:
			return "BackUp";
		case DirUp:
			return "Up";
		case DirFrontUp:
			return "FrontUp";
	}
}

CInputs::Commands CInputs::commandToJumpCommand(CInputs::Commands command){
	switch(command){
	
	/*
	// dirs
		case BackDown:
			return JumpBackDown;
		case  Down:
			return JumpDown;
		case  FrontDown:
			return JumpFrontDown;
		case  Back:
			return JumpBack;
		case  Stand:
			return JumpStand;
		case  Front:
			return JumpFront;
		case  BackUp:
			return JumpBackUp;
		case  Up:
			return JumpUp;
		case  FrontUp:
			return JumpFrontUp;
	*/
	// attack
		case AttackBackDown:
			return JumpAttackBackDown;
		case  AttackDown:
			return JumpAttackDown;
		case  AttackFrontDown:
			return JumpAttackFrontDown;
		case  AttackBack:
			return JumpAttackBack;
		case  AttackStand:
			return JumpAttackStand;
		case  AttackFront:
			return JumpAttackFront;
		case  AttackBackUp:
			return JumpAttackBackUp;
		case  AttackUp:
			return JumpAttackUp;
		case  AttackFrontUp:
			return JumpAttackFrontUp;
	
	// proj
		case ProjBackDown:
			return JumpProjBackDown;
		case  ProjDown:
			return JumpProjDown;
		case  ProjFrontDown:
			return JumpProjFrontDown;
		case  ProjBack:
			return JumpProjBack;
		case  ProjStand:
			return JumpProjStand;
		case  ProjFront:
			return JumpProjFront;
		case  ProjBackUp:
			return JumpProjBackUp;
		case  ProjUp:
			return JumpProjUp;
		case  ProjFrontUp:
			return JumpProjFrontUp;
		
	// strong proj
		case StrongProjBackDown:
			return JumpStrongProjBackDown;
		case  StrongProjDown:
			return JumpStrongProjDown;
		case  StrongProjFrontDown:
			return JumpStrongProjFrontDown;
		case  StrongProjBack:
			return JumpStrongProjBack;
		case  StrongProjStand:
			return JumpStrongProjStand;
		case  StrongProjFront:
			return JumpStrongProjFront;
		case  StrongProjBackUp:
			return JumpStrongProjBackUp;
		case  StrongProjUp:
			return JumpStrongProjUp;
		case  StrongProjFrontUp:
			return JumpStrongProjFrontUp;
			
	// dash
		case DashBackDown:
			return JumpDashBackDown;
		case  DashDown:
			return JumpDashDown;
		case  DashFrontDown:
			return JumpDashFrontDown;
		case  DashBack:
			return JumpDashBack;
		case  DashStand:
			return JumpDashStand;
		case  DashFront:
			return JumpDashFront;
		case  DashBackUp:
			return JumpDashBackUp;
		case  DashUp:
			return JumpDashUp;
		case  DashFrontUp:
			return JumpDashFrontUp;
		

		case Hit:
			return Hit;
		case  HitAir:
			return HitAir;
		case  HitGround:
			return HitGround;
		
		case Start:
			return Start;
		case  Select:
			return Select;
		default :
			return NoCommand;

		
	}
}