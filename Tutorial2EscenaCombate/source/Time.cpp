



/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/
#include <ctime>
#include "time.h"

#include <nds.h>

// Includes librerias propias
#include <nf_lib.h>

float CTime::_deltaTime = 0;
// Clase CTime
CTime::CTime(){
	_lastTime = time(NULL);
	_currentTime = time(NULL);
	time(&_lastTime);
	//_currentTime = _lastTime;
}
		
// Destructor
CTime::~CTime(){
}

//	Metodos
float& CTime::deltaTime(){
	return _deltaTime;
} // deltaTime
		
void CTime::Update(){
	/*
	time(&_currentTime) ;
	_deltaTime = difftime(_currentTime, _lastTime);
	//_deltaTime = _currentTime - _lastTime;
	_lastTime = _currentTime;
	*/
	_deltaTime = 1;//0.016f;
} // Update