#ifndef __CHARACTER_PARSER_H__
#define __CHARACTER_PARSER_H__





/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/

// Defines
#include <stack>

// Clase CCharacterParser
class CXMLParser {

	
	public:
		
		struct TXML{
			char *string;
			char *value;
			u8 numChilds;
			struct TXML *childs;
			struct TXML *parent;
			
		};

		// Contructores
		CXMLParser(const char *characterName);

		// Destructor
		~CXMLParser(void);
		
		
	private:

		TXML * _data;

		char* ReadFile(const char *file);
		TXML* Parse(const char *rawData);

		void readWord(const char *rawData, u16 *index, char *&outWord);

		TXML* createTXML(char *rawData);
		TXML* addChildToTXML(TXML* &currentStruct,TXML* childToAdd);

		void printXML(TXML* data);
		void printSingleXML(TXML* data);


		
};



#endif
