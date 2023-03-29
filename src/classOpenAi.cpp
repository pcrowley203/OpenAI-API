#include <string>
#include <cstring>
#include <curl/curl.h>
#include <curl/easy.h>


#include "classOpenAi.h"



#undef BUFFLEN
#define BUFFLEN 16




OpenAi::OpenAi(string eP, string pK, string m, int mNOT, int t){
	
	endPoint = eP;
	privateKey = pK;

	model = m;
	maximumNumberOfTokens = mNOT;
	temperature = t;
	
	strcpy(payLoad, "\0");
	strcpy(response, "\0");
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


	char auth[BUFFLEN_LONG];
	strcpy(auth, "Authorization:Bearer ");
	strcat(auth, privateKey.c_str());


	slist1 = NULL;
	slist1 = curl_slist_append(slist1, "Content-Type:application/json");
	slist1 = curl_slist_append(slist1, auth);
	
	
	
	hnd = curl_easy_init();
	curl_easy_setopt(hnd, CURLOPT_BUFFERSIZE, 102400L);
	curl_easy_setopt(hnd, CURLOPT_URL, endPoint.c_str());
	curl_easy_setopt(hnd, CURLOPT_NOPROGRESS, 1L);
	curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, payLoad);
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
	
	strcpy(response, chunk.memory);

	curl_easy_cleanup(hnd);
	hnd = NULL;
	curl_slist_free_all(slist1);
	slist1 = NULL;
}

