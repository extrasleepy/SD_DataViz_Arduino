/****************************************
 * Example Sound Level Sketch for the 
 * Adafruit Microphone Amplifier
 ****************************************/
//Modified to woek with SD card by akleindolph

const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

#include <SPI.h>
#include <SD.h>

File myFile;

const int chipSelect = 10;

void setup() 
{
  Serial.begin(9600);
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
  myFile = SD.open("soundlev.csv", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to file...");
    // close the file:
    myFile.close();
    Serial.println("success!");
  } 
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening soundlev.csv");
  }
}


void loop() 
{
  unsigned long startMillis= millis();  // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  // collect data for 50 mS
  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(0);
    if (sample < 1024)  // toss out spurious readings
    {
      if (sample > signalMax)
      {
        signalMax = sample;  // save just the max levels
      }
      else if (sample < signalMin)
      {
        signalMin = sample;  // save just the min levels
      }
    }
  }
  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
  double volts = (peakToPeak * 3.3) / 1024;  // convert to volts
  delay(20);
  myFile = SD.open("soundlev.csv", FILE_WRITE);
  if (myFile) {
    myFile.print(millis());
    myFile.print(",");
    myFile.println(volts);
    
    Serial.print(millis()); 
    Serial.print(","); 
    Serial.println(volts);
  } 
  else{
    // if the file didn't open, print an error:
    Serial.println("error opening data file");
  }
  myFile.close();
}



