//This program will read the value from the photoresistor

int led = D0; //led is plugged in D0 pin.
int photoresistor = A0; //photoresistor is plugged in A0 pin (analogic)
int power = A5; //the photoresistor second end is plugged here. In this way I have a constant voltage sent to A0 and I can read the value from there.

int analogValue; // variable that stores the value of the photoresistor


void setup() {
    
    //Declare which pin we will use and in which way they will be used.
    pinMode(led,OUTPUT); // Our LED pin is output (lighting up the LED)
    pinMode(photoresistor,INPUT);  // Our photoresistor pin is input (reading the photoresistor)
    pinMode(power,OUTPUT); // Our power pin will send power to the photoresistor
    
    digitalWrite(power, HIGH); //the output of the power pin is set to HIGH value.
    
    //Declare a variable that will be accessed by the cloud
    Particle.variable("analogVal", &analogValue, INT); //When we ask for analogVal the cloud will read an integer value from the variable analogValue in this app.
    
    //Declare a function that will be used by the cloud
    Particle.function("led", ledToggle); //When we ask the cloud for the function led, it will use the function ledToggle() in this app.
    
}

void loop() {
    
    //every 100 ms read the value from the photoresistor.
    analogValue = analogRead(photoresistor);
    delay(100);
    
}

int ledToggle(String command) {

    if(command == "on") {
        digitalWrite(led,HIGH);
        return 1;
    }
    
    else if(command == "off") {
            digitalWrite(led,LOW);
            return 0;
        }
    
        else {
            return -1;
        }
}
