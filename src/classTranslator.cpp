#include <cstring>
#include <json/json.h>
#include <json/reader.h>
#include <json/value.h>


#include "classTranslator.h"



using namespace Json;
using namespace std;


Translator::Translator(){}
Translator::~Translator(){}


void Translator::SetInputString(string iS){
	
	inputString = iS;
	outputString = "";
}


string Translator::GetOutputString(){
	
	return outputString;
}


void Translator::Translate(){
	
	Value thisJsonValue;
	Reader thisJsonReader;
	
	thisJsonReader.parse(inputString, thisJsonValue, true);
	
	outputString = thisJsonValue["choices"][0]["text"].asString();
}
	
	
	
