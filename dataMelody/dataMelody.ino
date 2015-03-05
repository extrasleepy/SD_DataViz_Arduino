//Plays a melody based on collected data
//circuit: 8-ohm speaker on digital pin 3 

// paste data in { }brackets:
int melody[] = {/*your data here*/};

void setup() {
}

void loop() {
                                // iterate over the notes of the melody:
  for (int note = 0; note < sizeof(melody); note++) {
    //melody[note]=map(melody[note],0,30000,1000,10000);
    tone(8, melody[note]/30,melody[note]/30);
    delay(100);
    //delay(melody[note]/100);  //optional adjustment to delay
    noTone(8);
  }
  delay(1000);                //one second before song repeats
}
