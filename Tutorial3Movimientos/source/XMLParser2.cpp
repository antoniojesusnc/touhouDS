/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/

// Includes C/C++
#include <stdio.h>

#include <stack>

// Includes propietarios NDS
#include <nds.h>
#include <filesystem.h>


// Includes librerias propias
#include <nf_lib.h>

// Includes del programa
#include "XMLParser2.h"



#include <nds.h>
#include <filesystem.h>

#include <stdlib.h>
#include <string.h>
#include <dirent.h>


/*
	Metodos de la clase "CCharacterParser2"
*/

// Contructor clase CCharacterParser2
CXMLParser2::CXMLParser2(const char *characterName) {
	
	vu8 size = (strlen(characterName)+9);
	char *fileName = (char*)malloc(sizeof(char)*size );
	strcat(fileName , "xml/");
	strcat(fileName , characterName);
	strcat(fileName , ".xml");
	printf("\n %s",fileName);
	char *rawData = ReadFile(fileName);
	free(fileName);


	_rawData = rawData;
	_data = Parse(rawData);

	printXML(_data);

	debug();
} // CCharacterParser2

char* CXMLParser2::ReadFile(const char *fileName){
	
	FILE* inf = fopen(fileName,"rb");
	if(inf)
	{
		int len;

		fseek(inf,0,SEEK_END);
		len = ftell(inf);
		fseek(inf,0,SEEK_SET);

		char *entireFile = (char*)malloc(len+1);
		entireFile[len] = '\0';

		if(fread(entireFile,1,len,inf) != len)
			NF_Error(404, "file not found",1);

		//free(entireFile);

		fclose(inf);

		return entireFile;
	}
	return NULL;
} // readFile

CXMLParser2::TXML* CXMLParser2::Parse(const char *rawData){

	u16 index = 0;
	while(rawData[index] != '\0'){
	
		printf("%c", rawData[index]);
		++index;
	}

} // Parse




void CXMLParser2::readWord(const char *rawData, int* index, char *&outWord){

	
} // readWord

CXMLParser2::TXML* CXMLParser2::createTXML(char *tag){



} // createEmptyTXML

CXMLParser2::TXML* CXMLParser2::addChildToTXML(TXML**currentStruct,char* childToAdd){

	
} // addChildToTXML

void CXMLParser2::printXML(TXML* data){
	printSingleXML(data);
	
	for(vu8 i = 0; i < data->numChilds; ++i){
		printSingleXML(data->childs[i]);
	}
	
} // printXML

void CXMLParser2::printSingleXML(TXML* data){
	if(data == NULL){
		printf("\nVacio");
		return;
	}
	printf("\n %s : %s  -  %d",data->string, data->value, data->numChilds);
} // printSingleXML

bool CXMLParser2::isValidChar(volatile char c){
	// numbers   // lower case    // upper case  // character /
	return c > 21 && c < 125;
	//return  ( (c > 48 && c < 57) || (c > 65 && c < 90) || (c > 91 && c < 122) || c == 47); 
			
}

// Destructor clase CCharacterParser2
CXMLParser2::~CXMLParser2(void) {

} // ~CCharacterParser2



void CXMLParser2::debug(){

	int index = 0;
	printf("\n Size : %d\n",strlen(_rawData));
	while(_rawData[index] != '\0'){
		printf("%c",_rawData[index] );
		++index;
	}
}

