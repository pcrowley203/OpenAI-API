#ifndef __CLASS_OPENAI__
#define __CLASS_OPENAI__

#include <cstring>


using namespace std;



class OpenAi {
	
	public:
	
		OpenAi(string p, string m, int mNOT, int t);
		~OpenAi();
		
		void CreateOutboundMessagePayload();
		string GetOutboundMessagePayload();
	
	
	private:
	
		string prompt;
		string model;
		int maximumNumberOfTokens;
		int temperature;

		string payLoad;
};



#endif



