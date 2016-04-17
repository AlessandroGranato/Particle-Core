/* Function prototypes -------------------------------------------------------*/
int tinkerDigitalRead(String pin);
int tinkerDigitalWrite(String command);
int tinkerAnalogRead(String pin);
int tinkerAnalogWrite(String command);

SYSTEM_MODE(AUTOMATIC); //This means that the Core will attempt to connect to Wi-Fi automatically.

void setup()
{
    //Setup the Tinker application here

    //Register all the Tinker functions. When we ask to the cloud to use for example "digitalread", he will use the function tinkerDigitalRead in this app.
    //Note that digitalread != digitalRead. The first is the name that we gave to the function in the cloud, while the second is the standard way to read from pins.
    Particle.function("digitalread", tinkerDigitalRead);
    Particle.function("digitalwrite", tinkerDigitalWrite);

    Particle.function("analogread", tinkerAnalogRead);
    Particle.function("analogwrite", tinkerAnalogWrite);
}

void loop()
{
    //This will run in a loop. No need to write something here because we will wait input from the app.
}

int tinkerDigitalRead(String pin)
{
    //convert ascii to integer
    int pinNumber = pin.charAt(1) - '0';
    //Sanity check to see if the pin numbers are within limits
    if (pinNumber < 0 || pinNumber > 7) return -1;

    if(pin.startsWith("D"))
    {
        pinMode(pinNumber, INPUT_PULLDOWN);
        return digitalRead(pinNumber);
    }
    else if (pin.startsWith("A"))
    {
        pinMode(pinNumber+10, INPUT_PULLDOWN);
        return digitalRead(pinNumber+10);
    }
    return -2;
}

int tinkerDigitalWrite(String command)
{
    bool value = 0;
    //convert ascii to integer
    int pinNumber = command.charAt(1) - '0';
    //Sanity check to see if the pin numbers are within limits
    if (pinNumber < 0 || pinNumber > 7) return -1;

    if(command.substring(3,7) == "HIGH") value = 1;
    else if(command.substring(3,6) == "LOW") value = 0;
    else return -2;

    if(command.startsWith("D"))
    {
        if(pinNumber == 0) {
            pinMode(pinNumber, OUTPUT);
            digitalWrite(pinNumber, HIGH);
            delay(100);
            digitalWrite(pinNumber, LOW);
            delay(100);
            digitalWrite(pinNumber, HIGH);
            delay(100);
            digitalWrite(pinNumber, LOW);
            delay(100);
            digitalWrite(pinNumber, HIGH);
            delay(100);
            digitalWrite(pinNumber, LOW);
            delay(100);
            digitalWrite(pinNumber, HIGH);
            delay(100);
            digitalWrite(pinNumber, LOW);
            delay(100);
        }
        
        else if(pinNumber == 4) {
            if (value == 1) {
                bool dFive = (digitalRead(D5) == HIGH);
                bool dSix = (digitalRead(D6) == HIGH);
            
                pinMode(pinNumber, OUTPUT);
                pinMode(D5, OUTPUT);
                pinMode(D6, OUTPUT);
                digitalWrite(pinNumber, HIGH);
                digitalWrite(D5, LOW);
                digitalWrite(D6, LOW);
                delay(100);
                digitalWrite(pinNumber, LOW);
                digitalWrite(D5, HIGH);
                digitalWrite(D6, LOW);
                delay(100);
                digitalWrite(pinNumber, LOW);
                digitalWrite(D5, LOW);
                digitalWrite(D6, HIGH);
                delay(100);
                digitalWrite(pinNumber, HIGH);
                digitalWrite(D5, LOW);
                digitalWrite(D6, LOW);
                delay(100);
                digitalWrite(pinNumber, LOW);
                digitalWrite(D5, HIGH);
                digitalWrite(D6, LOW);
                delay(100);
                digitalWrite(pinNumber, LOW);
                digitalWrite(D5, LOW);
                digitalWrite(D6, HIGH);
                delay(100);
                digitalWrite(pinNumber, HIGH);
                digitalWrite(D5, LOW);
                digitalWrite(D6, LOW);
                delay(100);
                digitalWrite(pinNumber, LOW);
                digitalWrite(D5, HIGH);
                digitalWrite(D6, LOW);
                delay(100);
                digitalWrite(pinNumber, LOW);
                digitalWrite(D5, LOW);
                digitalWrite(D6, HIGH);
                delay(100);
                digitalWrite(pinNumber, HIGH);
                digitalWrite(D5, LOW);
                digitalWrite(D6, LOW);
                delay(100);
                
                if(dFive == true) {
                    digitalWrite(D5, HIGH);
                }
                else {
                    digitalWrite(D5, LOW);
                }
                
                if(dSix == true) {
                    digitalWrite(D6, HIGH);
                }
                else {
                    digitalWrite(D6, LOW);
                }
            }
            else {
                pinMode(pinNumber, OUTPUT);
                digitalWrite(pinNumber, LOW);
            }
        }
        else{
            pinMode(pinNumber, OUTPUT);
            digitalWrite(pinNumber, value);
        }
        return 1;
    }
    else if(command.startsWith("A"))
    {
        pinMode(pinNumber+10, OUTPUT);
        digitalWrite(pinNumber+10, value);
        return 1;
    }
    else return -3;
}

int tinkerAnalogRead(String pin)
{
    //convert ascii to integer
    int pinNumber = pin.charAt(1) - '0';
    //Sanity check to see if the pin numbers are within limits
    if (pinNumber < 0 || pinNumber > 7) return -1;

    if(pin.startsWith("D"))
    {
        return -3;
    }
    else if (pin.startsWith("A"))
    {
        return analogRead(pinNumber+10);
    }
    return -2;
}

int tinkerAnalogWrite(String command)
{
    String value = command.substring(3);

    if(command.substring(0,2) == "TX")
    {
        pinMode(TX, OUTPUT);
        analogWrite(TX, value.toInt());
        return 1;
    }
    else if(command.substring(0,2) == "RX")
    {
        pinMode(RX, OUTPUT);
        analogWrite(RX, value.toInt());
        return 1;
    }

    //convert ascii to integer
    int pinNumber = command.charAt(1) - '0';
    //Sanity check to see if the pin numbers are within limits

    if (pinNumber < 0 || pinNumber > 7) return -1;

    if(command.startsWith("D"))
    {
        pinMode(pinNumber, OUTPUT);
        analogWrite(pinNumber, value.toInt());
        return 1;
    }
    else if(command.startsWith("A"))
    {
        pinMode(pinNumber+10, OUTPUT);
        analogWrite(pinNumber+10, value.toInt());
        return 1;
    }
    else if(command.substring(0,2) == "TX")
    {
        pinMode(TX, OUTPUT);
        analogWrite(TX, value.toInt());
        return 1;
    }
    else if(command.substring(0,2) == "RX")
    {
        pinMode(RX, OUTPUT);
        analogWrite(RX, value.toInt());
        return 1;
    }
    else return -2;
}
