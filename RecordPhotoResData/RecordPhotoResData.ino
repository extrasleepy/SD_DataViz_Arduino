/*
 AnalogReadSerial with Button and SD storage
 Reads an analog input on pin A0, prints the result to the serial monitor.
 
 Attach the one pin of a photoresistor to pin A0, and the other pin to +5V.  
 Hook a 4.7K resistor to pin A2 as welland hook the other leg to GND.
 
 Attach pushbutton to PIN 3.  Make sure pin has 10K pull-down resistor hooked to GND.
 
 Based on Arduino and Adafruit sample code.
 Modified for LW Device Invention Class by akleindolph
 */

#include <SPI.h>
#include <SD.h>

int pushButton = 3;
File myFile;
const int chipSelect = 10;

void setup() {
  Serial.begin(9600);
  pinMode(pushButton, INPUT);
  Serial.print("Initializing SD card..."); 
  pinMode(SS, OUTPUT);
  delay(1000);

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("light.csv", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.println("writing to File!");
    myFile.print("Time,");
    myFile.println("Light");
    // close the file:
    myFile.close();
    Serial.println("success!");
  } 
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening light.csv");
  }
}

void loop() {
  int buttonState = digitalRead(pushButton);
  if (buttonState==HIGH){
    myFile = SD.open("light.csv", FILE_WRITE);
    int sensorValue = analogRead(A2);
    Serial.println(sensorValue);   //print light value to Serial monitor
    myFile.print(millis()/1000);  //record time in milliseconds
    myFile.print(",");
    myFile.println(sensorValue);
    myFile.close();
    delay(100);
  }
  delay(200);
  Serial.println("waiting");
}




