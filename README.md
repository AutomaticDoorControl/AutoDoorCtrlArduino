# Automatic Door Control Arduino
Main repository of all Arduino-related files and programs belonging to the ADC project.
The Arduino portion of the ADC project is tasked with recieving a 6 digit TOTP over bluetooth, comparing the TOTP to one generated using the onboard RTC and HMAC private key, and if the TOTP matches firing a relay to trigger the door opening.

## How to Wire HC-08: (Also shown in Circuit_Diagrams/ADC_circuit)
1. VCC goes to 5V power supply on arduino
2. GND goes to ground power on arudino
3. TXD goes to Digital pin 10 on arduino
4. RXD goes to Digital pin 11 on arduino
5. The other two (State and FN) don't touch

## How to wire the RTC: (also shown in Circuit_Diagrams/ADC_Circuit)
1. GND goes to the ground on the arduino
2. VCC goes to the 3.5V power supply (5V also works but recommended use is 3.5V)
3. SDA goes to Analogin Pin A4
4. SCL goes to Analogin Pin A5
5. 32K and SQW don't touch

## How to setup Arduino:

1. Wire the arduino up correctly
3. First set up the time to the RTC by uploading RTC.ino to the arduino and setting the current time in the code
4. Next you might want to rename the HC-08 so you can add it to the API. The code rename.ino can help with renaming the HC-08 module
5. Last step is to upload the TOTP_ADC code and select the correct key for the specific door (note that we use https://github.com/lucadentella/TOTP-Arduino/tree/master/ for TOTP generation and https://github.com/JChristensen/DS3232RTC for the RTC)
