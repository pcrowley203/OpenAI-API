#include <string>
#include <iostream>

#include "classOpenAi.h"
#include "classTranslator.h"
#include "classHttp.cpp"

#define KEY "OPENAI_API_KEY"


using namespace std;


int main(){
	
	string endPoint = "https://api.openai.com/v1/completions";
	string model = "text-davinci-003";
	int maximumNumberOfTokens = 200;
	int temperature = 0;
	
	string privateKey = getenv(KEY);
	
	Http thisHttp(endPoint, privateKey);
	
	while (true){
		
		cout << endl << "Give me a prompt, please.  (Type \"exit\" to exit.)" << endl << endl;
		string prompt;
		getline(cin, prompt);
		if (prompt == "exit") break;
		
		OpenAi thisOpenAi(prompt, model, maximumNumberOfTokens, temperature);
		thisOpenAi.CreateOutboundMessagePayload();
		string payLoad = thisOpenAi.GetOutboundMessagePayload();
	
		thisHttp.SendRequestAndReceiveResponse(payLoad);
		string response = thisHttp.GetResponse();
		
		Translator thisTranslator;
		thisTranslator.SetInputString(response);
		thisTranslator.Translate();
		string responseText = thisTranslator.GetOutputString();
		
		cout << responseText << endl << endl << endl;
	}
	
	return 0;
}