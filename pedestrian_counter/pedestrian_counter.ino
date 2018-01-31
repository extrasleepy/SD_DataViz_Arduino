// This #include statement was automatically added by the Particle IDE.
//#include <Adafruit_VL53L0X.h>

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

//variables for eeprom
int address = 10;
int value;
int storedValue;
bool samePerson = FALSE;

void setup() {
  EEPROM.put(address, 0); //reset value back to 0 turn off to add even when power removed
  Serial.begin(115200);
  pinMode(D7,OUTPUT);

  EEPROM.get(address, storedValue);
  value = storedValue;
  //Particle.variable("value", value);

  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }

  Serial.println(F("VL53L0X API Simple Ranging example\n\n"));
}


void loop() {


  VL53L0X_RangingMeasurementData_t measure;

  Serial.print("Reading a measurement... ");
  //lox.rangingTest(&measure, true); // pass in 'true' to get debug data printout!
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
  } else {
    Serial.println(" out of range ");
    samePerson = FALSE;
  }

  if (measure.RangeMilliMeter>40 && measure.RangeMilliMeter<1100) {
    digitalWrite(D7,HIGH);

    if(samePerson==FALSE){
        value++;
        EEPROM.put(address, value);
        Particle.publish("interactions=", String(value));
        Serial.println(value);
        samePerson = TRUE;
    }
  }else{
    digitalWrite(D7,LOW);
  }
  delay(50);
}
