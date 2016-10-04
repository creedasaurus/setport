#include <iostream>
#include <vector>
#include <string>
using namespace std;

const string LOG_FILE = "/tmp/testing-setport.tmp";
const string en[] = {"Testing:    ", "Expected:   ", "Status:     PASSED\n", "Status:     FAILED\n"};
const string es[] = {"Pruebas:    ", "Esperado:   ", "Estado:     PASADO\n", "Estado:     FALLADO\n"};
enum {TEST, EXPECT, STAT_PASS, STAT_FAIL};
const string LANGHOLDERS[] = {"LANGUAGE", "LC_ALL", "LC_MESSAGES", "LANG"};

void testCommand(const string& command, int expectedStatus, const string* msg);

int main(int argc, char *args[]) {
    
    	// ---------- Getting Language -------
	const string* msg = en;
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
			msg = es;
			break;
		}
		if (langCheckCount == 4 && envLang.substr(0,1) != "C") {
			cout << "No language found for " << envLang << ". Defaulting to English" << endl;
		}
	}
	//------ End getting language --------
    
    
    
    // Set of positive tests
    vector<string> positiveTests = { 
        "setport", 
        "setport -h",
        "setport --help",
        "setport -p 4040",
        "setport --port 4040",
        "setport -p -e",
        "setport -!",
        "setport -?",
        "setport --about",
        "setport --version",
        "setport -v"
    };

    // Set of negative tests
    vector<string> negativeTests = {
        "setport help",
        "setport -help",
        "setport --h",
        "setport -h --help",
        "setport -hs",
        "setport -p --port 9",
        "setport -p 77 33",
        "setport -p -21",
        "setport -p 0",
        "setport --port",
        "setport -p 90642",
        "setport -x 45321",
        "setport -P 714",
        "setport -p 1234fsd",
        "setport -p -asd",
        "setport -p -e BUTT_PORT",
    };

    
    // Positive Tests
    for (auto const test : positiveTests) {
        testCommand(test, 0, msg);
    }
    
    // Negative tests -
    for (auto const test : negativeTests) {
        testCommand(test, 1, msg);
    }
    
    return EXIT_SUCCESS;
}

void testCommand(const string& command, int expectedStatus, const string* msg) {
    cout << msg[TEST] + command << endl;
    
    string systemStringCall = command + " > " + LOG_FILE;
    int statusCode = system(systemStringCall.c_str()) / 256;
    
    cout << msg[EXPECT] << statusCode << endl;
    
    if (statusCode == expectedStatus) {
        cout << msg[STAT_PASS] << endl;
    } else if (statusCode != expectedStatus) {
        cout << msg[STAT_FAIL] << endl;
    }
}