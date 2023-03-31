#ifndef __CLASS_OPENAI__
#define __CLASS_OPENAI__

#include <cstring>


using namespace std;

struct MemoryStruct {
	char *memory;
	size_t size;
};

size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);


class OpenAi {
	
	public:
	
		OpenAi(string eP, string pK, string m, int mNOT, int t);
		~OpenAi();
		
		void SendARequest(string p);
		string GetResponse();
	
	
	private:
	
		void CreateOutboundMessagePayload();
		void SendRequestAndReceiveResponse();
		
		string endPoint;
		string privateKey;
		string prompt;
		string model;
		int maximumNumberOfTokens;
		int temperature;

		string payLoad;
		string response;
};



#endif



