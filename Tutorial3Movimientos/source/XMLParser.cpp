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
	
	char *fileName = new char[30];
	strcat(fileName , "xml/");
	strcat(fileName , characterName);
	strcat(fileName , ".xml");

	char *rawData = ReadFile(fileName);
	free(fileName);

	_data = Parse(rawData);

	printXML(_data);

} // CCharacterParser

char* CXMLParser::ReadFile(const char *fileName){
	
	FILE* inf = fopen(fileName,"rb");
	if(inf)
	{
		int len;

		fseek(inf,0,SEEK_END);
		len = ftell(inf);
		fseek(inf,0,SEEK_SET);

		char *entireFile = (char*)malloc(len+1);
		entireFile[len] = 0;
		if(fread(entireFile,1,len,inf) != len)
			NF_Error(404, "file not found",1);

		free(entireFile);

		fclose(inf);

		return entireFile;
	}
	return NULL;
} // readFile

CXMLParser::TXML* CXMLParser::Parse(const char *rawData){
	
	u16 index = -1;
	std::stack<char *> stack;

	char* auxWord = NULL;	

	TXML *structedData = NULL;
	TXML *currentStructedData = NULL;

	
	
	

	while(rawData[++index] != 0){
		switch(rawData[index]){
			case  '<': 
				
					

				if(rawData[index+1] != '/'){
					
					readWord(rawData, &index, auxWord);

					//printf("\n2%d: %d %s %c %c",index, auxWord, auxWord, auxWord[2], auxWord[3]);
					//return NULL;

					if(strcmp(auxWord,stack.top())!=0){
						stack.push(auxWord);
						TXML *tempData = createTXML(&stack);
						if(currentStructedData == NULL){
							currentStructedData = tempData;
						}else{
							currentStructedData = addChildToTXML(currentStructedData, tempData);
						}
	
						if(structedData == NULL){
							structedData = currentStructedData;
						}
					}
				}
				
				break;
			case  '/': 
				readWord(rawData, &index, auxWord);
				if(strcmp(stack.top(),auxWord) == 0){
					stack.pop();
					currentStructedData = currentStructedData->parent;
				}else{
					NF_Error(402, "pop no encontrado",0);
				}
				break; 
			case  '>': 
			case '\t': 
			case '\n': 
			case  ' ': 
				break; 
			default  : 
				readWord(rawData, &index, auxWord);
				currentStructedData->value = (char*)malloc(sizeof(char)*strlen(auxWord));
				strcpy(currentStructedData->value,auxWord);
				break;
		}
		
	}
	
	
	printf("end");
	
	
} // Parse




void CXMLParser::readWord(const char *rawData, u16* index, char*&outWord){
	//free(outWord);

	vu8 indexTemp = (*index);
	vu8 stringSize = 0;

	while(rawData[++indexTemp] != '>'){
		++stringSize;
	}

	
	free(outWord);
	outWord = (char*)malloc(sizeof(char)*stringSize+1);
	
	
	strncpy(outWord, &(rawData[(*index)+1]), sizeof(char)*stringSize+1);
	outWord[stringSize] = '\0';
	
	

	*index += stringSize;

} // readWord

CXMLParser::TXML* CXMLParser::createTXML(std::stack<char*> *stackData){

	TXML *tempData = (TXML*)malloc(sizeof(TXML));
	tempData->string = stackData->top();
	tempData->value = NULL;
	tempData->numChilds = 0;
	tempData->childs = NULL;
	tempData->parent = NULL;
	return tempData;

} // createEmptyTXML

CXMLParser::TXML* CXMLParser::addChildToTXML(TXML* &currentStruct,TXML* childToAdd){
	TXML *temp = (TXML*)malloc(sizeof(TXML)*currentStruct->numChilds+1);
	vu8 i;
	for(i = 0; i < currentStruct->numChilds; ++i){
		temp->string = (char*)malloc(sizeof(char)*strlen(currentStruct->childs[i].string));
		strcpy(temp[i].string, currentStruct->childs[i].string);

		temp->value = (char*)malloc(sizeof(char)*strlen(currentStruct->childs[i].value));
		strcpy(temp[i].value, currentStruct->childs[i].value);
		
		if(&currentStruct->childs[i].numChilds > 0)
			temp[i].childs = currentStruct->childs[i].childs;

		temp[i].parent = currentStruct;


	}
	
	temp->string = (char*)malloc(sizeof(char)*strlen(childToAdd->childs[i].string));
	strcpy(temp[i].string, childToAdd->childs[i].string);

	temp->value = (char*)malloc(sizeof(char)*strlen(childToAdd->childs[i].value));
	strcpy(temp[i].value, childToAdd->childs[i].value);
	temp[i].parent = currentStruct;
	
	free(currentStruct->childs);
	currentStruct->childs = temp;

	return &temp[i];
} // addChildToTXML

void CXMLParser::printXML(TXML* data){
	printSingleXML(data);
	for(vu8 i = 0; i < data->numChilds; ++i){
		printXML(&data->childs[i]);
	}
} // printXML

void CXMLParser::printSingleXML(TXML* data){
	printf("\n %s : %s  -  %d",data->string, data->value, data->numChilds);
} // printSingleXML

// Destructor clase CCharacterParser
CXMLParser::~CXMLParser(void) {

} // ~CCharacterParser



