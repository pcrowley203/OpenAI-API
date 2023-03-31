#include <string>
#include <cstring>
#include <curl/curl.h>
#include <curl/easy.h>


#include "classOpenAi.h"





OpenAi::OpenAi(string eP, string pK, string m, int mNOT, int t){
	
	endPoint = eP;
	privateKey = pK;

	model = m;
	maximumNumberOfTokens = mNOT;
	temperature = t;
	
	payLoad = "";
	response = "";
}


OpenAi::~OpenAi(){}


void OpenAi::SendARequest(string p){
	
	prompt = p;
	
	CreateOutboundMessagePayload();
	SendRequestAndReceiveResponse();
}


string OpenAi::GetResponse(){
	
	return string(response);
}



void OpenAi::SendRequestAndReceiveResponse(){
	
	CURL *hnd;
	struct curl_slist *slist1;
	
	
	struct MemoryStruct chunk;
	chunk.memory = (char *)malloc(1);
	chunk.size = 0;


	string auth = "Authorization:Bearer ";
	auth += privateKey;


	slist1 = NULL;
	slist1 = curl_slist_append(slist1, "Content-Type:application/json");
	slist1 = curl_slist_append(slist1, auth.c_str());
	
	
	hnd = curl_easy_init();
	
	
	curl_easy_setopt(hnd, CURLOPT_BUFFERSIZE, 102400L);
	curl_easy_setopt(hnd, CURLOPT_URL, endPoint.c_str());
	curl_easy_setopt(hnd, CURLOPT_NOPROGRESS, 1L);
	curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, payLoad.c_str());
	curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)-1);
	curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, slist1);
	curl_easy_setopt(hnd, CURLOPT_USERAGENT, "curl/7.61.1");
	curl_easy_setopt(hnd, CURLOPT_MAXREDIRS, 50L);
	curl_easy_setopt(hnd, CURLOPT_HTTP_VERSION, (long)CURL_HTTP_VERSION_2TLS);
	curl_easy_setopt(hnd, CURLOPT_SSH_KNOWNHOSTS, "/home/paul.crowley/.ssh/known_hosts");
	curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "POST");
	curl_easy_setopt(hnd, CURLOPT_TCP_KEEPALIVE, 1L);
	curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	curl_easy_setopt(hnd, CURLOPT_WRITEDATA, (void *)&chunk);


	curl_easy_perform(hnd);
	
	response = string(chunk.memory);

	curl_easy_cleanup(hnd);
	hnd = NULL;
	curl_slist_free_all(slist1);
	slist1 = NULL;
}

void OpenAi::CreateOutboundMessagePayload(){
	
	payLoad = "{";
	
	payLoad += "\"model\":\"";
	payLoad += model;
	
	payLoad += "\",";
	
	payLoad += "\"prompt\":\"";
	payLoad += prompt;
	
	payLoad += "\",";
	
	payLoad += "\"max_tokens\":";
	payLoad += itostring(maximumNumberOfTokens);
	
	payLoad += ",";
	
	payLoad += "\"temperature\":";
	payLoad += itoa(temperature);
	
	payLoad += "}";
}
	
	
	
size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp){
	
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)userp;

	char *ptr = (char *)realloc(mem->memory, mem->size + realsize + 1);
	
	if(!ptr) {
		printf("not enough memory (realloc returned NULL)\n");
		fflush(stdout);
		return 0;
	}

	mem->memory = ptr;
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}
	
