
// to acces to /dev/ttyUSB0 from user 'sudo usermod -a -G dialout $USER'
// IR sensor HW-201 at #2
// DoIt ESP32 DevKit V1

#define SENSOR_PIN 2 // 

unsigned long lastflash;
int RPM;
void ICACHE_RAM_ATTR sensor_update() {
  RPM++;
}

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(SENSOR_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), sensor_update, RISING);
}

void loop() {
  noInterrupts();  
  int wings= 2;  // no of wings of rotating object, for disc object use 1 with white tape on one side
  int RPMnew = RPM/wings;  //here we used fan which has 3 wings
  Serial.print(RPM);
  Serial.print(", ");
  Serial.print(RPMnew);
  Serial.print(" Rot/sec :");  //Revolutions per second  
  Serial.print((RPMnew*60));
  Serial.println("Rot/min. ");   //Revolutions per minute  
  RPM=0;
  interrupts(); 
  delay(1000); //1 sec for real test
}