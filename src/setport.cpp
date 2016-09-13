#include <iostream>
using namespace std;

void printUsage();

int main(int argc, char *args[]) {

    // Check that there are arguments at all
    if (argc > 1) {

        string flag = args[1];

        // "-h" and "--help" cases
        if (flag == "-h" || flag == "--help") {

            // Check for more arguments, and then print usage like normal
            if (argc > 2) {
                cout << "No more arguments required for '-h' or '--help'\n";
            }
            printUsage();


            // "-p" and "--port" cases
        } else if (flag == "-p" || flag == "--port") {

            // Check for only one more argument after
            if (argc == 3) {

                try {
                    int portNum = stoi(args[2]);

                    // Make sure the port is within range
                    if (portNum > 1 && portNum < 65000) {

                        //~~~  SUCCESS!!! PORT IS SET ~~~~
                        cout << "listening on port " << portNum << endl;
                        // TODO: handle port setting

                    } else {
                        cout << "Port: " << portNum << " is not within proper port range." << endl;
                        printUsage();
                        return EXIT_FAILURE;
                    }
                } catch (const exception& e) {
                    cout << "invalid_argument for port flag" << endl;
                    printUsage();
                    return EXIT_FAILURE;
                }

            } else {
                cout << "Improper number of args for port setting: " << argc - 2 << endl;
                printUsage();
                return EXIT_FAILURE;
            }

        } else {
            // Unknown first arg
            cout << "Unknown argument: " << args[1] << endl;
            printUsage();
            return EXIT_FAILURE;
        }

    } else {
        cout << "portsetter requires arguments!" << endl;
        printUsage();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void printUsage() {
    cout << "Port Setter v1.0 ( https://stoopclub.ddns.net )\n"
            "USAGE:\n"
            "     portsetter [Options] {target}\n"
            "OPTIONS:\n"
            "     -h  ( --help )\n"
            "     -p  ( --port )  {port number}\n"
            "PORTS:\n"
            "     -- Only ports between 1 - 65000 are allowed\n"
            "EXAMPLES:\n"
            "     portsetter -p 8080\n"
            "     portsetter --port 8080\n"
            "     portsetter -h\n"
            "     portsetter --help" << endl;
}
