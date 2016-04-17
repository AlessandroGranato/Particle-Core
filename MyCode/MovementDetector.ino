//Laser Movement Detector with Led

//Leds
int led = D0; //the led that lights up when something breaks the connection laser-photoresistor
int boardLed = D7; //integrated led in the core, needed for calibration
int photoresistor = A0; // one end of the photoresistor is connected here, and we will read info from this pin
int power = A5; //one end of the photoresistor is connected here, and will receive the power

int intactValue; // avg value that the photoresistor reads when the beam is intact
int brokenValue; // avg value that the photoresistor reads when the beam is broken
int beamThreshold; // value halfway between intactvalue and brokenValue, above which we will assume the led is on and below which we will assume it is off.

bool beamBroken = false; // flag used to update status

void setup() {
    
    pinMode(led,OUTPUT); // LED pin is output (lighting up the LED)
    pinMode(boardLed,OUTPUT); // boardLed is output as well
    pinMode(photoresistor,INPUT);  //Photoresistor pin is input (reading the photoresistor)
    pinMode(power,OUTPUT); // The other photoresistor pin must send power to the circuit.
    
    digitalWrite(power,HIGH); //power to the photoresistor is HIGH

    //CALIBRATION
    
    //boardedLed set on high value, starting the calibration collecting data about light around the photoresistor when laser is turned off
    digitalWrite(boardLed,HIGH);
    // 5 seconds for the user to understand what the program does. It can be set to lower value of course
    delay(5000);
    
     // Then, the D7 LED will go off.
    digitalWrite(boardLed,LOW);
    delay(500);
    
    // Now we'll take some readings (used later for the avg value of light when laser beam is broken)
    int broken1 = analogRead(photoresistor); // read photoresistor
    delay(200); // wait 200 milliseconds
    int broken2 = analogRead(photoresistor); // read photoresistor
    delay(1000); // wait 300 milliseconds
    
    // Now flash to let us know that you've taken the readings...
    digitalWrite(boardLed,HIGH);
    delay(100);
    digitalWrite(boardLed,LOW);
    delay(100);
    digitalWrite(boardLed,HIGH);
    delay(100);
    digitalWrite(boardLed,LOW);
    delay(100);
    
    //boardedLed and Led on high value, turn on the laser and point it to the photoresistor
    digitalWrite(boardLed,HIGH);
    digitalWrite(led,HIGH);
    // 5 seconds are given to the user in order to turn on the laser and point it to the photoresistor
    delay(5000);
    
    // The D7 LED will turn off...
    digitalWrite(boardLed,LOW);
    
    // Now we'll take some readings (used later for the avg value of light when laser beam is intact)
    int intact1 = analogRead(photoresistor); // read photoresistor
    delay(200); // wait 200 milliseconds
    int intact2 = analogRead(photoresistor); // read photoresistor
    delay(1000); // wait 1 second
    
    // Now flash the D7 LED on and off three times to let us know that we're ready to go!
    digitalWrite(boardLed,HIGH);
    delay(100);
    digitalWrite(boardLed,LOW);
    delay(100);
    digitalWrite(boardLed,HIGH);
    delay(100);
    digitalWrite(boardLed,LOW);
    delay(100);
    digitalWrite(boardLed,HIGH);
    delay(100);
    digitalWrite(boardLed,LOW);
    

    // Now we average the "on" and "off" values to get an idea of what the resistance will be when the LED is on and off
    brokenValue = (broken1+broken2)/2;
    intactValue = (intact1+intact2)/2;
    
    // Let's also calculate the value between intactValue and brokenValue, above which we will assume the laser beam is intact and below which we assume the laser beam is broken.
    beamThreshold = (intactValue+brokenValue)/2;
    
}

void loop() {

    //Situation in which the laser beam is broken due to some reasons.
    if (analogRead(photoresistor)<beamThreshold) {
        
        //If the laser beam was intact in the previous loop, then something changed just now, and we have to update the system  
        if(beamBroken == false) {
            
            Particle.publish("beamStatus","broken",60,PRIVATE); // Send a message to the dashboard
            digitalWrite(led,HIGH); // Set the led on high value, in order to tell us that something is blocking the laser beam
            beamBroken = true; // updrate beamBroken value
        }
    }
    
    //Situation in which the laser beam is intact.  
    else {

        //If the laser beam was broken in the previous loop, then something changed just now, and we have to update the system    
        if(beamBroken == true) {
            
            Particle.publish("beamStatus","intact",60,PRIVATE); // Send a message to the dashboard
            digitalWrite(led,LOW);  // Set the led on low value, in order to tell us that nothing is interrupting the laser beam
            beamBroken = false; // updrate beamBroken value
        }
    }
    
    delay(100); 
  
}
