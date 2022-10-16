/**
 * @author Jeff Underdown <jeff.underdown@gmail.com>
 * @description command line tool for controlling PacLED64 controller board
 */
#include "stdafx.h"
#include "windows.h"
#include "PacDrive.h"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
	
	string lastArgName;
	int intensity = 0;
	int address = 0;

	for (int i = 0; i < argc; ++i) {
		string arg = argv[i];
		
		// if the last arg was an identifier then this one should be a value
		if (lastArgName == "a") {
			address = stoi(arg);
		}
		else if (lastArgName == "i") {
			intensity = stoi(arg);
		}


		// is this arg an identifier?
		if (arg.substr(0, 1) == "-") {
			lastArgName = arg.substr(1, 1);
		} else {
			lastArgName = "";
		}
	}

	PacInitialize();

	Pac64SetLEDIntensity(0, address, (byte) intensity);

	cout << "address: " << address << "\n";
	cout << "intensity: " << intensity << "\n";
	cout << "done" << "\n";

	PacShutdown();

	return 0;
}
