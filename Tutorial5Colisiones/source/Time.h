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

	

	public:
		
		// Contructores
		CTime();
		
		// Destructor
		~CTime(void);

		//	Metodos
		static float& deltaTime();
		
		void Update();

		time_t getCurrentTime(){return _currentTime;}
		time_t getLastTime(){return _currentTime;}
	private:
		time_t _currentTime;
		time_t _lastTime;
		static float _deltaTime;
};



#endif
		
