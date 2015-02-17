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

	debug();
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
		entireFile[len] = 0;//'\0';

		if(fread(entireFile,1,len,inf) != len)
			NF_Error(404, "file not found",1);

		free(entireFile);

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


	_index = &index;
	_rawData = rawData;

	//printf("\n %s\n", rawData);
	while(rawData[index] != 0){//'\0'){

		if(!isValidChar(rawData[index]) || rawData[index] == '>'){
			++index;
			continue;	
		}

		if(index < 5){
		
			//debug();

			
		}else{
			printXML(structedData);
			printf("\n d %d %s %c %d",index, auxWord, rawData[index], rawData[index]);
			
			//printXML(currentStructedData);

			return structedData;
		}
		//continue;

		if(rawData[index] == '<'){
			if(rawData[index+1] != '/'){

				printf("\n << %s %d",auxWord, index);
				readWord(rawData, &index, auxWord);
				

				if(currentStructedData == NULL){
					currentStructedData = createTXML(auxWord);
					
				}else{
					
					printf("\n chng %s",auxWord);
					printf("\n b %d %c %s",index, rawData[index], auxWord);
					printf("\n aa %d %c %c",*_index, _rawData[*_index], _rawData[*_index+1] );
					addChildToTXML(currentStructedData, auxWord);
					printf("\n b %d %c %s",index, rawData[index], auxWord);
					if(index > 6)
						return structedData;
				}	


				if(structedData == NULL){
					printf("\n onnly");
					
					*structedData = *currentStructedData;
					
				}
				
			}else{ // end if < and not /
			
				printf("aaaaaaaaaaaaaa");
			}
		}else{ // else <
			if(rawData[index] == '/'){
							
				readWord(rawData, &index, auxWord);
				
				printf("\n // %c %d %s", rawData[index],index, auxWord);
				return structedData;

				currentStructedData = currentStructedData->father;
			}else{ // is data

				printf("\n vant %c %d",rawData[index], index);
				readWord(rawData, &index, auxWord);
				printf("\n vdes %s %c", auxWord, rawData[index]);
				return structedData;
										/*
				currentStructedData->value = (char*)malloc(sizeof(char)*strlen(auxWord));
				strcpy(currentStructedData->value,auxWord);
				*/
				currentStructedData->value = auxWord;
			} // end else if / 
						
		} // end else if <

				
		++index;
	} // end while
	
	
	printf("\nEnd");
	return structedData;
	
} // Parse




void CXMLParser::readWord(const char *rawData, int* index, char *&outWord){

	printf("\n a %d %c %s",*index, rawData[*index], outWord);
	
	vu8 indexTemp = (*index);
	vu8 stringSize = 0;

	while(rawData[++indexTemp] != '>'){
		++stringSize;
	}

	
	//free(outWord);
	outWord = (char*)malloc(sizeof(char)*(stringSize+1));
	/*
	indexTemp = *index
	
	while(++indexTemp <= *index+stringSize){
		outWord[indexTemp-*index-1] = rawData[indexTemp];
	}
	*/
	strncpy(outWord, &(rawData[(*index)+1]), sizeof(char)*(stringSize));
	outWord[stringSize] = '\0';
	
	
	//printf("\n b %d %d %c %s",*index, stringSize,rawData[*index], outWord);
	*index += stringSize+1;
	//printf("\n b %d %d %c %s",*index, stringSize,rawData[*index], outWord);
	//printf("\n b %d %d %c %s",*index+1, stringSize,rawData[*index+1], outWord);
	debug();
} // readWord

