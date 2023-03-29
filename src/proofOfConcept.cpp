#include <string>
#include <iostream>

#include "classOpenAi.h"
#include "classTranslator.h"

#define KEY "OPENAI_API_KEY"

#undef BUFFLEN
#define BUFFLEN 256

using namespace std;


int main(){
	
	string endPoint = "https://api.openai.com/v1/completions";
	string model = "text-davinci-003";
	int maximumNumberOfTokens = 200;
	int temperature = 0;
	
	string privateKey = getenv(KEY);
	
	OpenAi thisOpenAi(endPoint, privateKey, model, maximumNumberOfTokens, temperature);
	
	while (true){
		
		cout << "Give me a prompt, please.  (Type \"exit\" to exit.)" << endl << endl;
		string prompt;
		getline(cin, prompt);
		if (prompt == "exit") break;
		
		thisOpenAi.SendARequest(prompt);
		string response = thisOpenAi.GetResponse();
		
		Translator thisTranslator;
		thisTranslator.SetInputString(response.c_str());
		thisTranslator.Translate();
		string responseText = string(thisTranslator.GetOutputString());
		
		cout << responseText << endl << endl << endl;
	}
	
	return 0;
}