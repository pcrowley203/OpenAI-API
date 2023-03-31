#include <string>
#include <cstring>
#include <curl/curl.h>
#include <curl/easy.h>


#include "classOpenAi.h"





OpenAi::OpenAi(string p, string m, int mNOT, int t){
	
	prompt = p,
	model = m;
	maximumNumberOfTokens = mNOT;
	temperature = t;
	
	payLoad = "";
}


OpenAi::~OpenAi(){}




string OpenAi::GetOutboundMessagePayload(){
	
	return payLoad;
}


void OpenAi::CreateOutboundMessagePayload(){
	
	payLoad = "{";
	
	payLoad += "\"prompt\":\"";
	payLoad += prompt;
	
	payLoad += "\",";
	
	payLoad += "\"model\":\"";
	payLoad += model;
	
	payLoad += "\",";
	
	payLoad += "\"max_tokens\":";
	payLoad += to_string(maximumNumberOfTokens);
	
	payLoad += ",";
	
	payLoad += "\"temperature\":";
	payLoad += to_string(temperature);
	
	payLoad += "}";
}
