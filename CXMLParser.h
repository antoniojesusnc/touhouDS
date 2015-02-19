#ifndef __CHARACTER_PARSER_H__
#define __CHARACTER_PARSER_H__





/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/

// Defines
#include <stack>


class CXML;


// Clase CCharacterParser
class CXMLParser {

	public:
		// Contructores
		CXMLParser(const char *characterName);

		// Destructor
		~CXMLParser(void);
		
		
	private:

		CXML * _data;
		const char * _rawData;
		int *_index;

		char* ReadFile(const char *file);
		CXML* Parse(const char *rawData);

		void readWord(const char *rawData, int *index, char *&outWord);

		CXML* createCXML(char *tag);
		void addChildToCXML(CXML *&currentStruct,char* childToAdd);

		void printXML(CXML* data);
		void printSingleXML(CXML* data);

		void debug();

		bool isValidChar(volatile char c);
};



#endif
