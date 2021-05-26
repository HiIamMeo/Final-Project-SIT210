
#define triggerPin D7 // pwm/input
#define echoPin D3 //output

double duration, distance;
const double speedOfSound = 0.0135; // in inches

void setup() {
    pinMode(triggerPin, OUTPUT); // send pulses out from the Argon
    pinMode(echoPin, INPUT); // receives the pulses from the device
}

double getDistance() { // returns distance from the sensor, NOT from equilibrium
    digitalWrite(triggerPin, HIGH); // makes sure the trigger pin is clear
    delayMicroseconds(2); 
    digitalWrite(triggerPin, LOW); // generates an ultrasonic sound wave 
    delayMicroseconds(10);       
    
    duration = pulseIn(echoPin, HIGH); // measures the duration of a pulse in   microseconds
    distance = (duration / 2) * speedOfSound; // duration = time it takes for the pulse to go out + bounce back.
    return distance;
}

void loop() 
{
    double data = getDistance();
    if(data < 10)
    {
        Particle.publish("Warning", "ESCAPED");
    }
    else if(data > 20)
    {
        Particle.publish("Warning", "Nothing");
    }
    delay(5000);
}
