/**************************************************************************/
/*
 Based on SD reader and MMA8451 code written by Adafruit
 Modified by A. Kleindolph
 */
/**************************************************************************/
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

Adafruit_MMA8451 mma = Adafruit_MMA8451();

File myFile;

const int chipSelect = 10;
float recordTime = 30*1000;   //length of time to record = seconds *1000

void setup(void) {

  Serial.begin(9600);

  //accel setup:
  Serial.println("Adafruit MMA8451 test!");

  if (! mma.begin()) {
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("MMA8451 found!");

  mma.setRange(MMA8451_RANGE_2_G);

  Serial.print("Range = "); 
  Serial.print(2 << mma.getRange());  
  Serial.println("G");
  //SD card setup:
  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
  pinMode(SS, OUTPUT);
  delay(1000);

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }

  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("datafun.csv", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    myFile.println("time,x,y,z");
    // close the file:
    myFile.close();
  } 
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening data file");
  }
}

void loop() {
  // Read the 'raw' data in 14-bit counts
  myFile = SD.open("datafun.csv", FILE_WRITE);
  mma.read();  //read accelerometer

  if ((myFile) && (millis()<recordTime)) {  //if recording time is not exceeded
    //print accel data to serial monitor
    Serial.print("X:\t"); 
    Serial.print(mma.x); 
    Serial.print("\tY:\t"); 
    Serial.print(mma.y); 
    Serial.print("\tZ:\t"); 
    Serial.print(mma.z); 
    Serial.println();

    /* Get a new sensor event */
    sensors_event_t event; 
    mma.getEvent(&event);

    /* Display the results (acceleration is measured in m/s^2) */
    Serial.print("X: \t"); 
    Serial.print(event.acceleration.x); 
    Serial.print("\t");
    Serial.print("Y: \t"); 
    Serial.print(event.acceleration.y); 
    Serial.print("\t");
    Serial.print("Z: \t"); 
    Serial.print(event.acceleration.z); 
    Serial.print("\t");
    Serial.println("m/s^2 ");

    //print accelerometer and time values
    myFile.print(millis()/1000);
    myFile.print(",");
    myFile.print(event.acceleration.x); 
    myFile.print(",");
    myFile.print(event.acceleration.y); 
    myFile.print(",");
    myFile.print(event.acceleration.z); 
    myFile.println(" ");
  } 

  else if ((myFile) && (millis()>recordTime)){
    // if time is up, stop recording data
    Serial.println("done recording");
    delay(10000);
  }

  else{
    // if the file didn't open, print an error:
    Serial.println("error opening data file");
  }
  myFile.close();

  delay(1000);  //time between readings
}


