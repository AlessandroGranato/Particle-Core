//Program that simulate leds of a semaphore

int led1 = D6; 
int led2 = D5;
int led3 = D4;


void setup() {
    
  //We set leds as output, since they have to illuminate in time    
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

}

void loop() {
  
  //green led is up
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);

  delay(3000);

  //green and yellow led are up  
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);

  delay(3000);
  
  //red led is up
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);

  delay(3000);

  // And repeat!
}