void OpenAi::CreateOutboundMessagePayload(){
	
	strcpy(payLoad, "{");
	
	strcat(payLoad, "\"model\":\"");
	strcat(payLoad, model.c_str());
	
	strcat(payLoad, "\",");
	
	strcat(payLoad, "\"prompt\":\"");
	strcat(payLoad, prompt.c_str());
	
	strcat(payLoad, "\",");
	
	strcat(payLoad, "\"max_tokens\":");
	char maximumNumberOfTokens_str[BUFFLEN];
	sprintf(maximumNumberOfTokens_str,"%d",maximumNumberOfTokens);
	strcat(payLoad, maximumNumberOfTokens_str);
	
	strcat(payLoad, ",");
	
	strcat(payLoad, "\"temperature\":");
	char temperature_str[BUFFLEN];
	sprintf(temperature_str,"%d",temperature);
	strcat(payLoad, temperature_str);
	
	strcat(payLoad, "}");
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
	









// #include <iostream>

// OptimalBlue::OptimalBlue(Loan* aLoan, int verbo){
	// thisLoan = aLoan;
	// verbosity = verbo;
	
	// strcpy(accessToken, "\0");
	// strcpy(rawPriceData, "\0");
	// strcpy(payLoad, "\0");
// }

// OptimalBlue::~OptimalBlue(){}



// void OptimalBlue::SetAccessToken(char* aT){
	// strcpy(accessToken, aT);
// }


// char* OptimalBlue::GetAccessToken(){
	
	// return accessToken;
// }


// void OptimalBlue::CreateOptions(){
	
	// CreateMessageToOptimalBlue();
	// GetRawPriceData();
	// ParsePriceData();
	// DeselectUsdaLoans();
	// DeselectLoansPricedBelowThreshold();
	// DeselectDominatedLoans();
// }


// void OptimalBlue::DeselectUsdaLoans(){
	
	// for (int i=0; i<productMenu.size(); i++){
		
		// LoanOption* option = productMenu[i];
		
		// if (!strncmp(option->GetProductCode(),"USDA",4)) option->SetRetain(false);
	// }
// }


// void OptimalBlue::DeselectLoansPricedBelowThreshold(){
	
	// for (int i=0; i<productMenu.size(); i++){
		
		// LoanOption* option = productMenu[i];
		
		// if (option->GetPrice() < PRICE_THRESHOLD ) option->SetRetain(false);
	// }
// }
	

// void OptimalBlue::DeselectDominatedLoans(){
	
	// for (int i=0; i<productMenu.size(); i++){

		// LoanOption* option1 = productMenu[i];
		
		// for (int j=i+1; j<productMenu.size(); j++){
			
			// LoanOption* option2 = productMenu[j];
			
			// if (
				// !strcmp(option1->GetAmortizationType(), option2->GetAmortizationType()) &&
				// !strcmp(option1->GetArmIndex(), option2->GetArmIndex()) &&
				// option1->GetTerm() == option2->GetTerm() &&
				// option1->GetRetain() &&
				// option2->GetRetain()
			// ){
				// if (
					// option1->GetRate() <= option2->GetRate() &&
					// (
						// !strcmp(option1->GetAmortizationType(), "Fixed") ||
						// option1->GetArmMargin() <= option2->GetArmMargin()
					// )
				// ){
					// option2->SetRetain(false);
				// } else if (
					// option1->GetRate() >= option2->GetRate() &&
					// (
						// !strcmp(option1->GetAmortizationType(), "Fixed") ||
						// option1->GetArmMargin() >= option2->GetArmMargin()
					// )
				// ){
					// option1->SetRetain(false);
				// }
			// }
		// }
	// }
// }
	
	
	
// void OptimalBlue::GetResults(vector <LoanOption*> &dataSet){
	
	// for (int i=0; i<productMenu.size(); i++){
		
		// LoanOption* option = productMenu[i];
		
		// if (option->GetRetain()) dataSet.push_back(option);
		// else free(option);
	// }
// }
	
	
// void OptimalBlue::ParsePriceData(){
	
	// if (
			// strstr(rawPriceData,"\"products\":[") &&
			// !strstr(rawPriceData,"\"products\":[]")
		// ){
			
		// char* products;
		
		// strtok(rawPriceData,"[]");
		// products = strtok(NULL,"[]");
		
		// bool first1 = true;
		// char* aProduct;
		// char* ptr1;
		
		// while (aProduct=strtok_r(first1 ? products : NULL, "{}", &ptr1)){
			
			// first1 = false;
			
			// if (strcmp(aProduct,",")){
				
				// bool first2 = true;
				// char* anAttributeValuePair;
				// char* aValue;
				// char* ptr2;
				
				// if (verbosity>0) printf("%d\t", productMenu.size());
				
				// LoanOption* newOption = new LoanOption;
				// productMenu.push_back(newOption);
				// newOption->SetLoan(thisLoan); 
				
				// while (anAttributeValuePair=strtok_r(first2 ? aProduct : NULL, ",", &ptr2)){
					
					// first2 = false;
					// char* anAttribute;
					// char* aValue;
					
					// anAttribute=strtok(anAttributeValuePair,":\"");
					// aValue=strtok(NULL, ":\"");
					
					// if (false){
						// ;
					// } else if (!strcmp(anAttribute, "amortizationType")){
						// newOption->SetAmortizationType(aValue);
					// } else if (!strcmp(anAttribute, "armIndex") && aValue){
						// newOption->SetArmIndex(aValue);
					// } else if (!strcmp(anAttribute, "armMargin") && aValue){
						// newOption->SetArmMargin(atof(aValue)/100);
					// } else if (!strcmp(anAttribute, "productCode")){
						// newOption->SetProductCode(aValue);
					// } else if (!strcmp(anAttribute, "productName")){
						// newOption->SetProductName(aValue);
					// } else if (!strcmp(anAttribute, "loanTerm")){
						// newOption->SetTerm(12*atoi(aValue));
					// } else if (!strcmp(anAttribute, "price")){
						// newOption->SetPrice(atof(aValue)/100);
					// } else if (!strcmp(anAttribute, "rate")){
						// newOption->SetRate(atof(aValue)/100);
					// } else {
						// ;
					// }
				// }
			// }
					
					
			// // printf("%d\n", productMenu[productMenu.size()-1]->GetTerm());
					
		// }
	// }
// }






// int OptimalBlue::ObtainAccessToken(){
	// CURLcode ret;
	// CURL *hnd;
	// struct curl_slist *slist1;
	
	// char messagePayLoad[32768];
	
	// struct MemoryStruct chunk;
	// chunk.memory = (char *)malloc(1);
	// chunk.size = 0;

	// slist1 = NULL;
	// slist1 = curl_slist_append(slist1, "Content-Type:application/x-www-form-urlencoded");

	// hnd = curl_easy_init();
	// curl_easy_setopt(hnd, CURLOPT_BUFFERSIZE, 102400L);
	// curl_easy_setopt(hnd, CURLOPT_URL, "https://login.microsoftonline.com/marketplaceauth.optimalblue.com/oauth2/token");
	// curl_easy_setopt(hnd, CURLOPT_NOPROGRESS, 1L);
	
	// strcpy(messagePayLoad, "resource=https://marketplaceauth.optimalblue.com/d35ae893-2367-40b5-a9b4-bfab3acb7991"); strcat(messagePayLoad, "&");
	// strcat(messagePayLoad, "client_id=a10832b6-c753-452c-bc7d-0b3e7f55db4b"); strcat(messagePayLoad, "&");
	// strcat(messagePayLoad, "client_secret=%2B2LPcTd%2FTNnZacYSjxekm4ZJODPfgP7Pd64PrHNx014%3D"); strcat(messagePayLoad, "&");
	// strcat(messagePayLoad, "grant_type=client_credentials");
	
	// curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, messagePayLoad);
	// curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)-1);
	// curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, slist1);
	// curl_easy_setopt(hnd, CURLOPT_USERAGENT, "curl/7.61.1");
	// curl_easy_setopt(hnd, CURLOPT_MAXREDIRS, 50L);
	// curl_easy_setopt(hnd, CURLOPT_HTTP_VERSION, (long)CURL_HTTP_VERSION_2TLS);
	// curl_easy_setopt(hnd, CURLOPT_SSH_KNOWNHOSTS, "/home/paul.crowley/.ssh/known_hosts");
	// curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "POST");
	// curl_easy_setopt(hnd, CURLOPT_TCP_KEEPALIVE, 1L);
	// curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	// curl_easy_setopt(hnd, CURLOPT_WRITEDATA, (void *)&chunk);


	// ret = curl_easy_perform(hnd);
	
	
	// char* saveptr;
	// char* keyValuePair;
	// char* key;
	// char* value;
	// bool first=true;
	// char* access_token;
	
	// while(true){
		// keyValuePair = strtok_r(first ? chunk.memory : NULL, ",", &saveptr);
		// key = strtok(keyValuePair,":");
		// value = strtok(NULL,":");
		
		// if (!strcmp(key, "\"access_token\"")){
			// access_token = strtok(value, "\"");
			// break;
		// }
		
		// first=false;
	// }
	
	// strcpy(accessToken, access_token);
	
	// if (verbosity>1){
		// printf("%s\n\n",accessToken);
		// fflush(stdout);
	// }

	// curl_easy_cleanup(hnd);
	// hnd = NULL;
	// curl_slist_free_all(slist1);
	// slist1 = NULL;
  
	// return (int)ret;
// }


