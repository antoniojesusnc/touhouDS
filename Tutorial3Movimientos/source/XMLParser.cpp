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
		entireFile[len] = 3;

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

	char* auxWord = NULL;	

	TXML *structedData = NULL;
	TXML *currentStructedData = NULL;


	int parents = 0;
	
	//printf("\n %s\n", rawData);
	while(rawData[++index] != 3){

		printf("%d",rawData[index]);
		//continue;

		if(rawData[index] == '<'){
			if(rawData[index+1] != '/'){
				
				++parents ;
				
				printf("\n aa %d %c", index, rawData[index]);
				readWord(rawData, &index, auxWord);
				printf("\n << %s %d %c",auxWord, index,rawData[index]);
				
				//printf("\n2%d: %d %s %c %c",index, auxWord, auxWord, auxWord[2], auxWord[3]);
				//return NULL;

				//printf("\n outStack ");
				printf("\n stack %s",auxWord);
					
				TXML *tempData = createTXML(auxWord);
						
				if(currentStructedData == NULL){
					currentStructedData = tempData;
				}else{
					//printf("\n chng %s",auxWord);
					printSingleXML(currentStructedData);
					currentStructedData = addChildToTXML(currentStructedData, tempData);
					printSingleXML(currentStructedData);
				}	
				if(structedData == NULL){
					printf("\n onnly");
					structedData = currentStructedData;
				}
			} // end if < and not /
			else{
			printf("aaaaaaaaaaaaaa");
			}
		}else{ // else <
			if(rawData[index] == '/'){
				printf("\n // %d %c %s",rawData[index], rawData[index], auxWord);
				return structedData;

				readWord(rawData, &index, auxWord);
				currentStructedData = currentStructedData->parent;
			}else{
				if( (rawData[index] > 48 && rawData[index] < 57) || // numbers
					(rawData[index] > 65 && rawData[index] < 90) ||// lower case
					(rawData[index] > 91 && rawData[index] < 122) ){ // upper case

					printf("\n aa2 %c %d ",rawData[index], index);
					printf("\ndefault %d %c %s",rawData[index-2], rawData[index-2], auxWord);
					printf("\ndefault %d %c %s",rawData[index-1], rawData[index-1], auxWord);
					printf("\ndefault %d %c %s",rawData[index], rawData[index], auxWord);
					readWord(rawData, &index, auxWord);
					printf("\ndefault %d %c %s",rawData[index-2], rawData[index-2], auxWord);
					printf("\ndefault %d %c %s",rawData[index-1], rawData[index-1], auxWord);
					printf("\ndefault %d %c %s",rawData[index], rawData[index], auxWord);
					//return structedData;
											/*
					currentStructedData->value = (char*)malloc(sizeof(char)*strlen(auxWord));
					strcpy(currentStructedData->value,auxWord);
					*/
					currentStructedData->value = auxWord;
					break;
				} // end if alpha numeric
						
			} // en else if /
		} // end else if <

				
		//printf("#%d %d %c#", index, rawData[index],rawData[index] );
	} // end while
	
	
	printf("\nEnd");
	return structedData;
	
} // Parse




void CXMLParser::readWord(const char *rawData, u16* index, char*&outWord){

	vu8 indexTemp = (*index);
	vu8 stringSize = 0;

	while(rawData[++indexTemp] != '>'){
		++stringSize;
	}

	
	//free(outWord);
	outWord = (char*)malloc(sizeof(char)*stringSize+1);
	
	
	strncpy(outWord, &(rawData[(*index)+1]), sizeof(char)*stringSize+1);
	outWord[stringSize] = '\0';
	
	

	*index += stringSize;

	printf("\n %c %c %c", rawData[*index-1],rawData[*index],rawData[*index+1]);

} // readWord

CXMLParser::TXML* CXMLParser::createTXML(char *rawData){

	TXML *tempData = (TXML*)malloc(sizeof(TXML));
	tempData->string = rawData;
	tempData->value = NULL;
	tempData->numChilds = 0;
	tempData->childs = NULL;
	tempData->parent = NULL;
	return tempData;

} // createEmptyTXML

CXMLParser::TXML* CXMLParser::addChildToTXML(TXML* &currentStruct,TXML* childToAdd){

	TXML *temp = (TXML*)malloc(sizeof(TXML)*(currentStruct->numChilds+1));

	vu8 i;
	vu8 auxSize;
	for(i = 0; i < currentStruct->numChilds; ++i){
		/*
		auxSize = strlen(currentStruct->childs[i].string);
		temp->string = (char*)malloc(sizeof(char)*(auxSize+1));
		strcpy(temp[i].string, currentStruct->childs[i].string);
		temp->string[auxSize] = '\0';
		
		auxSize = strlen(currentStruct->childs[i].value);
		temp->value = (char*)malloc(sizeof(char)*(auxSize+1) );
		strcpy(temp[i].value, currentStruct->childs[i].value);
		temp->value[auxSize] = '\0';
		
		*/
		temp[i].string = currentStruct->childs[i].string;
		temp[i].value = currentStruct->childs[i].value;
		if(currentStruct->childs[i].numChilds > 0)
			temp[i].childs = currentStruct->childs[i].childs;

		temp[i].parent = currentStruct;
		temp[i].numChilds = currentStruct->childs[i].numChilds;
	}

	/*
	auxSize = strlen(childToAdd->string);
	temp->string = (char*)malloc(sizeof(char)*(auxSize+1));
	strcpy(temp[i].string, childToAdd->string);
	temp[i].string[auxSize] = '\0';

	//printf("\n addchildS %d %s %d %s",i, temp->string , strlen(childToAdd->string), childToAdd->string );
		//return NULL;

	if(childToAdd->value != NULL){
		auxSize = strlen(childToAdd->value);
		temp->string = (char*)malloc(sizeof(char)*(auxSize+1));
		strcpy(temp[i].string, childToAdd->value);
		temp[i].value[auxSize] = '\0';
	
		//printf("\n addchildV %s %d %s",temp->value , strlen(childToAdd->value), childToAdd->value );
			//return NULL;	
	}else{
		temp[i].value = NULL;
	}
	*/
	temp->string = childToAdd->string;
	temp->value = childToAdd->value;
	
	temp[i].numChilds = childToAdd->numChilds;
	temp[i].parent = currentStruct;
	temp[i].childs = childToAdd->childs;

	free(currentStruct->childs);
	currentStruct->childs = temp;
	++currentStruct->numChilds;

	return temp;
} // addChildToTXML

void CXMLParser::printXML(TXML* data){
	printSingleXML(data);
	
	for(vu8 i = 0; i < data->numChilds; ++i){
		printSingleXML(&data->childs[i]);
	}
	
} // printXML

void CXMLParser::printSingleXML(TXML* data){
	if(data == NULL){
		printf("\nVacio");
		return;
	}
	printf("\n %s : %s  -  %d",data->string, data->value, data->numChilds);
} // printSingleXML

// Destructor clase CCharacterParser
CXMLParser::~CXMLParser(void) {

} // ~CCharacterParser



