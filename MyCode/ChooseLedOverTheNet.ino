//Choose led from internet

//Leds
int led1 = D4;
int led2 = D5;
int led3 = D6;

void setup() {
    
    //pin configuration
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    
    // We are going to declare a Particle.function so that we can turn the LED on and off from the cloud.
    Particle.function("chooseLed",ledChosen);
    // This is saying that when we ask the cloud for the function "chooseLed", it will employ the function ledChosen() from this app.

    //Led set low
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
}

void loop() {
    // Do nothing, wait the command.
}

int ledChosen(String command) {
    //Particle.function always gets String as input(the command) and return an integer.
   
   //if the green led has been chosen
   if (command=="green") {
        digitalWrite(led1, HIGH);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        return 0;
   }
   
   //if the yellow led has been chosen
   else if (command=="yellow") {
        digitalWrite(led1, LOW);
        digitalWrite(led2, HIGH);
        digitalWrite(led3, LOW);
        return 1;
   }
   
   //if the red led has been chosen
    else if (command=="red") {
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, HIGH);
        return 2;
   }
   
   //default answer when other parameters are given in input when calling ledChosen()
   else {
        return -1;
   }
   
}
