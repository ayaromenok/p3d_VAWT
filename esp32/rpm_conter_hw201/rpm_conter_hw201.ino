
// to acces to /dev/ttyUSB0 from user 'sudo usermod -a -G dialout $USER'
#define SENSOR_PIN 15 // On DOIT ESP32  devkit V1 pin GPIO15 is close to 3V3/GND

unsigned long lastflash;
int RPM;
void ICACHE_RAM_ATTR sens() {
  RPM++;
}
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(SENSOR_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), sens, RISING);
}

void loop() {
  
  noInterrupts();
  int wings= 3;  // no of wings of rotating object, for disc object use 1 with white tape on one side
  int RPMnew = RPM/wings;  //here we used fan which has 3 wings
  Serial.print(RPMnew);
  Serial.print(" Rot/sec :");  //Revolutions per second
  int state = digitalRead(SENSOR_PIN);
  Serial.print((RPMnew*60));
  Serial.println("Rot/min. ");   //Revolutions per minute  
  RPM=0;
  interrupts(); 
  delay(5000); //10 sec for manual test
}