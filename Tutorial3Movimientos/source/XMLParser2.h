#ifndef __CHARACTER_PARSER2_H__
#define __CHARACTER_PARSER2_H__





/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/

// Defines
#include <stack>

// Clase CCharacterParser2
class CXMLParser2 {

	
	public:
		
		struct TXML{
			
			char *string;
			char *value;
			u8 numChilds;
			TXML **childs;
			TXML *father;
		};

		// Contructores
		CXMLParser2(const char *characterName);

		// Destructor
		~CXMLParser2(void);
		
		
	private:

		TXML * _data;
		const char * _rawData;
		int *_index;

		char* ReadFile(const char *file);
		TXML* Parse(const char *rawData);

		void readWord(const char *rawData, int *index, char *&outWord);

		TXML* createTXML(char *tag);
		TXML* addChildToTXML(TXML**currentStruct,char* childToAdd);

		void printXML(TXML* data);
		void printSingleXML(TXML* data);

		void debug();

		bool isValidChar(volatile char c);
};



#endif
