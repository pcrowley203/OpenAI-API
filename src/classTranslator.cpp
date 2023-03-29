#include <cstring>
#include <cstdio>
#include <json/json.h>
#include <json/reader.h>
#include <json/value.h>


#include "classTranslator.h"

#undef BUFFLEN
#define BUFFLEN 1024


using namespace Json;
using namespace std;


Translator::Translator(){}
Translator::~Translator(){}


void Translator::SetInputString(const char* iS){
	
	strcpy(inputString, iS);
	strcpy(outputString, "\0");
}


char* Translator::GetOutputString(){
	
	return outputString;
}


void Translator::Translate(){
	
	Value thisJsonValue;
	Reader thisJsonReader;
	
	thisJsonReader.parse(string(inputString), thisJsonValue, true);
	
	sprintf(outputString, "%s", thisJsonValue["choices"][0]["text"].asString().c_str());
}
	
	
	
