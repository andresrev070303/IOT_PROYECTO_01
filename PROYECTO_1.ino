const int PIN_BLUE = 12;
const int PIN_WHITE = 14;
const int PIN_RED = 27;
const long MIN_DISTANCE = 1;
const long MAX_DISTANCE = 100;

class LED {
  private:
    int pin;

  public:
    LED(int pin) : pin(pin) {
      pinMode(pin, OUTPUT);
    }

    void turnOn() {
      digitalWrite(pin, HIGH);
    }


    void turnOff() {
      digitalWrite(pin, LOW);
    }


    void blink() {
      turnOn();
      delay(200);
      turnOff();
      delay(200);
    }
};


class UltrasonicSensor {
  private:
    int triggerPin;
    int echoPin;


  public:
    UltrasonicSensor(int triggerPin, int echoPin) : triggerPin(triggerPin), echoPin(echoPin) {}
    double readUltrasonicDistance() {
      pinMode(triggerPin, OUTPUT);  // Clear the trigger
      digitalWrite(triggerPin, LOW);
      delayMicroseconds(2);
      // Sets the trigger pin to HIGH state for 10 microseconds
      digitalWrite(triggerPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(triggerPin, LOW);
      pinMode(echoPin, INPUT);
      // Reads the echo pin, and returns the sound wave travel time in microseconds
      return 0.01723 * pulseIn(echoPin, HIGH);
    }
};


void manageLEDs(long distance, LED& red, LED& white, LED& blue) {
  if (distance >= MIN_DISTANCE &&  distance <= 10) {
    red.blink();
    white.turnOff();
    blue.turnOff();
  } else if (distance > 10 && distance <= 25) {
    red.turnOn();
    white.turnOff();
    blue.turnOff();
  } else if (distance > 25 && distance <= 35) {
    red.turnOff();
    white.blink();
    blue.turnOff();
  } else if (distance > 35 && distance <= 50) {
    red.turnOff();
    white.turnOn();
    blue.turnOff();
  } else if (distance > 50 && distance <= 60){
    red.turnOff();
    white.turnOff();
    blue.blink();
  } else if (distance > 60 && distance <= MAX_DISTANCE){
    red.turnOff();
    white.turnOff();
    blue.turnOn();
  } else{
    red.turnOff();
    white.turnOff();
    blue.turnOff();
  }
}


void setup() {
  Serial.begin(9600);
}


void loop() {
  UltrasonicSensor sensor(25, 26);
  LED red(PIN_RED), white(PIN_WHITE), blue(PIN_BLUE);
  double distance = sensor.readUltrasonicDistance();
  Serial.print(distance);
  Serial.println("cm");
  delay(1000); // Wait for 100 millisecond(s)
  manageLEDs(distance, red, white, blue);
}
