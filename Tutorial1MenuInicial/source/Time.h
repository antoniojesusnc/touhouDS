#ifndef __TIME_H__
#define __TIME_H__





/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/
#include <ctime>


// Clase CEngine
class CTime {

	private:
		time_t _currentTime;
		time_t _lastTime;
		static double _deltaTime;

	public:
		
		// Contructores
		CTime();
		
		// Destructor
		~CTime(void);

		//	Metodos
		static double& deltaTime(){
			return _deltaTime;
		} // deltaTime
		
		void Update(){
			time(&_currentTime);
			_deltaTime = difftime(_currentTime, _lastTime);
			_currentTime = _lastTime;
		} // Update
		
};

//double CTime::_deltaTime = 0;


#endif
		
