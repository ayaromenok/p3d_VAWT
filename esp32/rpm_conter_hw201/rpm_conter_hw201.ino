
// to acces to /dev/ttyUSB0 from user 'sudo usermod -a -G dialout $USER'
#define SENSOR_PIN 15 // ESP32 pin GPIO18 connected to OUT pin of IR obstacle avoidance sensor

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // initialize the Arduino's pin as aninput
  pinMode(SENSOR_PIN, INPUT);
}

void loop() {
  // read the state of the the input pin:
  int state = digitalRead(SENSOR_PIN);

  if (state == LOW)
    Serial.println("The obstacle is present");
  else
    Serial.println("The obstacle is NOT present");

  delay(500);
}