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
#include "XMLParser.h"



#include <nds.h>
#include <filesystem.h>

#include <stdlib.h>
#include <string.h>
#include <dirent.h>


/*
	Metodos de la clase "CCharacterParser"
*/

// Contructor clase CCharacterParser
CXMLParser::CXMLParser(const char *characterName) {
	

	char *fileName = (char*)malloc(strlen(characterName)+9);
	// se crea con basura, y para q el cat funcione bien
	fileName[0] = '\0';  
	strcat(fileName , "xml/");
	strcat(fileName , characterName);
	strcat(fileName , ".xml");
	//fileName[strlen(characterName)+9] = '\0';
	//printf("%s",fileName);

	_rawData = ReadFile(fileName);
	//free(fileName);
	_data = Parse(_rawData);
	//free(_rawData);
	
} // CCharacterParser

char* CXMLParser::ReadFile(const char *fileName){
	
	FILE* inf = fopen(fileName,"rb");
	if(inf)
	{
		int len;

		fseek(inf,0,SEEK_END);
		len = ftell(inf);
		fseek(inf,0,SEEK_SET);

		char *entireFile = (char*)malloc(len+2);
		entireFile[len] = 0;//'\0';
		entireFile[len+1] = '\0';

		if(fread(entireFile,1,len,inf) != len)
			NF_Error(404, "file not found",1);

		//free(entireFile);

		fclose(inf);

		return entireFile;
	}
	return NULL;
} // readFile

CXMLParser::TXML* CXMLParser::Parse(const char *rawData){
	
	int index = 0;

	char* auxWord = NULL;	

	TXML *structedData = NULL;
	TXML *currentStructedData = NULL;

	TXML **auxChild;

	//printf("\n %s\n", rawData);
	while(rawData[index] != 0){//'\0'){
		if(!isValidChar(rawData[index]) || rawData[index] == '>'){
			++index;
			continue;	
		}
		if(rawData[index] == '<'){
			if(rawData[index+1] != '/'){
				readTag(rawData, &index, auxWord);
				if(currentStructedData == NULL){
					currentStructedData = createTXML(auxWord);
				}else{
					addChildToTXML(currentStructedData, auxWord, auxChild);
				}
				if(structedData == NULL){
					structedData = currentStructedData;
				}
			}else{ // end if < and not /
			}
		}else{ // else <
			if(rawData[index] == '/'){
				readTag(rawData, &index, auxWord);
				currentStructedData = currentStructedData->father;
			}else{ // is data
				readValue(rawData, &index, auxWord);
				currentStructedData->value = auxWord;
			} // end else if / 
		} // end else if <
		++index;
	} // end while
	
	return structedData;
	
} // Parse




void CXMLParser::readTag(const char *rawData, int* index, char *&outWord){
	volatile int indexTemp = (*index);
	vu8 stringSize = 0;
	while(rawData[++indexTemp] != '>'){
		++stringSize;
	}
	//free(outWord);
	outWord = (char*)malloc(sizeof(char)*(stringSize+1));
	strncpy(outWord, &(rawData[(*index)+1]), sizeof(char)*(stringSize));
	outWord[stringSize] = '\0';

	*index += stringSize;
} // readTag

void CXMLParser::readValue(const char *rawData, int* index, char *&outWord){
	volatile int indexTemp = (*index)-2;
	vu8 stringSize = 0;
	while(rawData[++indexTemp] != '<'){
		++stringSize;
	}
	//free(outWord);
	stringSize;
	outWord = (char*)malloc(sizeof(char)*(stringSize-1));
	strncpy(outWord, &(rawData[(*index)]), sizeof(char)*(stringSize-1));
	outWord[stringSize-1] = '\0';

	*index += stringSize-2;
} // readValue

CXMLParser::TXML* CXMLParser::createTXML(char *tag){

	TXML *tempData = (TXML*)malloc(sizeof(TXML));
	tempData->tag = tag;
	tempData->value = NULL;
	tempData->numChilds = 0;
	tempData->childs = NULL;
	tempData->father = NULL;
	return tempData;

} // createEmptyTXML

void  CXMLParser::addChildToTXML(TXML *&currentStruct,char* childToAdd, TXML**&temp){
	temp = (TXML**)malloc(sizeof(TXML*)*(currentStruct->numChilds+1));
	vu8 i;
	for(i = 0; i < currentStruct->numChilds; ++i){
		temp[i] = currentStruct->childs[i];
		/*
		temp[i] = (TXML*)malloc(sizeof(TXML));
		temp[i]->tag = currentStruct->childs[i]->tag;
		temp[i]->value = currentStruct->childs[i]->value;
		temp[i]->childs = currentStruct->childs[i]->childs;
		temp[i]->father = currentStruct;
		temp[i]->numChilds = currentStruct->childs[i]->numChilds;

		free(currentStruct->childs[i]);
		*/
	}
	temp[i] = (TXML*)malloc(sizeof(TXML));
	
	temp[i]->tag = childToAdd;
	temp[i]->value = NULL;
	temp[i]->numChilds = 0;
	temp[i]->father = currentStruct;
	temp[i]->childs = NULL;
	++currentStruct->numChilds;

	free(currentStruct->childs);
	currentStruct->childs = &temp[0];
	currentStruct = temp[i];
} // addChildToTXML

bool CXMLParser::isValidChar(volatile char c){
	// numbers   // lower case    // upper case  // character /
	return c > 21 && c < 125;
	//return  ( (c > 48 && c < 57) || (c > 65 && c < 90) || (c > 91 && c < 122) || c == 47); 
			
}

CXMLParser::TXML* CXMLParser::getDataByTag(char * tag, TXML* current){

	if(current == NULL)
		current = _data;

	if(tagCompare(current, tag ))
		return current;
	TXML *temp;
	for(vu8 i = 0; i < current->numChilds; ++i){
		if((temp = getDataByTag(tag, current->childs[i])) != NULL){
			return temp;
		}
	}
	
	return NULL;
} // getDataByTag

bool CXMLParser::tagCompare(TXML *data, char * tag){

	if(strcmp(data->tag, tag) == 0){
		//printXML(data);
		return true;
	}else{
		return false;
	}
	
	
} // tagCompare

// Destructor clase CCharacterParser
CXMLParser::~CXMLParser(void) {

	free(_rawData);

	destroyXML(_data);
} // ~CCharacterParser

void CXMLParser::destroyXML(TXML* data){

	for(vu8 i = 0; i < data->numChilds; ++i){
		destroyXML(data->childs[i]);
	}
	destroySingleXML(data);
} // destroyXML

void CXMLParser::destroySingleXML(TXML* data){
	free(data->tag);
	free(data->value);
	data->father = NULL;
} // destroySingleXML



void CXMLParser::printData(){
	printXML(_data);
} // printData

void CXMLParser::printXML(TXML* data, u8 deep){

	if(deep == 0)
		printf("\nXML");

	printSingleXML(data, deep+1);
	
	for(vu8 i = 0; i < data->numChilds; ++i){
		printXML(data->childs[i], deep+1);
	}
	
} // printXML

void CXMLParser::printSingleXML(TXML* data, u8 deep){
	if(data == NULL){
		printf("\nVacio");
		return;
	}
	printf("\n");
	for(vu8 i = 0; i < deep; ++i){
		printf(" ");
	}
	printf("%s:%s-%d",data->tag, data->value, data->numChilds);
} // printSingleXML
