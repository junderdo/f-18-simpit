/**
 * @author Jeff Underdown <jeff.underdown@gmail.com>
 * @description command line tool for controlling PacLED64 controller board
 */
#include "stdafx.h"
#include "windows.h"
#include "PacDrive.h"
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
	
	string lastArgName;
	int intensity = 0;
	int address = 0;
	bool setIntensity = false;
	bool setAddress = false;

	for (int i = 0; i < argc; ++i) {
		string arg = argv[i];
		
		// if the last arg was an identifier then this one should be a value
		if (lastArgName == "a") {
			address = min(LED_CHANNEL_MAX, max(LED_CHANNEL_MIN, stoi(arg)));
			setAddress = true;
		}
		else if (lastArgName == "i") {
			intensity = min(LED_BRIGHTNESS_LEVEL_MAX, max(LED_BRIGHTNESS_LEVEL_MIN, stoi(arg)));
			setIntensity = true;
		}


		// is this arg an identifier?
		if (arg.substr(0, 1) == "-") {
			lastArgName = arg.substr(1, 1);
		} else {
			lastArgName = "";
		}
	}


	if (setAddress && setIntensity) {
		PacInitialize();

		Pac64SetLEDIntensity(0, address, (byte) intensity);

		cout << "address: " << address << "\n";
		cout << "intensity: " << intensity << "\n";

		PacShutdown();
	} else {
		throw "missing argument(s)";
	}


	return 0;
}
