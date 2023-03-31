#ifndef __TRANSLATOR__
#define __TRANSLATOR__

#include <cstring>


class Translator{
	
	public:
	
		Translator();
		~Translator();
		
		void SetInputString(string iS);
		string GetOutputString();
		
		void Translate();
		
	private:
		
		string inputString;
		string outputString;
	
};

#endif