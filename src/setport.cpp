#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

enum messages { 
	NEEDS_ARGS, 
	NO_MORE_ARGS, 
	PORT_TOOMANY, 
	NO_ENV, 
	INVALID_ARG_PORT, 
	PORT_NO_ALPHA, 
	PORT_RANGE, 
	LISTENING, 
	UNKNOWN_ARG };
	
const string LANGHOLDERS[] = {"LANGUAGE", "LC_ALL", "LC_MESSAGES", "LANG"};
const string version = "v0.1.0a";

//Function to get the text from a file and save it as a string for use
string getFileText(const string&);

int main(int argc, char *args[]) {
	
	
	// ---------- Getting Language -------
	string loc = "en";
	char* envVar;
	string envLang = "";
	int langCheckCount = 0;
	// check every lang holder in order
	// -- if no identifiable language is found, default to English
	for (const auto i: LANGHOLDERS) {
		langCheckCount++;
		if (envVar = getenv(i.c_str())) {
			envLang = envVar;
		}	
		if (envLang.substr(0,2) == "en") {
			break;
		}
		if (envLang.substr(0,2) == "es") {
			loc = "es";
			break;
		}
		if (langCheckCount == 4 && envLang.substr(0,1) != "C") {
			cout << "No language found for " << envLang << ". Defaulting to English" << endl;
		}
	}
	//------ End getting language --------

	
	
	// Get the warning text strings depending on the locale
	vector<string> status;
	fstream inFile("/usr/local/etc/setport/setport.warnings_" + loc + ".txt");
	string temp;
	if (inFile.is_open()) {
		while (getline(inFile, temp)) {
			status.push_back(temp);
		}
		inFile.close();
	}
	//----- end getting warning strings ------

	
	// Load Usage text and About text depending on locale
	string usageText = getFileText("/usr/local/etc/setport/setport.usage_" + loc + ".txt");
	string aboutText = getFileText("/usr/local/etc/setport/setport.about_" + loc + ".txt");


	// Check that there are arguments at all
	if (argc == 1) {
		cout << status[NEEDS_ARGS] << endl;
		cout << usageText;
		return EXIT_SUCCESS;
	}

	string flag = args[1];

	//--------------------------------------------------- HELP case
	if (flag == "-h" || flag == "--help" || flag == "-?") {
		
		// Check for more arguments, and then print usage like normal
		if (argc > 2) {
			cout << status[NO_MORE_ARGS] << flag << endl;
			cout << usageText;
			return EXIT_FAILURE;
		}
		
		cout << usageText;
        return EXIT_SUCCESS;
        
	} //------------------------------------------------ ABOUT case
	else if (flag == "-!" || flag == "--about") {
		
		// Check for more arguments, and then print usage like normal
		if (argc > 2) {
			cout << status[NO_MORE_ARGS] << flag << endl;
			cout << usageText;
			return EXIT_FAILURE;
		}
		
		cout << aboutText;
        return EXIT_SUCCESS;
        
	} //------------------------------------------------ VERSION case
	else if (flag == "-v" || flag == "--version") {
		
		// Check for more arguments, and then print usage like normal
		if (argc > 2) {
			cout << status[NO_MORE_ARGS] << flag << endl;
			cout << usageText;
			return EXIT_FAILURE;
		}
		
		cout << version << endl;
        return EXIT_SUCCESS;
        
	} //------------------------------------------------ PORT Case
	else if (flag == "-p" || flag == "--port") {
		
		string portArg;
		int portNum;
		
		if (argc == 2 || argc > 4) {
			cout << status[PORT_TOOMANY] << endl;
			cout << usageText;
			return EXIT_FAILURE;
		}
			
		portArg = args[2];
		
		//------------------------------------------------ Env-Port Case
		if (portArg == "-e") {
			char* env;
			string envPort = "PORT";
			
			if (argc == 4) {
				envPort = args[3];
			}
			
			if ( env = getenv(envPort.c_str()) ) {
				portArg = env;
			}
			else {
				cout << status[NO_ENV] << envPort << endl;
				return EXIT_FAILURE;
			}
			
		} 
		else {
			if (argc > 3) {
				cout << status[INVALID_ARG_PORT] << endl;
				cout << usageText;
				return EXIT_FAILURE;
			}
		}
		
		//--------------------- PARSE PORT ---------------------------
		try {
			
			string::size_type postNum;
			portNum = stoi(portArg, &postNum);
			
			// if part of the number is a letter
			if (isalpha(portArg[postNum])) {
				cout << status[PORT_NO_ALPHA] << endl;
				return EXIT_FAILURE;
			}
			
		} // NaN
		catch (const exception& e) {
			cout << status[INVALID_ARG_PORT] << endl;
			cout << usageText;
			return EXIT_FAILURE;
		}
		
		
		//--------------------- RANGE CHECK ---------------------------
		if (portNum < 1 || portNum > 65000) {
			cout << status[PORT_RANGE] << endl;
			cout << usageText;
			return EXIT_FAILURE;
		}
		
			
		//--------------------- SUCCESS ---------------------------
		cout << status[LISTENING] << portNum << endl;
		// TODO: handle port

	}
	else {
		// Unknown first arg
		cout << status[UNKNOWN_ARG] << args[1] << endl;
		cout << usageText;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}


// Parse file text to use for output
string getFileText(const string& inputFileName) {
	string temp;
	string fileText = "";
	
	fstream inFile(inputFileName);
	
	if (inFile.is_open()) {
		while (getline(inFile, temp)) {
			fileText += temp;
			fileText += '\n';
		}
		inFile.close();
	}
	return fileText;
}
