OpenAI-API:  A VERY simple proof of concept API to ChatGPT.
 
The executable, once invoked, asks the user for a prompt, and then relays that prompt to ChatGPT.  It then receives ChatGPT's response, parses out the actual answer to the prompt, and prints that answer to the screen.  It then asks for another prompt.



To build this project, you will need to have the following packages installed:  curl, curl-devel, jsoncpp, and jsoncpp-devel.

Once those are installed, at the top level of the repo, call:

export OPENAI_API_KEY="put your key here inside these quotes"
chmod 744 build.sh
./build.sh


To run:

bin/proofOfConcept.exe