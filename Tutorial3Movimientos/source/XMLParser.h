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
			TXML **childs;
			TXML *father;
		};

		// Contructores
		CXMLParser(const char *characterName);

		// Destructor
		~CXMLParser(void);
		
		
	private:

		TXML * _data;
		const char * _rawData;
		int *_index;

		char* ReadFile(const char *file);
		TXML* Parse(const char *rawData);

		void readTag(const char *rawData, int *index, char *&outWord);
		void readValue(const char *rawData, int *index, char *&outWord);

		TXML* createTXML(char *tag);
		void addChildToTXML(TXML *&currentStruct,char* childToAdd, TXML**&temp);

		void printXML(TXML* data, u8 deep = 0);
		void printSingleXML(TXML* data, u8 deep = 0);

		void debug();

		bool isValidChar(volatile char c);
};



#endif
