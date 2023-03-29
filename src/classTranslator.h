#ifndef __TRANSLATOR__
#define __TRANSLATOR__

#undef BUFFLENLONG
#define BUFFLENLONG 131072


class Translator{
	
	public:
	
		Translator();
		~Translator();
		
		void SetInputString(const char* iS);
		char* GetOutputString();
		
		void Translate();
		
	private:
		
		char inputString[BUFFLENLONG];
		char outputString[BUFFLENLONG];
	
};

#endif