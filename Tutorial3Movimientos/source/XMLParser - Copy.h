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
		
		class TXML{
			
			
			TXML()

			char *string;
			char *value;
			u8 numChilds;
			struct TXML **childs;
			struct TXML *father;
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

		void readWord(const char *rawData, int *index, char *&outWord);

		TXML* createTXML(char *tag);
		void addChildToTXML(TXML* &currentStruct,char* childToAdd);

		void printXML(TXML* data);
		void printSingleXML(TXML* data);

		void debug();

		bool isValidChar(volatile char c);
};



#endif
