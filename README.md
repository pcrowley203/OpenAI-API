OpenAI-API:  A very simple proof of concept API to ChatGPT.
 
The executable, once invoked, asks the user for a prompt, and then relays that prompt to ChatGPT.  It then receives ChatGPT's response, parses out the actual answer to the prompt, and prints that answer to the screen.  It then asks for another prompt.



To build this project:

export OPENAI_API_KEY="put your key here inside these quotes"
chmod 744 build.sh
./build.sh


To run:

bin/proofOfConcept.exe