// Portions of this code adapted from https://forum.arduino.cc/index.php?topic=367987.msg2536880#msg2536880

// https://github.com/JChristensen/DS3232RTC, provides functions for
//interacting with RTC
#include "DS3232RTC.h"

// Time values sent over serial should be prefixed with a T to
// ensure we're getting the right values over serial
#define TIME_HEADER  "T"

// STart the program by notifying the user that we're ready to recieve
void setup()
{
	Serial.begin(9600);
	Serial.println("Waiting for sync message");
}

// Every second, check for a new time and update the current time with it.
// Otherwise, print the current time.
void loop()
{
	if (Serial.available()) {
		processSyncMessage();
	}
	if (timeStatus()!= timeNotSet) {
		digitalClockDisplay();  
	}
	delay(1000);
}

// Print the current time and date
void digitalClockDisplay()
{
	// digital clock display of the time
	Serial.print("GMT Time: ");
	Serial.print(hour());
	printDigits(minute());
	printDigits(second());
	Serial.print(' ');
	Serial.print(day());
	Serial.print(' ');
	Serial.print(month());
	Serial.print(' ');
	Serial.print(year());
	Serial.println();
}

// Print an int as a two digit number prefixed by a colon
void printDigits(int digits)
{
	Serial.print(':');
	// If our value is less than 10, pad with a 0
	if(digits < 10)
		Serial.print('0');
	Serial.print(digits);
}

// Get the message sent over serial and use it to set the current time and RTC
void processSyncMessage() {
	unsigned long pctime;
	const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013

	// Make sure this is a time transmission
	if(Serial.find(TIME_HEADER))
	{
		// Read the time, and if valid set the current time and RTC
		pctime = Serial.parseInt();
		if( pctime >= DEFAULT_TIME) { // check the integer is a valid time (greater than Jan 1 2013)
			setTime(pctime); // Sync Arduino clock to the time received on the serial port
			RTC.set(now()); // Set RTC to the current value of the Arduino clock
		}
	}
}
