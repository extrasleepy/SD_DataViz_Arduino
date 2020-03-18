int photoresistor = A0; // This is where your photoresistor is plugged in.
int analogValue = 0; // Here we are declaring the integer variable analogvalue, which we will use later to store the value of the photoresistor.
int averageValue = 0;
int averageLoops = 10;

void setup() {
    pinMode(photoresistor,INPUT);  // Our photoresistor pin is input (reading the photoresistor)
    pinMode(D7,OUTPUT);    //built in LED
    // We are going to declare a Particle.variable() here so that we can access the value of the photoresistor from the cloud.
    Particle.variable("analogvalue", analogValue);
}

void loop() {
   
   for (int i=0; i<averageLoops; i++){  //collect data a certain number of times
    // check to see what the value of the photoresistor is and store it in the int variable analogvalue
        digitalWrite(D7,HIGH);
        analogValue = analogRead(A0);
        averageValue+=analogValue;
        delay(100);
    }
    
    digitalWrite(D7,LOW);
  
    averageValue=averageValue/averageLoops;     //divide to get average
    Serial.println(averageValue);
    
    String photoresistor = String(averageValue);   //store analogvalue as a String variable to publish
    Particle.publish("sensor value", photoresistor);   //publish the name of the event and the value of the sensor
    
    delay(1000);
}