CXMLParser::TXML* CXMLParser::createTXML(char *tag){

	printf("a1 %d %c %c ",*_index, _rawData[*_index], _rawData[*_index+1] );
	struct TXML *tempData = (TXML*)malloc(sizeof(TXML));
	printf("a2 %d %c %c ",*_index, _rawData[*_index], _rawData[*_index+1] );
	tempData->string = tag;
	printf("a3 %d %c %c ",*_index, _rawData[*_index], _rawData[*_index+1] );
	tempData->value = NULL;
	printf("a3 %d %c %c ",*_index, _rawData[*_index], _rawData[*_index+1] );
	tempData->numChilds = 0;
	printf("a4 %d %c %c ",*_index, _rawData[*_index], _rawData[*_index+1] );
	tempData->childs[0] = NULL;
	printf("\n a5 %d %c %c",*_index, _rawData[*_index], _rawData[*_index+1] );
	debug();
	tempData->father = NULL;
	debug();
	printf("\n a8 %d %c %c",*_index, _rawData[*_index], _rawData[*_index+1] );
	return tempData;

} // createEmptyTXML

void CXMLParser::addChildToTXML(TXML* &currentStruct,char* childToAdd){

	printf("\n aa %d %c %c %s %d",*_index, _rawData[*_index], _rawData[*_index+1], childToAdd, strlen(childToAdd) );
	TXML **temp = (TXML**)malloc(sizeof(TXML*)*(currentStruct->numChilds+2));

	vu8 i;
	vu8 auxSize;
	for(i = 0; i < currentStruct->numChilds; ++i){
		printf("\n10 buvcle");
		temp[i]->string = currentStruct->childs[i]->string;
		temp[i]->value = currentStruct->childs[i]->value;
		if(currentStruct->childs[i]->numChilds > 0)
			temp[i]->childs = currentStruct->childs[i]->childs;

		temp[i]->father = currentStruct;
		temp[i]->numChilds = currentStruct->childs[i]->numChilds;
	}


	temp[i] = (TXML*)malloc(sizeof(TXML));
	/*
	temp[i]->string = childToAdd->string;
	temp[i]->value = childToAdd->value;
	temp[i]->numChilds = childToAdd->numChilds;
	temp[i]->parent = currentStruct;
	temp[i]->childs = childToAdd->childs;
	*/
	printf("\n bb %d ",sizeof(TXML));
	printf("\n b2 %d %c %c",*_index, _rawData[*_index], _rawData[*_index+1] );
	temp[i]->string = childToAdd;
	printf("\n b3 %d %c %c",*_index, _rawData[*_index], _rawData[*_index+1] );
	temp[i]->value = NULL;
	printf("\n b5 %d %c %c",*_index, _rawData[*_index], _rawData[*_index+1] );
	temp[i]->numChilds = 0;
	printf("\n b6 %d %c %c",*_index, _rawData[*_index], _rawData[*_index+1] );
	temp[i]->father = currentStruct;
	printf("\n b7 %d %c %c",*_index, _rawData[*_index], _rawData[*_index+1] );
	temp[i]->childs[0] = NULL;
	printf("\n b8 %d %c %c",*_index, _rawData[*_index], _rawData[*_index+1] );
	
	//free(currentStruct->childs);
	currentStruct->childs = temp;
	++currentStruct->numChilds;

	currentStruct = temp[i];
} // addChildToTXML

void CXMLParser::printXML(TXML* data){
	printSingleXML(data);
	
	for(vu8 i = 0; i < data->numChilds; ++i){
		printSingleXML(data->childs[i]);
	}
	
} // printXML

void CXMLParser::printSingleXML(TXML* data){
	if(data == NULL){
		printf("\nVacio");
		return;
	}
	printf("\n %s : %s  -  %d",data->string, data->value, data->numChilds);
} // printSingleXML

bool CXMLParser::isValidChar(volatile char c){
	// numbers   // lower case    // upper case  // character /
	return c > 21 && c < 125;
	//return  ( (c > 48 && c < 57) || (c > 65 && c < 90) || (c > 91 && c < 122) || c == 47); 
			
}

// Destructor clase CCharacterParser
CXMLParser::~CXMLParser(void) {

} // ~CCharacterParser



void CXMLParser::debug(){
	int index = 0;
	printf("\n");
	while(_rawData[index] != 0){
		printf("%c",_rawData[index] );
		++index;
	}
}

