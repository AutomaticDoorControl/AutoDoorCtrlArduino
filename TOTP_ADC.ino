
#include <sha1.h>     //sha1.h and TOTP.h allow for TOTP authentification
#include <TOTP.h>
#include <DS3232RTC.h>  //https://github.com/JChristensen/DS3232RTC

//Key for -ADC-
uint8_t hmacKey[] = {0xb8, 0x52, 0xaf, 0xc9, 0x91, 0x82, 0x5b, 0xf9, 0x72, 0x8f, 0x99, 0xd1, 0x31, 0x65, 0xc1, 0xe5, 0xde, 0xe8, 0xd2, 0xea, 0x71, 0xa7, 0x63, 0x39, 0x38, 0x24, 0xe1, 0xe2, 0x94, 0xd2, 0x29, 0x3f};

//Key for -SAGE_SOUTH-
//uint8_t hmacKey[] = {0x6d, 0x64, 0x3f, 0x8b, 0xda, 0xeb, 0xf8, 0x7a, 0x45, 0x72, 0x27, 0x12, 0x78, 0x48, 0xca, 0x91, 0xfd, 0xf1, 0x7e, 0x94, 0xa3, 0x28, 0x7e, 0x91, 0xb6, 0xe5, 0x3f, 0xa1, 0xec, 0xf6, 0x1a, 0xe0};

//Key for -LALLY_NORTH-
//uint8_t hmacKey[] = {0xe0, 0x56, 0x37, 0xef, 0xed, 0xff, 0xae, 0x61, 0x2b, 0x9b, 0x03, 0x1c, 0x03, 0xa4, 0x62, 0x3c, 0xfa, 0xcf, 0x70, 0x6c, 0xdf, 0x4f, 0xe7, 0x02, 0xba, 0x3e, 0x4e, 0xfa, 0x66, 0xd8, 0xc0, 0x60};

//Key for -SAGE_EAST-
//uint8_t hmacKey[] = {0xf1, 0x83, 0x92, 0xef, 0xa0, 0x7c, 0x46, 0x92, 0x64, 0x4b, 0x86, 0xa1, 0xc5, 0x4b, 0xf3, 0xbd, 0xf5, 0xf8, 0x24, 0xfc, 0x5d, 0x25, 0xd6, 0xc9, 0xf5, 0x15, 0xd6, 0x7b, 0x38, 0x1b, 0x4a, 0x59};

//Set up variables
TOTP totp = TOTP(hmacKey, 32);
String temp;
String code;
#define DOOR_PIN 13

void setup() {

    
    pinMode(DOOR_PIN, OUTPUT);
    Serial.begin(9600);
    //If time gets messed up you need to reset it (takes about 7 seconds to upload)
//  setTime(13, 45, 0, 1, 11, 2019);
//  RTC.set(now());
    
    setSyncProvider(RTC.get);   // the function to get the time from the RTC
    if(timeStatus() != timeSet)
        Serial.println("Unable to sync with the RTC");
    else
        Serial.println("RTC has set the system time");
  
  // Adjust the following values to match the current date and time
  // and power on Arduino at the time set (use GMT timezone!)
}

void loop() {
  //Loops when recieves an input
  if(Serial.available() > 0){
    code = "";
    temp = Serial.readString();
    for(int i=0; i < 6; i++){
        code += temp[i];
    }
    //Time since epoch
    time_t current_time =  RTC.get();
    //Print info to make sure GMT timezone is correct
    Serial.println(current_time);
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

    //Get the code
    char* newCode = totp.getCode(current_time);
    String correct(newCode);
    if(code.equals(correct)) {
      Serial.println("Door Open");
      digitalWrite(DOOR_PIN, HIGH);
      delay(2000);
      digitalWrite(DOOR_PIN, LOW);
      Serial.println("Door is now closing");
    }  
    else{
      Serial.println("Invalid token");
      digitalWrite(DOOR_PIN, LOW);
    }
    Serial.println(code);
    Serial.println(correct);
  }
}


void printDigits(int digits)
{
    // utility function for digital clock display: prints preceding colon and leading 0
    Serial.print(':');
    if(digits < 10)
        Serial.print('0');
    Serial.print(digits);
}
