#ifndef __CLASS_HTTP__
#define __CLASS_HTTP__

#include <cstring>


using namespace std;



struct MemoryStruct {
	char *memory;
	size_t size;
};

size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);


class Http {
	
	public:
	
		Http(string eP, string pK);
		~Http();
		
		void SendRequestAndReceiveResponse(string pL);
		string GetResponse();
	
	
	private:
		
		string endPoint;
		string privateKey;

		string payLoad;
		string response;
};



#endif



